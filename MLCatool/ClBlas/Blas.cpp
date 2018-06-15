#include<cstdio>
#include<cmath>
#include"Blas.h"
#include"clBLAS.h"


cl_context ctx = 0;
cl_command_queue queue = 0;
const clblasOrder order = clblasColumnMajor;

int env_init()
{
	cl_int err;
	cl_platform_id platform = 0;
	cl_device_id device = 0;
	cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
	int ret = 0;

	/* Setup OpenCL environment. */
	err = clGetPlatformIDs(1, &platform, NULL);
	if (err != CL_SUCCESS) {
		printf("clGetPlatformIDs() failed with %d\n", err);
		return 1;
	}

	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if (err != CL_SUCCESS) {
		printf("clGetDeviceIDs() failed with %d\n", err);
		return 1;
	}

	props[1] = (cl_context_properties)platform;
	ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
	if (err != CL_SUCCESS) {
		printf("clCreateContext() failed with %d\n", err);
		return 1;
	}

	queue = clCreateCommandQueue(ctx, device, 0, &err);
	if (err != CL_SUCCESS) {
		printf("clCreateCommandQueue() failed with %d\n", err);
		clReleaseContext(ctx);
		return 1;
	}

	/* Setup clblas. */
	err = clblasSetup();
	if (err != CL_SUCCESS) {
		printf("clblasSetup() failed with %d\n", err);
		clReleaseCommandQueue(queue);
		clReleaseContext(ctx);
		return 1;
	}
	return ret;
}

int env_release()
{
	/* Finalize work with clblas. */
	clblasTeardown();

	/* Release OpenCL working objects. */
	clReleaseCommandQueue(queue);
	clReleaseContext(ctx);
	return 0;
}

static void printResult(int n, float x[])
{
	size_t i;
	printf("\nResult:\n");

	for (i = 0; i < n; i++) {
		printf("\t%f", x[i]);
		printf("\n");
	}
}

void srotg(float sa, float sb, float c, float s)
{
	// clblasSrotg(sa, 0, sb, 0, c, s, 0);
}

void sscal_(int n, float sa, float *sx, int incx)
{
	cl_int err;
	int ret = 0;
	cl_mem bufX;
	cl_event event = NULL;

	int lenX = 1 + (n - 1)*std::abs(incx);
	/* Prepare OpenCL memory objects and place vectors inside them. */
	bufX = clCreateBuffer(ctx, CL_MEM_READ_WRITE, (lenX * sizeof(cl_float)),
		NULL, &err);

	err = clEnqueueWriteBuffer(queue, bufX, CL_TRUE, 0,
		(lenX * sizeof(cl_float)), sx, 0, NULL, NULL);

	/* Call clblas function. */
	err = clblasSscal(n, sa, bufX, 0, incx, 1, &queue, 0, NULL, &event);

	if (err != CL_SUCCESS) {
		printf("clblasSscal() failed with %d\n", err);
		ret = 1;
	}
	else {
		/* Wait for calculations to be finished. */
		err = clWaitForEvents(1, &event);

		/* Fetch results of calculations from GPU memory. */
		err = clEnqueueReadBuffer(queue, bufX, CL_TRUE, 0, (lenX * sizeof(cl_float)),
			sx, 0, NULL, NULL);
		/* At this point you will get the result of SSCAL placed in X vector. */
		// printResult(n,sx);
	}

	/* Release OpenCL events. */
	clReleaseEvent(event);

	/* Release OpenCL memory objects. */
	clReleaseMemObject(bufX);
}

int dgemv_(const char *TRANS,
	const int *M,
	const int *N,
	const double *ALPHA,
	const double *A,
	const int *LDA,
	const double *X,
	const int *INCX,
	const double *BETA,
	double *Y,
	const int *INCY)
{
	cl_int err;
	cl_mem bufA, bufX, bufY;
	cl_event event = NULL;
	clblasTranspose trans;
	int ret = 0;

	switch (*TRANS)
	{
	case 'N':
	case 'n':
		trans = clblasNoTrans;
		break;
	case 'T':
	case 't':
		trans = clblasTrans;
		break;
	case 'C':
	case 'c':
		trans = clblasConjTrans;
		break;
	}

	/* Prepare OpenCL memory objects and place matrices inside them. */
	bufA = clCreateBuffer(ctx, CL_MEM_READ_ONLY, *M * *N * sizeof(*A),
		NULL, &err);
	bufX = clCreateBuffer(ctx, CL_MEM_READ_ONLY, *N * sizeof(*X),
		NULL, &err);
	bufY = clCreateBuffer(ctx, CL_MEM_READ_WRITE, *M * sizeof(*Y),
		NULL, &err);

	err = clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0,
		*M * *N * sizeof(*A), A, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(queue, bufX, CL_TRUE, 0,
		*N * sizeof(*X), X, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(queue, bufY, CL_TRUE, 0,
		*M * sizeof(*Y), Y, 0, NULL, NULL);

	/* Call clblas extended function. */
	err = clblasDgemv(order, trans, *M, *N, *ALPHA,
		bufA, 0, *LDA, bufX, 0, *INCX, *BETA,
		bufY, 0, *INCY, 1, &queue, 0, NULL, &event);
	if (err != CL_SUCCESS) 
	{
		printf("clblasDgemvEx() failed with %d\n", err);
		ret = 1;
	}
	else 
	{
		/* Wait for calculations to be finished. */
		err = clWaitForEvents(1, &event);

		/* Fetch results of calculations from GPU memory. */
		err = clEnqueueReadBuffer(queue, bufY, CL_TRUE, 0, *M * sizeof(*Y),
			Y, 0, NULL, NULL);
		/* At this point you will get the result of SGEMV placed in 'result' array. */
	}

	/* Release OpenCL events. */
	clReleaseEvent(event);

	/* Release OpenCL memory objects. */
	clReleaseMemObject(bufY);
	clReleaseMemObject(bufX);
	clReleaseMemObject(bufA);

	return ret;
}

int dgemm_(const char * TRANSA,
	const char * TRANSB,
	const int * M,
	const int * N,
	const int * K,
	const double * ALPHA,
	const double * A,
	const int * LDA,
	const double * B,
	const int * LDB,
	const double * BETA,
	double * C,
	const int * LDC
)
{
	cl_int err;
	cl_mem bufA, bufB, bufC;
	cl_event event = NULL;
	clblasTranspose transa,transb;
	int ret = 0;

	switch (*TRANSA)
	{
	case 'N':
	case 'n':
		transa = clblasNoTrans;
		break;
	case 'T':
	case 't':
		transa = clblasTrans;
		break;
	case 'C':
	case 'c':
		transa = clblasConjTrans;
		break;
	}

	switch (*TRANSB)
	{
	case 'N':
	case 'n':
		transb = clblasNoTrans;
		break;
	case 'T':
	case 't':
		transb = clblasTrans;
		break;
	case 'C':
	case 'c':
		transb = clblasConjTrans;
		break;
	}

	bufA = clCreateBuffer(ctx, CL_MEM_READ_ONLY, *M * *K * sizeof(*A),
		NULL, &err);
	bufB = clCreateBuffer(ctx, CL_MEM_READ_ONLY, *K * *N * sizeof(*B),
		NULL, &err);
	bufC = clCreateBuffer(ctx, CL_MEM_READ_WRITE, *M * *N * sizeof(*C),
		NULL, &err);

	err = clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0,
		*M * *K * sizeof(*A), A, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0,
		*K * *N * sizeof(*B), B, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0,
		*M * *N * sizeof(*C), C, 0, NULL, NULL);

	/* Call clblas extended function. Perform gemm for the lower right sub-matrices */
	err = clblasDgemm(order, transa, transb, *M, *N, *K,
		*ALPHA, bufA, 0, *LDA,
		bufB, 0, *LDB, *BETA,
		bufC, 0, *LDC,
		1, &queue, 0, NULL, &event);
	if (err != CL_SUCCESS) {
		printf("clblasDgemmEx() failed with %d\n", err);
		ret = 1;
	}
	else 
	{
		/* Wait for calculations to be finished. */
		err = clWaitForEvents(1, &event);

		/* Fetch results of calculations from GPU memory. */
		err = clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0,
			*M * *N * sizeof(*C),
			C, 0, NULL, NULL);
	}

	/* Release OpenCL events. */
	clReleaseEvent(event);

	/* Release OpenCL memory objects. */
	clReleaseMemObject(bufC);
	clReleaseMemObject(bufB);
	clReleaseMemObject(bufA);

	return ret;
}

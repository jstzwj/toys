// #define EIGEN_USE_BLAS

#include<iostream>
#include<algorithm>
#include"blas.h"
#include"dense"

#include"MatrixExtension.h"
#include"DimensionalityReduction.h"

using namespace Eigen;


int main()
{
	// env_init();

	MatrixXd a(4,4);
	MatrixXd b(4,4);
	a << 1, 2, 3, 4
		, 2, 3, 4, 5
		, 6, 7, 8, 9
		, 0, 1, 2, 3;

	std::cout << catool::statistics_toolbox::princomp(a);

	//std::cout << "a+b =\n" << a+b << std::endl;



	// env_release();
	system("pause");
	return 0;
}
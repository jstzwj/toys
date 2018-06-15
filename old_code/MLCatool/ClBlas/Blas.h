#pragma once
#pragma warning(disable: 4996)  

int env_init();

int env_release();

#ifdef __cplusplus
extern "C"
{
#endif

	int dgemv_(const char *, const int *, const int *, const double *, const double *, const int *, const double *, const int *, const double *, double *, const int *);

	int dgemm_(const char *, const char *, const int *, const int *, const int *, const double *, const double *, const int *, const double *, const int *, const double *, double *, const int *);

#ifdef __cplusplus
}
#endif
#include<iostream>
#include<string>
#include<vector>
#include<array>
int a(const char c[])
{
	return 1;
}
int a(const std::string & str)
{
	return 3;
}


/*
struct IO
{
template<typename T> IO& operator=(T&& t) { std::cout << "yes1" << std::endl; return *this; }
//IO& operator=(IO&& t) { std::cout << "yes2" << std::endl; return *this; }
IO() { std::cout << "NO" << reinterpret_cast<intptr_t> (this)<<std::endl; }
//IO(IO&&) { std::cout << "PPP2" << std::endl; }
IO(int i) { std::cout << "NO2" << reinterpret_cast<intptr_t> (this) << std::endl; }
~IO() { std::cout << "LLL" << std::endl; }
};


int main()
{

IO op{ 1 };
std::cout << "=====" << std::endl;
op = {};

system("pause");
return 0;
}

*/

/*
#include<variant>
#include<iostream>
template<class...T>
std::ostream & operator<<(std::ostream &os, const std::variant<T...>& v)
{
	std::visit([&os](const auto &x) {os << x; },v);
	return os;
}
int main()
{
	std::cout << std::endl;
}

*/


#include<iostream>
#include<cmath>
#include<ctime>
#include<immintrin.h>
#include <intrin.h>  
inline double qPow(double i, int n)
{
	double result = i;
	int m = 1;
	if (n >= 0)
	{
		for (; (m << 1) < n; m <<= 1)		result *= result;
		for (; m != n; ++m)		result *= i;
	}
	else if (n == 0)
	{
		result = 1;
	}
	else
	{
		result = 1.0 / qPow(i, -n);
	}
	return result;
}
#define ONE_SIX 0.166666666666666666666666666666666666
#define ONE_120 0.00833333333333333333333333333333
#define ONE_5040 1.984126984126984126984126984127e-4
#define ONE_362880 2.7557319223985890652557319223986e-6
#define ONE_39916800 2.5052108385441718775052108385442e-8
#define PI 3.1415926535897932384626433832795
#define TWO_PI 6.283185307179586476925286766559
#define HALF_PI 1.5707963267948966192313216916398
#define ONE_TWO_PI 0.15915494309189533576888376337251

inline double mySin(double n)
{
	if (n > 0)
	{
		n -= (int)(n * ONE_TWO_PI + 0.5 )*TWO_PI;
		if (n > HALF_PI) n = PI - n;
	}
	else
	{
		n -= (int)( n * ONE_TWO_PI - 0.5)*TWO_PI;
		if (n < -HALF_PI) n = -PI - n;
	}
	double n3 = n*n*n;
	return n - ONE_SIX*n3 + ONE_120*n*n*n3 - ONE_5040*n3*n3*n + ONE_362880*n3*n3*n3 - ONE_39916800*n*n*n3*n3*n3;

	//double n5 = n*n*n*n*n;
	//double n9 = n3*n3*n3;
	//return n - ONE_SIX*n*n*n + ONE_120*n*n*n*n*n - ONE_5040*n*n*n*n*n*n*n + ONE_362880*n*n*n*n*n*n*n*n*n - ONE_39916800*n*n*n*n*n*n*n*n*n*n*n;
	//return n*( 1.0-n2*ONE_SIX + n2*n2*ONE_120 - n2*n2*n2*ONE_5040 + n2*n2*n2*n2*ONE_362880 - ONE_39916800*n2*n2*n2*n2*n2);

	//return n - ONE_SIX*n2*n + ONE_120*n2*n2*n - ONE_5040*n2*n2*n2*n + ONE_362880*n2*n2*n2*n2*n - ONE_39916800*n2*n2*n2*n2*n2*n;
	//return n - ONE_SIX*n3 + ONE_120*n*n*n3 - ONE_5040*n3*n3*n + ONE_362880*n3*n3*n3 - ONE_39916800*n*n*n3*n3*n3;
	//return n - ONE_SIX*n*n*n + ONE_120*n5 - ONE_5040*n5*n*n + ONE_362880*n5*n*n*n*n - ONE_39916800*n5*n5*n;
	//return n - ONE_SIX*n3 + ONE_120*n2*n3- ONE_5040*n2*n2*n3+ ONE_362880*n3*n3*n3- ONE_39916800*n2*n3*n3*n3;
}


int main()
{
	clock_t start, end;
	int n = 10000000;
	srand(time(NULL));
	double m = 5.0;
	double m2 = 1.0;
	std::cout << "m:" << m << std::endl;

	//mySin(m);
	/*start = clock();
	for (int i = 0; i < n;++i)
	{
		double input = rand()/1000.0;
		double re1, re2;
		re1=sin(input);
		re2=mySin(input);
		if (fabs(re1-re2)>1e-6)
		{
			std::cout << "diff results:"<<input<<"\t"<<re1 << "\t" << re2 << std::endl;
		}
	}
	end = clock();

	std::cout << "case1:\n" << "time:" << end - start<<std::endl;
	std::cout << sin(m) << std::endl;*/
	start = clock();
	for (int i = 0; i < n; ++i)
	{
		sin(m);
	}
	end = clock();
	std::cout << "case1:\n" << "time:" << end - start << std::endl;
	std::cout << sin(m) << std::endl; 



	start = clock();
	for (int i = 0; i < n; ++i)
	{
		mySin(m);
	}
	end = clock();
	std::cout << "case2:\n" << "time:" << end - start <<std::endl;
	std::cout << mySin(m) << std::endl;


	//std::cout<<mySin(1);
	system("pause");
	return 0;
}











//std::string s("123");
//std::cout << a("hello world");
//std::cout << s.length();
//std::array<int,4> arr{1,2,3,4};
//arr[5] = 6;
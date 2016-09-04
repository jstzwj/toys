#include <assert.h> 
#include<iostream>

#include"cal.h"

inline bool floatEq(double lhs, double rhs)
{
	double tmp = lhs - rhs;
	return tmp > -1e-6&&tmp < 1e-6;
}


int main()
{
	assert(floatEq(cal("0"),0.0)==true);
	assert(floatEq(cal("1"), 1.0) == true);
	assert(floatEq(cal("9"), 9.0) == true);
	assert(floatEq(cal("11"), 11.0) == true);
	assert(floatEq(cal("123"), 123.0) == true);

	assert(floatEq(cal("+1"), 1.0) == true);
	assert(floatEq(cal("-1"), -1.0) == true);
	assert(floatEq(cal("+145"), 145.0) == true);
	assert(floatEq(cal("-1123"), -1123.0) == true);

	assert(floatEq(cal("1+1"), 2.0) == true);
	assert(floatEq(cal("1-1"), 0.0) == true);
	assert(floatEq(cal("4*5"), 20.0) == true);
	assert(floatEq(cal("20/2"), 10.0) == true);

	assert(floatEq(cal("123+123"), 246.0) == true);
	assert(floatEq(cal("123-246"), -123.0) == true);
	assert(floatEq(cal("123*2"), 246.0) == true);
	assert(floatEq(cal("123/5"), 24.6) == true);

	assert(floatEq(cal("1+2*3"), 7.0) == true);
	assert(floatEq(cal("4*5+6"), 26.0) == true);
	assert(floatEq(cal("1+1+3+4"), 9.0) == true);
	assert(floatEq(cal("2*3*4"), 24.0) == true);
	assert(floatEq(cal("6-1-1"), 4.0) == true);
	assert(floatEq(cal("120/5/2"), 12.0) == true);
	assert(floatEq(cal("120-20/5*25+80"), 100.0) == true);
	assert(floatEq(cal("123+5-6-123"), -1.0) == true);

	assert(floatEq(cal("(1+2)"), 3.0) == true);
	assert(floatEq(cal("(1+4*5)"), 21.0) == true);
	assert(floatEq(cal("(1+1)+2"), 4.0) == true);
	assert(floatEq(cal("1+(1+1)"), 3.0) == true);
	assert(floatEq(cal("1-(1-1)"), 1.0) == true);
	assert(floatEq(cal("4*(1+2)"), 12.0) == true);


	assert(floatEq(cal("((1+2)*4+1)+7*6-9"), 46.0) == true);
	assert(floatEq(cal("2*((12+23)-34)"), 2.0) == true);


	assert(floatEq(cal("(0)"), 0.0) == true);
	//assert(floatEq(cal("()"), 0.0) == true);


	system("pause");
	return 0;
}


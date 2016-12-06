#include<iostream>
#include<string>
#include<cctype>
bool isChar(const char *&str,char c) {return *str == c ? (++str,true) : false;}
bool isDigit(char c) { return c >= '0'&&c <= '9'; }
void skipSpace(const char *&str){while ((*str)&&(*str == ' '))str++;}
double toDouble(const char*& str)
{
	double ans=0.0, temp = 10.0;
	skipSpace(str);
	while (*str != '\0')
	{
		if (*str == '.') { str++; break; }
		if (!isDigit(*str))return ans;
		ans = ans * 10 + (*str - '0');
		str++;
	}
	while (*str != '\0')
	{
		if (!isDigit(*str))return ans;
		ans = ans + (*str - '0') / temp;
		temp *= 10;
		str++;
	}
	return ans;
}
bool calNum(const char *& str, double & result)
{
	skipSpace(str);
	if (isChar(str, '+') || isDigit(*str))
	{
		skipSpace(str);
		result = toDouble(str);
	}
	else if (isChar(str, '-'))
	{
		skipSpace(str);
		result = -toDouble(str);
	}
	else
	{
		throw "Unexpected number.";
	}
	return true;
}
bool calAdd(const char *& str, double & result);
bool calUnit(const char *& str, double & result)
{
	skipSpace(str);
	if (isChar(str, '('))
	{
		skipSpace(str);
		calAdd(str, result);
		skipSpace(str);
		if (!isChar(str, ')'))
			throw "Can not find the right bracket.";
	}
	else
	{
		return calNum(str, result);
	}
	return true;
}
bool calMul(const char *& str, double & result)
{
	double right;
	skipSpace(str);
	if (calUnit(str, result))
	{
		while (true)
		{
			skipSpace(str);
			if (isChar(str, '*')) 
			{
				if (calUnit(str, right))	result *= right;
			}
			else if (isChar(str, '/'))
			{
				if (calUnit(str, right))	result /= right;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		throw "Can not parse a number or expression before operator";
	}
	return true;
}
bool calAdd(const char *& str, double & result)
{
	double right;
	skipSpace(str);
	if (calMul(str, result))
	{
		while (true)
		{
			if (isChar(str, '+'))
			{
				if (calMul(str, right))	result += right;
			}
			else if (isChar(str, '-'))
			{
				if (calMul(str, right))	result -= right;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		throw "Can not parse a number or expression before operator";
	}
	return true;
}
bool calExpression(const char *& str, double & result)
{
	skipSpace(str);
	bool res=calAdd(str, result);
	if (*str != '\0')
	{
		throw"Unexpected token after the string.";
	}
	return res;
}
int main()
{
	std::string str;
	const char * strp;
	double result = 0.0;
	while (true)
	{
		std::cout << "Please input an expression:"<< std::endl;
		std::getline(std::cin,str);
		strp = str.data();
		try
		{
			calExpression(strp,result);
		}
		catch (char * error)
		{
			std::cerr << "error:" << error << std::endl;
		}

		std::cout << result << std::endl;
	}
	system("pause");
	return 0;
}
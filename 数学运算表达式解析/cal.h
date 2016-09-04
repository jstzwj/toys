#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<cctype>
class ExpBase
{
public:
	ExpBase() {}
	~ExpBase() {}
	virtual double getValue() { return 0.0; }
	virtual void release() {}
};

class ExpOp :public ExpBase
{
public:
	char opvalue;
	ExpBase * left;
	ExpBase * right;
public:
	virtual double getValue()
	{
		switch (opvalue)
		{
		case '+':
			if (left != nullptr&&right != nullptr)
				return left->getValue() + right->getValue();
			break;
		case '-':
			if (left != nullptr &&right != nullptr)
				return left->getValue() - right->getValue();
			break;
		case '*':
			if (left != nullptr &&right != nullptr)
				return left->getValue() * right->getValue();
			break;
		case '/':
			if (left != nullptr &&right != nullptr)
				return left->getValue() / right->getValue();
			break;
		default:
			throw "unknown op";
			break;
		}
	}
	virtual void release()
	{
		if (left != nullptr)
			left->release();
		if (right != nullptr)
			right->release();
		delete this;
	}
};

class ExpNum :public ExpBase
{
public:
	double numvalue;
public:
	virtual double getValue() { return numvalue; }
	virtual void release()
	{
		delete this;
	}
};

enum class TokenMark
{
	ADD, SUB, MULT, DIV, NUM, LBRACKET, RBRACKET
};
class Token
{
public:
	TokenMark tokenmark;
	int startpos;
	int endpos;
	//int line;
};
/*parse*/
int getUnsignedInteger(const std::string & str, int & cur)
{
	int result = 0;
	int len = 0;
	while (isdigit(str[cur]))
	{
		result = result * 10 + str[cur] - '0';
		++cur;
		++len;
	}
	if (len <= 0)
	{
		throw "not a int";
	}
	else
	{
		return result;
	}
}
int getInteger(const std::string & str, int & cur)
{
	if (str[cur] == '+')
	{
		++cur;
		return getUnsignedInteger(str, cur);
	}
	else if (str[cur] == '-')
	{
		++cur;
		return -getUnsignedInteger(str, cur);
	}
	else
	{
		return getUnsignedInteger(str, cur);
	}
}

ExpBase * ParseInteger(const std::string & str, int & cur)
{
	ExpNum * curnum;
	curnum = new ExpNum;

	curnum->numvalue = getInteger(str, cur);

	return curnum;
}

ExpBase * ParseNumber(const std::string & str, int & cur)
{
	ExpBase * curptr;
	curptr = ParseInteger(str, cur);
	return curptr;
}

ExpBase * ParseExpression(const std::string & str, int & cur);

ExpBase * ParseMultDivExpression(const std::string & str, int & cur)
{
	ExpBase * curptr = nullptr;
	ExpOp * ptr = nullptr;
	int curtmp=cur;

	try
	{
		curptr = ParseNumber(str,cur);
	}
	catch(char *e)
	{
		try
		{
			curptr = ParseExpression(str,cur);
		}
		catch (char *e)
		{
			cur = curtmp;
			throw e;
		}
	}

	while (str[cur]=='*'||str[cur]=='/')
	{
		
		ptr = new ExpOp;
		ptr->opvalue = str[cur];
		ptr->left = curptr;

		++cur;

		try
		{
			curptr = ParseNumber(str, cur);
		}
		catch (char *e)
		{
			try
			{
				curptr = ParseExpression(str, cur);
			}
			catch (char *e)
			{
				cur = curtmp;
				delete ptr;
				throw e;
			}
		}
		ptr->right = curptr;
		curptr = ptr;
	}
	return curptr;
}


ExpBase * ParseAddSubExpression(const std::string & str, int & cur)
{
	ExpBase * curptr = nullptr;
	ExpOp * ptr = nullptr;
	int curtmp = cur;

	try
	{
		curptr = ParseMultDivExpression(str, cur);
	}
	catch (char *e)
	{
		cur = curtmp;
		throw e;
	}

	while (str[cur] == '+' || str[cur] == '-')
	{
		ptr = new ExpOp;
		ptr->opvalue = str[cur];
		ptr->left = curptr;

		++cur;

		try
		{
			curptr = ParseMultDivExpression(str, cur);
		}
		catch (char *e)
		{
			cur = curtmp;
			delete ptr;
			throw e;
		}
		ptr->right = curptr;
		curptr = ptr;
	}
	return curptr;
}
ExpBase * ParseExpression(const std::string & str, int & cur)
{
	ExpBase * curptr;
	int curtmp = cur;

	try
	{
		if (str[cur]=='(')
		{
			++cur;
			curptr = ParseExpression(str, cur);
			if (str[cur] == ')')
			{
				++cur;
				if (str[cur]!='\0')
				{
					cur = curtmp;
					throw "";
				}
			}
		}
		else
		{
			cur = curtmp;
			throw "";
		}
	}
	catch (char *e)
	{
		try
		{
			curptr = ParseAddSubExpression(str, cur);
		}
		catch (char *e)
		{
			throw "ERROR";
		}
	}
	
	return curptr;
}



double cal(const std::string & input)
{
	int cur(0);
	ExpBase* root= ParseExpression(input, cur);

	double result= root->getValue();
	root->release();
	return result;
}
//321
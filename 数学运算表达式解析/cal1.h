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
	try
	{
		curnum->numvalue = getInteger(str, cur);
	}
	catch (char *)
	{
		return nullptr;
	}
	return curnum;
}
ExpBase * ParseNumber(const std::string & str, int & cur)
{
	ExpBase * curptr;
	curptr = ParseInteger(str, cur);
	return curptr;
}
ExpBase * ParseMultDivPureExpression(const std::string & str, int & cur)
{
	ExpBase * curptr = nullptr;
	ExpOp * ptr = nullptr;

	curptr = ParseNumber(str, cur);
	if (curptr != nullptr)
	{
		while (1)
		{
			if (str[cur] == '*' || str[cur] == '/')
			{
				ptr = new ExpOp;
				ptr->opvalue = str[cur];
				ptr->left = curptr;

				++cur;
				curptr = ParseNumber(str, cur);
				if (curptr == nullptr)
				{
					curptr = ptr->left;
					delete ptr;
					--cur;
					return curptr;
				}
				else
				{
					ptr->right = curptr;
					curptr = ptr;
				}
			}
			else
			{
				return curptr;
			}
		}

	}
	else
	{
		return nullptr;
	}
}
ExpBase * ParseAddSubPureExpression(const std::string & str, int & cur)
{
	ExpBase * curptr=nullptr;
	ExpOp * ptr=nullptr;

	curptr = ParseMultDivPureExpression(str, cur);
	if (curptr != nullptr)
	{
		while (1)
		{
			if (str[cur] == '+' || str[cur] == '-')
			{
				ptr = new ExpOp;
				ptr->opvalue = str[cur];
				ptr->left = curptr;

				++cur;
				curptr = ParseMultDivPureExpression(str, cur);
				if (curptr == nullptr)
				{
					curptr = ptr->left;
					delete ptr;
					--cur;
					return curptr;
				}
				else
				{
					ptr->right = curptr;
					curptr = ptr;
				}
			}
			else
			{
				return curptr;
			}
		}
		
	}
	else
	{
		return nullptr;
	}
}
ExpBase * ParsePureExpression(const std::string & str, int & cur)
{
	ExpBase * curptr;
	if (str[cur] == '(')
	{
		++cur;
		curptr = ParsePureExpression(str, cur);
		if (curptr == nullptr)
		{
			--cur;
			return curptr;
		}
		if (str[cur] == ')')
		{
			++cur;
		}
		else
		{
			//throw "can not find right brancket";
			return curptr;
		}
		
	}
	else
	{
		curptr = ParseAddSubPureExpression(str, cur);
	}
	return curptr;
}
ExpBase * ParseMultDivExpression(const std::string & str, int & cur)
{
	ExpBase * curptr = nullptr;
	ExpOp * ptr = nullptr;
	ExpOp * ptrtmp = nullptr;

	curptr = ParsePureExpression(str, cur);

	if (curptr != nullptr)
	{
		while (1)
		{
			if (str[cur] == '*' || str[cur] == '/')
			{
				ptr = new ExpOp;
				ptr->opvalue = str[cur];
				ptr->left = curptr;

				++cur;
				curptr = ParsePureExpression(str, cur);
				if (curptr != nullptr)
				{
					ptr->right = curptr;
					curptr = ptr;
				}
				else
				{
					--cur;
					delete ptr;
					throw "multi nothing";
				}
			}
			else
			{
				return curptr;
			}
		}

	}
	else
	{
		throw "can not find ParsePureExpression";
	}
}
ExpBase * ParseAddSubExpression(const std::string & str, int & cur)
{
	ExpBase * curptr=nullptr;
	ExpOp * ptr=nullptr;
	ExpOp * ptrtmp = nullptr;

	curptr = ParseMultDivExpression(str, cur);

	if (curptr != nullptr)
	{
		while (1)
		{
			if (str[cur] == '+' || str[cur] == '-')
			{
				ptr = new ExpOp;
				ptr->opvalue = str[cur];
				ptr->left = curptr;

				++cur;
				curptr = ParseMultDivExpression(str, cur);
				if (curptr != nullptr)
				{
					ptr->right = curptr;
					curptr = ptr;
				}
				else
				{
					--cur;
					delete ptr;
					throw "add nothing";
				}
			}
			else
			{
				return curptr;
			}
		}
		
	}
	else
	{
		throw "can not find MultDivExpression";
	}
}
ExpBase * ParseExpression(const std::string & str, int & cur)
{
	ExpBase * curptr;
	if (str[cur] == '(')
	{
		++cur;
		curptr = ParseExpression(str, cur);
		if (curptr == nullptr)
		{
			--cur;
			return curptr;
		}
		if (str[cur] == ')')
		{
			++cur;
		}
		else
		{
			//throw "can not find right brancket";
			return curptr;
		}

	}
	else
	{
		curptr = ParseAddSubExpression(str, cur);
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
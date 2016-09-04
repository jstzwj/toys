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
			if(left!=nullptr&&right!=nullptr)
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
		if(left!=nullptr)
			left->release();
		if(right!=nullptr)
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
/*Lexer*/
bool isDigit(const std::string & str,int & cur)
{
	if (str[cur] >= '0'&&str[cur] <= '9')
	{
		++cur;
		return true;
	}
	else
	{
		return false;
	}
}
bool isUnsignedInteger(const std::string & str, int & cur)
{
	if (isDigit(str,cur))
	{
		while (isDigit(str, cur))
		{
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool isInteger(const std::string & str, int & cur)
{
	switch (str[cur])
	{
	case '+':
		if (isUnsignedInteger(str,++cur))
		{
			return true;
		}
		else
		{
			//error unknown integer
			return false;
		}
		break;
	case '-':
		if (isUnsignedInteger(str, ++cur))
		{
			return true;
		}
		else
		{
			//error unknown integer
			return false;
		}
		break;
	default:
		if (isUnsignedInteger(str, cur))
		{
			return true;
		}
		else
		{
			//error unknown integer
			return false;
		}
		break;
	}
}


bool isNumber(const std::string & str, int & cur)
{
	if (isInteger(str,cur))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isOp(const std::string & str, int & cur)
{
	switch (str[cur])
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
		++cur;
		return true;
		break;
	default:
		return false;
		break;
	}
}
TokenMark whichOp(const std::string & str, const int & cur)
{
	switch (str[cur])
	{
	case '+':
		return TokenMark::ADD;
	case '-':
		return TokenMark::SUB;
	case '*':
		return TokenMark::MULT;
	case '/':
		return TokenMark::DIV;
	case '(':
		return TokenMark::LBRACKET;
	case ')':
		return TokenMark::RBRACKET;
		break;
	default:
		//error
		throw "unknown op";
		break;
	}
}
std::vector<Token> Lexer(const std::string & str)
{
	int cur(0);
	int size(str.length());
	std::vector<Token> result;
	Token temp;
	while (cur<size)
	{
		temp.startpos = cur;
		if (isOp(str, cur))
		{
			temp.tokenmark = whichOp(str, cur - 1);
			temp.endpos = cur;
		}
		else if (isNumber(str, cur))
		{
			temp.tokenmark = TokenMark::NUM;
			temp.endpos = cur;
		}
		else
		{
			//error
			throw "It is not a number or operator.";
		}
		result.push_back(temp);
	}
	return result;
}
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
	if (str[cur]=='+')
	{
		++cur;
		return getUnsignedInteger(str,cur);
	}
	else if (str[cur] == '-')
	{
		++ cur;
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
	ExpBase * curptr;

	curptr = ParseNumber(str, cur);

	if (str[cur] == '*' || str[cur] == '/')
	{
		ExpOp * ptr = new ExpOp;
		ptr->opvalue = str[cur];
		ptr->left = curptr;

		++ cur;
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
			return ptr;
		}
	}
	else
	{
		return curptr;
	}
}
ExpBase * ParseAddSubPureExpression(const std::string & str, int & cur)
{
	ExpBase * curptr;

	curptr = ParseMultDivPureExpression(str, cur);
	if (curptr != nullptr)
	{
		if (str[cur] == '+' || str[cur] == '-')
		{
			ExpOp * ptr = new ExpOp;
			ptr->opvalue = str[cur];
			ptr->left = curptr;

			++cur;
			curptr = ParseAddSubPureExpression(str, cur);
			if (curptr==nullptr)
			{
				curptr = ptr->left;
				delete ptr;
				--cur;
				return curptr;
			}
			else
			{
				ptr->right = curptr;
				return ptr;
			}
		}
		else
		{
			return curptr;
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
		++ cur;
		curptr=ParsePureExpression(str,cur);
		if (curptr==nullptr)
		{
			--cur;
		}
		if (str[cur] == ')')
		{
			++cur;
		}
		else
		{
			throw "can not find right brancket";
		}
	}
	else
	{
		curptr=ParseAddSubPureExpression(str, cur);
	}
	return curptr;
}
ExpBase * ParseMultDivExpression(const std::string & str,int & cur)
{
	ExpBase * curptr;

	curptr = ParsePureExpression(str, cur);

	if (curptr != nullptr)
	{
		if (str[cur] == '*' || str[cur] == '/')
		{
			ExpOp * ptr = new ExpOp;
			ptr->opvalue = str[cur];
			ptr->left = curptr;

			++cur;
			curptr = ParseMultDivExpression(str, cur);
			if (curptr != nullptr)
			{
				ptr->right = curptr;
				return ptr;
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
	else
	{
		throw "can not find PureExpression";
	}
}
ExpBase * ParseExpression(const std::string & str, int & cur)
{
	ExpBase * curptr;

	curptr = ParseMultDivExpression(str, cur);

	if (curptr!=nullptr)
	{
		if (str[cur]=='+'|| str[cur] == '-')
		{
			ExpOp * ptr = new ExpOp;
			ptr->opvalue = str[cur];
			ptr->left = curptr;

			++cur;
			curptr=ParseExpression(str, cur);
			if (curptr!=nullptr)
			{
				ptr->right = curptr;
				return ptr;
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
	else
	{
		throw "can not find MultDivExpression";
	}
}




int main()
{
	ExpBase * root;
	std::string input;
	std::vector<Token> tokens;
	int cur(0);


	std::cout << "请输入一串四则运算：" << std::endl;
	std::cin >> input;
	//tokens = Lexer(input);
	root = ParseExpression(input,cur);

	std::cout<<root->getValue();
	system("pause");
	root->release();
	return 0;
}
//321
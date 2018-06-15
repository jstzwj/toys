#pragma once
#ifndef RAPIDPARSER_EBNFAST
#define RAPIDPARSER_EBNFAST

class ExpBase
{
public:
	ExpBase() = default;
	virtual ~ExpBase() {}
};
class ExpRule :public ExpBase
{
public:
	ExpRule() = default;
	virtual ~ExpRule() {}
};
class ExpExpression :public ExpBase
{
public:
	ExpExpression() = default;
	virtual ~ExpExpression() {}
};
class ExpIdentifier :public ExpBase
{
public:
	ExpIdentifier() = default;
	virtual ~ExpIdentifier() {}
};
class ExpTerm :public ExpBase	//(factor)
{
public:
	ExpTerm() = default;
	virtual ~ExpTerm() {}
};

class ExpSymbol :public ExpBase	//(factor)
{
public:
	ExpSymbol() = default;
	virtual ~ExpSymbol() {}
};

#endif // !RAPIDPARSER_EBNFAST

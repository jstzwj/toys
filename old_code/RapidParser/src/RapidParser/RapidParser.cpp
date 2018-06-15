#include "RapidParser.h"

namespace rpr
{
	RapidParser::RapidParser()
	{
	}

	RapidParser::~RapidParser()
	{
	}

	RapidParserCPP::RapidParserCPP()
	{
	}

	RapidParserCPP::~RapidParserCPP()
	{
	}

	rpr_string RapidParserCPP::cleanCode(const rpr_string & source)
	{
		rpr_string result = source;
		//目前只支持注释(?...?)
		//删除注释
		std::regex re(R"(\(\?.*?\?\))");
		std::regex_replace(result, re, T(""));
		return result;
	}

	std::shared_ptr<ExpBase> RapidParserCPP::parseEbnf(const rpr_string & source)
	{
		return std::shared_ptr<ExpBase>();
	}

	void RapidParserCPP::removeLeftRecursive(std::shared_ptr<ExpBase>& root)
	{
	}

	rpr_string RapidParserCPP::genFile(std::shared_ptr<ExpBase>& root)
	{
		return rpr_string();
	}

	rpr_string RapidParserCPP::genParser(const rpr_string & source)
	{
		return rpr_string();
	}
}
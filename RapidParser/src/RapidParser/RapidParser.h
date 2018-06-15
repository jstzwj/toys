#pragma once
#ifndef RAPIDPARSER_RAPIDPARSER
#define RAPIDPARSER_RAPIDPARSER
#include<memory>
#include<regex>
#include"config.h"
#include"EbnfAst.h"
namespace rpr
{
	/*
	It is the basic class of rapid parser, which is the main class of parser generator.
	*/
	class RapidParser
	{
	public:
		RapidParser();
		virtual ~RapidParser();
	protected:
		//去除所有注释等多余信息
		virtual rpr_string cleanCode(const rpr_string & source) = 0;
		//解析ebnf为语法树
		virtual std::shared_ptr<ExpBase> parseEbnf(const rpr_string & source) = 0;
		//语义分析，检测左递归，先解决直接左递归
		virtual void removeLeftRecursive(std::shared_ptr<ExpBase> &root) = 0;
		//产生文件（可继承，自定义backend）
		virtual rpr_string genFile(std::shared_ptr<ExpBase> &root) = 0;
	public:
		//总体封装
		virtual rpr_string genParser(const rpr_string & source) = 0;
	};

	class RapidParserCPP :public RapidParser
	{
	public:
		RapidParserCPP();
		virtual ~RapidParserCPP();
	protected:
		//去除所有注释等多余信息
		virtual rpr_string cleanCode(const rpr_string & source) override;
		//解析ebnf为语法树
		virtual std::shared_ptr<ExpBase> parseEbnf(const rpr_string & source)override;
		//语义分析，检测左递归，先解决直接左递归
		virtual void removeLeftRecursive(std::shared_ptr<ExpBase> &root) override;
		//产生文件（可继承，自定义backend）
		virtual rpr_string genFile(std::shared_ptr<ExpBase> &root)override;
	public:
		//总体封装
		virtual rpr_string genParser(const rpr_string & source)override;
	};
}

#endif // !RAPIDPARSER_RAPIDPARSER

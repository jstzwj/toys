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
		//ȥ������ע�͵ȶ�����Ϣ
		virtual rpr_string cleanCode(const rpr_string & source) = 0;
		//����ebnfΪ�﷨��
		virtual std::shared_ptr<ExpBase> parseEbnf(const rpr_string & source) = 0;
		//��������������ݹ飬�Ƚ��ֱ����ݹ�
		virtual void removeLeftRecursive(std::shared_ptr<ExpBase> &root) = 0;
		//�����ļ����ɼ̳У��Զ���backend��
		virtual rpr_string genFile(std::shared_ptr<ExpBase> &root) = 0;
	public:
		//�����װ
		virtual rpr_string genParser(const rpr_string & source) = 0;
	};

	class RapidParserCPP :public RapidParser
	{
	public:
		RapidParserCPP();
		virtual ~RapidParserCPP();
	protected:
		//ȥ������ע�͵ȶ�����Ϣ
		virtual rpr_string cleanCode(const rpr_string & source) override;
		//����ebnfΪ�﷨��
		virtual std::shared_ptr<ExpBase> parseEbnf(const rpr_string & source)override;
		//��������������ݹ飬�Ƚ��ֱ����ݹ�
		virtual void removeLeftRecursive(std::shared_ptr<ExpBase> &root) override;
		//�����ļ����ɼ̳У��Զ���backend��
		virtual rpr_string genFile(std::shared_ptr<ExpBase> &root)override;
	public:
		//�����װ
		virtual rpr_string genParser(const rpr_string & source)override;
	};
}

#endif // !RAPIDPARSER_RAPIDPARSER

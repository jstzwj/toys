#include "dictionary.h"



void dictionary::readFromFile(const std::string & filepath)
{
	char* err;
	char* sql = "create table dictionary\
				(ID integer primary key autoincrement,\
				name nvarchar(64),\
				no integer,\
				comment nvarchar(256))";//��ִ�е����
	if (sqlite3_open(filepath.c_str(), &handle) != SQLITE_OK)
	{
		printf("createDB failed in createTable\n");
		return;
	}

	if (SQLITE_OK == sqlite3_exec(handle, sql, NULL, NULL, &err)) 
	{// ִ�� SQL ���  
		printf("createTable succeed!\n");
		sqlite3_close(handle);//�ر����ݿ�  
		sqlite3_free(err);
		return;
	}
	else 
	{
		printf("err:%s", err);//���ʧ�ܴ�ӡ������  
		sqlite3_free(err);
		return;
	}
}

dictionary::dictionary()
{
}


dictionary::~dictionary()
{
}

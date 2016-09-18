#include "dictionary.h"



void dictionary::readFromFile(const std::string & filepath)
{
	char* err;
	char* sql = "create table dictionary\
				(ID integer primary key autoincrement,\
				name nvarchar(64),\
				no integer,\
				comment nvarchar(256))";//待执行的语句
	if (sqlite3_open(filepath.c_str(), &handle) != SQLITE_OK)
	{
		printf("createDB failed in createTable\n");
		return;
	}

	if (SQLITE_OK == sqlite3_exec(handle, sql, NULL, NULL, &err)) 
	{// 执行 SQL 语句  
		printf("createTable succeed!\n");
		sqlite3_close(handle);//关闭数据库  
		sqlite3_free(err);
		return;
	}
	else 
	{
		printf("err:%s", err);//如果失败打印错误码  
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

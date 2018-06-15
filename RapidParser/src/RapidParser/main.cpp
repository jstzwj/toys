#include<iostream>
#include<fstream>
#include<string>

#include"vfs/VirtualFile.h"
using namespace rpr;
using namespace rpr::vfs;

int main(int argc, char **argv)
{
	const rpr_char * filePath = nullptr;
	rpr_string fileContent;
	//第一种解决方案，传入文件名
	if (argc >= 1)
	{
		filePath = argv[0];
	}
	//读入文件
	rpr::vfs::FileReader reader(rpr_string(filePath));
	//fileContent = reader.readAll();

	system("pause");

	//输出代码到目标文件
}
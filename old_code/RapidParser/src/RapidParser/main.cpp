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
	//��һ�ֽ�������������ļ���
	if (argc >= 1)
	{
		filePath = argv[0];
	}
	//�����ļ�
	rpr::vfs::FileReader reader(rpr_string(filePath));
	//fileContent = reader.readAll();

	system("pause");

	//������뵽Ŀ���ļ�
}
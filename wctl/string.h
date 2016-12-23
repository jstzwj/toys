#pragma once
class string_node
{
	char c;
	string_node * next;
	string_node * last;
};


class string
{
public:
	string();
	~string();
protected:
	int AddItem_back(int num);
	int AddItem_back();
	int AddItem_front(int num);
	int AddItem_front();
	int DelItem_back(int num);
	int DelItem_back();
	int DelItem_front(int num);
	int DelItem_front();
	string_node * begin;
	string_node * end;
};


#pragma once
template<class T>
class vector_alloc
{
public:
	vector_alloc();
	~vector_alloc();
protected:
	T * data;
};

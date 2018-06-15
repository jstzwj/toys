#include "Memory.h"



Memory::Memory()
	:data(nullptr),len(0)
{
}

Memory::Memory(nodevm_int64_t length)
{
	len = length;
	data = new byte[length];
}


Memory::~Memory()
{
	delete data;
}

Memory::Memory(const Memory & other)
{
	this->len=other.len ;
	this->data = new byte[len];
	for (nodevm_int64_t i = 0; i < len;++i)
	{
		this->data[i] = other.data[i];
	}
}

Memory::Memory(Memory && other)
{
	this->len = other.len;
	other.len = 0;
	this->data = other.data;
	other.data = nullptr;
}

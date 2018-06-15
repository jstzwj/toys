#pragma once
#include"Type.h"

class Memory
{
public:
	Memory();
	Memory(nodevm_int64_t length);
	~Memory();

	Memory(const Memory & other);
	Memory(Memory && other);

	byte getByte(nodevm_int64_t length) { return data[length]; }
	Word getWord(nodevm_int64_t length) { return data[length]; }
	nodevm_int16_t getDWord(nodevm_int64_t length) { return ((nodevm_int16_t)(data[length])<<8)|(nodevm_int16_t)(data[length+1]); }
private:
	nodevm_int64_t len;
	byte * data;

};


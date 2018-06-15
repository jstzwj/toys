#include "Cpu.h"



Cpu::Cpu()
{
}


Cpu::~Cpu()
{
}

Cpu_x86::Cpu_x86()
	:Cpu(),memory(1*1024*1024)
{
}

Cpu_x86::~Cpu_x86()
{
}

bool Cpu_x86::run()
{
	while (1)
	{
		switch (memory.getDWord(EIP))
		{
		case :
			break;
		case :
			break;
		default:

		}
	}
	return false;
}

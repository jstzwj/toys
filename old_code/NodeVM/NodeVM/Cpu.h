#pragma once
#ifndef NODEVM_CPU
#define NODEVM_CPU

#include"Type.h"
#include"Memory.h"
class Cpu
{
public:
	Cpu();
	virtual ~Cpu();
	virtual bool run()=0;
private:

};

class Cpu_x86 :public Cpu
{
public:
	Cpu_x86();
	virtual ~Cpu_x86();

	virtual bool run();

	typedef nodevm_int32_t reg;
private:
	//内存
	Memory memory;
	//通用寄存器：8个，分别为
	reg EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI;
	//标志寄存器：1个，
	reg EFLAGS;
	//控制寄存器：5个，分别为
	reg CR0, CR1, CR2, CR3, CR4;
	//调试寄存器：8个，分别为
	reg DR0 ,DR1, DR2, DR3, DR4, DR5, DR6, DR7;
	//系统地址寄存器 : 4个，
	reg GDTR,IDTR,LDTR,TR;
	//16位段寄存器：6个，分别为
	reg CS, DS, ES, FS, GS, SS;
	//其他寄存器：
	reg EIP,TSC;
};

#endif // !NODEVM_CPU




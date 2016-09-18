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
	//�ڴ�
	Memory memory;
	//ͨ�üĴ�����8�����ֱ�Ϊ
	reg EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI;
	//��־�Ĵ�����1����
	reg EFLAGS;
	//���ƼĴ�����5�����ֱ�Ϊ
	reg CR0, CR1, CR2, CR3, CR4;
	//���ԼĴ�����8�����ֱ�Ϊ
	reg DR0 ,DR1, DR2, DR3, DR4, DR5, DR6, DR7;
	//ϵͳ��ַ�Ĵ��� : 4����
	reg GDTR,IDTR,LDTR,TR;
	//16λ�μĴ�����6�����ֱ�Ϊ
	reg CS, DS, ES, FS, GS, SS;
	//�����Ĵ�����
	reg EIP,TSC;
};

#endif // !NODEVM_CPU




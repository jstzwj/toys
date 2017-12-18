#include"Process.h"

#include <stdio.h>
#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib") 


int GetMemory(HANDLE hProcess)
{
	PROCESS_MEMORY_COUNTERS pmc;
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);
	//获取这个进程的内存使用情况。
	if (::GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		return pmc.WorkingSetSize;
	}
}

bool GetPIDs()
{
	int n = 16;//initial size
	int i;
	PDWORD pdwArr = NULL;
	DWORD dwcbNeeded;
	BOOL ret;
	HANDLE hDefaultHeap = NULL;
	WCHAR ProcessName[MAX_PATH] = L"<unknown>";
	hDefaultHeap = GetProcessHeap();
	if (hDefaultHeap == NULL)
	{
		printf("Failed to get process heap.\n");
		return false;
	}
	do
	{
		n *= 2;
		pdwArr = (PDWORD)HeapAlloc(hDefaultHeap, 0, n * sizeof(DWORD));
		if (pdwArr == NULL)
		{
			printf("Failed to create PID array\n");
			return false;
		}
		ret = EnumProcesses(pdwArr, n * sizeof(DWORD), &dwcbNeeded);
		if (!ret)
		{
			printf("Failed to enumerate PIDs\n");
			return false;
		}
	} while (dwcbNeeded == n * sizeof(DWORD));
	//Note Idle is not a real process
	printf("Total Processes: %d\n", dwcbNeeded / sizeof(DWORD) - 1);
	for (i = 0; i<dwcbNeeded / sizeof(DWORD); i++)
	{
		DWORD pid = *(pdwArr + i);
		printf("PID=%6d\t", pid);
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
		if (hProcess != NULL)
		{
			DWORD len = MAX_PATH;
			QueryFullProcessImageName(hProcess, 0, ProcessName, &len);
			if (len != 0)
				wprintf(L"%s\t", ProcessName);

			wprintf(L"mem=%d", GetMemory(hProcess));
		}
		printf("\n");
	}
	HeapFree(hDefaultHeap, 0, pdwArr);
	CloseHandle(hDefaultHeap);
	return true;
}
#include "ProcessHelper.h"

DWORD GetProcessIdFromName(const char* processName) {

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, processName) == 0)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				return GetProcessId(hProcess);
			}
		}
	}
	return 0;
}

DWORD GetModuleSize(DWORD processID, char* module)
{
	HANDLE hSnap;
	MODULEENTRY32 xModule;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processID);
	xModule.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnap, &xModule)) {
		while (Module32Next(hSnap, &xModule)) {
			if (!strncmp((char*)xModule.szModule, module, 8)) {
				CloseHandle(hSnap);
				return (DWORD)xModule.modBaseSize;
			}
		}
	}
	CloseHandle(hSnap);
	return 0;
}
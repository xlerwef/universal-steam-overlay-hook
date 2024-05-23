#pragma once
#include "Windows.h"
#include "cstdio"
#include "iostream"
#include "TlHelp32.h"

DWORD GetProcessIdFromName(const char* processName);
DWORD GetModuleSize(DWORD processID, char* module);
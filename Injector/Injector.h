#pragma once
#include <windows.h>

class Injector {
public:
    // Inject DLL into target process
    bool inject(DWORD processId, const wchar_t* dllPath) {
        // Get process handle
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
        if (hProcess == NULL) {
            return false;
        }

        // Calculate the size of the DLL path string (in bytes)
        size_t pathSize = (wcslen(dllPath) + 1) * sizeof(wchar_t);

        // Allocate memory in the target process for the DLL path
        LPVOID remotePath = VirtualAllocEx(hProcess, NULL, pathSize, MEM_COMMIT, PAGE_READWRITE);
        if (remotePath == NULL) {
            CloseHandle(hProcess);
            return false;
        }

        // Write the DLL path to the allocated memory in the target process
        if (!WriteProcessMemory(hProcess, remotePath, dllPath, pathSize, NULL)) {
            VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
            CloseHandle(hProcess);
            return false;
        }

        // Get the address of LoadLibraryW in kernel32.dll
        HMODULE hKernel32 = GetModuleHandle("kernel32.dll");
        LPVOID loadLibraryAddr = GetProcAddress(hKernel32, "LoadLibraryW");

        // Create a remote thread in the target process to load the DLL
        HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0,
            (LPTHREAD_START_ROUTINE)loadLibraryAddr,
            remotePath, 0, NULL);
        if (hThread == NULL) {
            VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
            CloseHandle(hProcess);
            return false;
        }

        // Wait for the remote thread to finish
        WaitForSingleObject(hThread, INFINITE);

        // Clean up
        VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
        CloseHandle(hThread);
        CloseHandle(hProcess);

        return true;
    }
};
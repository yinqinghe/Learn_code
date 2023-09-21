//#include <iostream>
//#include <chrono>
//#include <thread>
//#include <Windows.h>
//using namespace std;
//
//bool detect_sandbox() {
//    bool is_sandbox = false;
//    auto start_time = chrono::high_resolution_clock::now();
//
//    this_thread::sleep_for(chrono::milliseconds(100));
//
//    auto end_time = chrono::high_resolution_clock::now();
//    auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
//
//    if (elapsed_time.count() < 100) {
//        is_sandbox = true;
//    }
//
//    return is_sandbox;
//}
//
//int GetNumPages() {
//    // 获取系统页面文件大小信息
//    MEMORYSTATUSEX statex;
//    statex.dwLength = sizeof(statex);
//    if (!GlobalMemoryStatusEx(&statex)) {
//        cerr << "Failed to get system memory status." << endl;
//        return 1;
//    }
//
//    SYSTEM_INFO systemInfo;
//    GetSystemInfo(&systemInfo);
//    return statex.ullTotalPageFile / systemInfo.dwPageSize;
//}
//
//int GetNumDrives() {
//    DWORD drives = GetLogicalDrives();
//    int numDrives = 0;
//    for (char i = 0; i < 26; i++) {
//        if (drives & (1 << i)) {
//            char path[4];
//            sprintf_s(path, "%c:\\", 'A' + i);
//            UINT type = GetDriveTypeA(path);
//            if (type == DRIVE_FIXED || type == DRIVE_REMOVABLE) {
//                numDrives++;
//            }
//        }
//    }
//    return numDrives;
//}
//
//
//
//int main() {
//    if (detect_sandbox()) {
//        cout << "This program may be running in a sandbox!" << endl;
//    }
//    else {
//        cout << "This program is not running in a sandbox." << endl;
//    }
//
//    int numPages = GetNumPages();
//    cout << numPages << endl;
//    if (numPages < 4000000) {
//        cout << "内存页小于正常值，可能处于虚拟机环境" << endl;
//        return 1;
//    }
//
//    int numDrives = GetNumDrives();
//    cout << numDrives << endl;
//    if (numDrives < 2) {
//        cout << "硬盘数量小于正常值，可能处于虚拟机环境" << endl;
//        return 1;
//    }
//
//    if (IsDebuggerPresent()) {
//        cout << "调试器检测到当前程序" << endl;
//        return 1;
//    }
//
//    BOOL bDebuggerPresent = FALSE;
//    if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &bDebuggerPresent) && bDebuggerPresent) {
//        cout << "远程调试器检测到当前程序" << endl;
//        return 1;
//    }
//
//    if (GetSystemMetrics(SM_REMOTESESSION) != 0) {
//        cout << "当前程序正在远程桌面会话中" << endl;
//        return 1;
//    }
//
//
//    SYSTEM_INFO systemInfo;
//    GetSystemInfo(&systemInfo);
//    cout << systemInfo.dwNumberOfProcessors << endl;
//    if (systemInfo.dwNumberOfProcessors <= 4) {
//        cout << "CPU数量小于正常值，可能处于虚拟机环境" << endl;
//        return 1;
//    }
//    system("pause");
//    return 0;
//}
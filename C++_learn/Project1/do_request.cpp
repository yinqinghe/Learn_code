#include <windows.h>
#include <iostream>
#include <string>
#include <winhttp.h>

#pragma comment(lib,"winhttp.lib") 

int main() {

    // ��ʼ���Ự
    HINTERNET hSession = WinHttpOpen(L"User-Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

    // ���ӷ�����
    HINTERNET hConnect = WinHttpConnect(hSession, L"www.baidu.com",
        INTERNET_DEFAULT_HTTP_PORT, 0);

    // ��������  
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/test.html",
        NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    // ����User-Agent�ַ���  
    std::wstring userAgent = L"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36";

    // ���User-Agent����ͷ
    WinHttpAddRequestHeaders(hRequest, userAgent.c_str(), -1L, WINHTTP_ADDREQ_FLAG_ADD);

    // ��������
    WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

    // ��ȡ��Ӧ״̬��
    DWORD statusCode = 0;
    DWORD statusCodeSize = sizeof(statusCode);
    WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
        NULL, &statusCode, &statusCodeSize, WINHTTP_NO_HEADER_INDEX);

    // ��ȡ��Ӧ����
    std::string response;
    char buffer[1024];
    DWORD bytesRead;
    do {
        WinHttpReadData(hRequest, (LPVOID)buffer, 1024, &bytesRead);
        response.append(buffer, bytesRead);
    } while (bytesRead > 0);

    // �����Ӧ  
    std::cout << "Status code: " << statusCode << std::endl;
    std::cout << "Response: " << response << std::endl;

    // �رվ��
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return 0;
}
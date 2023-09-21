#include <iostream>
#include <curl/curl.h>
#include <iconv.h>
#include <fstream>
using namespace std;

// �ص����������ڴ�����յ��� HTTP ��Ӧ����
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}


int main()
{
    CURL* curl;
    CURLcode res;
    string response;

    // ��ʼ�� cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // ��������� URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com");

        // ���ûص����������ڴ�����յ�������
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        // ��������ͷ
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36 Edg/116.0.1938.62");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // ����������Ӧʱ��
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

        // ����SSL֤����֤
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        // ���ô���
        //curl_easy_setopt(curl, CURLOPT_PROXY, "http://127.0.0.1:8080");

        // ���� HTTP ����
        res = curl_easy_perform(curl);

        // ��������Ƿ�ɹ�
        if (res != CURLE_OK)
        {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
        else
        {
            cout << "Response Length: " << response.length() << " characters" << endl;

            // ��ӡ���յ�����Ӧ����
            ofstream outfile("D:\\C#\\Visual_Studio\\test\\Project1\\file.txt");
            outfile << response;
            outfile.close();
            cout << "Response: " << response << endl;
        }

        // ������ͷ���Դ
        curl_easy_cleanup(curl);
    }
    else
    {
        cerr << "Failed to initialize cURL" << endl;
    }

    // ȫ������
    curl_global_cleanup();

    return 0;
}
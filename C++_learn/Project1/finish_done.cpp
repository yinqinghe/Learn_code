#include <iostream>
#include <vector>
#include <curl/curl.h>
#include "ctpl_stl.h"
#include <thread>
#include <string>
#include <chrono>
using namespace std;

// �ص����������ڴ�����յ��� HTTP ��Ӧ����
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// ����HTTP������̺߳���
void sendHttpRequest(int id,const string& url)
{
    CURL* curl = curl_easy_init();
    if (curl)
    {
        CURLcode res;
        string response;
        // ��Ӷ������ͷ
        std::vector<std::string> headers = {
            "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.31",
        };
        struct curl_slist* headerList = NULL;
        for (const auto& header : headers) {
            headerList = curl_slist_append(headerList, header.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        // ���ô���
        curl_easy_setopt(curl, CURLOPT_PROXY, "http://127.0.0.1:8080");
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
        else
        {
            cout << "Response Length: " << response.length() << " characters" << endl;
            //cout << "Response: " << response << endl;
        }

        curl_easy_cleanup(curl);
    }
    else
    {
        cerr << "Failed to initialize cURL" << endl;
    }
}

int main() {
    // ��ȡ��ʼʱ���
    auto start = chrono::high_resolution_clock::now();
    vector<string> urls(200, "https://www.baidu.com"); // replace with your URLs
    ctpl::thread_pool pool(20); // create a thread pool with 20 threads
    // ��ȡ����ʱ���
    auto end = chrono::high_resolution_clock::now();

    // ��������ʱ��
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    for (int i = 0; i < 200; ++i) {
        pool.push(sendHttpRequest, urls[i]);
        if (i == 199) {
            cout << "�������н�����" << endl;
        }
    }



    // �������ʱ��
    //cout << "����ʱ��: " << duration.count() << " ����" << endl;
    cout << "����ʱ��: " << duration.count() / 1000.0 << " ��" << endl;

    return 0;

}
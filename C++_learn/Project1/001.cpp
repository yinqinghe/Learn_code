#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <curl/curl.h>
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
void sendHttpRequest(const string& url)
{
    CURL* curl = curl_easy_init();
    if (curl)
    {
        CURLcode res;
        string response;

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

int main()
{
    vector<thread> threads;
    int threadCount = 200;
    string url = "https://www.example.com"; // �滻Ϊ����Ŀ��URL

    // ����ָ���������̷߳���HTTP����
    for (int i = 0; i < threadCount; ++i)
    {
        threads.emplace_back(sendHttpRequest, url);
    }

    // �ȴ������߳����
    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}
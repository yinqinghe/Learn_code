#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <chrono>



using namespace std;

// 回调函数，用于处理接收到的 HTTP 响应数据
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// 发送HTTP请求的线程函数
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
        // 设置代理
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
    string url = "https://www.example.com"; // 替换为您的目标URL

    // 创建指定数量的线程发送HTTP请求
    for (int i = 0; i < threadCount; ++i)
    {
        threads.emplace_back(sendHttpRequest, url);
    }

    // 等待所有线程完成
    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}
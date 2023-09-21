#include <iostream>
#include <curl/curl.h>
#include <iconv.h>
#include <fstream>
using namespace std;

// 回调函数，用于处理接收到的 HTTP 响应数据
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

    // 初始化 cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // 设置请求的 URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com");

        // 设置回调函数，用于处理接收到的数据
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        // 设置请求头
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36 Edg/116.0.1938.62");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 设置请求响应时间
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

        // 忽略SSL证书验证
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        // 设置代理
        //curl_easy_setopt(curl, CURLOPT_PROXY, "http://127.0.0.1:8080");

        // 发送 HTTP 请求
        res = curl_easy_perform(curl);

        // 检查请求是否成功
        if (res != CURLE_OK)
        {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
        else
        {
            cout << "Response Length: " << response.length() << " characters" << endl;

            // 打印接收到的响应数据
            ofstream outfile("D:\\C#\\Visual_Studio\\test\\Project1\\file.txt");
            outfile << response;
            outfile.close();
            cout << "Response: " << response << endl;
        }

        // 清理和释放资源
        curl_easy_cleanup(curl);
    }
    else
    {
        cerr << "Failed to initialize cURL" << endl;
    }

    // 全局清理
    curl_global_cleanup();

    return 0;
}
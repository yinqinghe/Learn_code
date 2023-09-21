#include <fstream>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <chrono>

using namespace std;

CURL* curl;

// 回调函数，用于处理接收到的 HTTP 响应数据
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void initializeCurl()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
}

string getRequestResponse(const string& url)
{
    CURLcode res;
    string response;

    // 初始化 cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        cout << "url.c_str() " << url.c_str() << endl;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36 Edg/116.0.1938.62");
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
        else
        {
            cout << "Response Length: " << response.length() << " characters" << endl;
            ofstream outfile("D:\\C#\\Visual_Studio\\test\\Project1\\file.txt");
            outfile << response;
            outfile.close();
            cout << "Response: " << response << endl;
        }
    }
    else
    {
        cerr << "Failed to initialize cURL" << endl;
    }
    return response;
}

class HttpProcessor {
public:
    void start() {
        // 创建一定数量的工作线程
        for (int i = 0; i < THREAD_COUNT; ++i) {
            threads.emplace_back(bind(&HttpProcessor::threadWorker, this));
        }
    }
    void stop() {
        // 通知所有工作线程退出
        {
            lock_guard<mutex> lock(m_mutex);
            m_exiting = true;
        }
        m_cv.notify_all();

        // 等待所有线程退出
        for (auto& thread : threads) {
            thread.join();
        }
        threads.clear();
    }
    // 发送HTTP请求
    void sendRequest(const string& url) {
        unique_lock<mutex> lock(m_mutex);
        m_requests.push(getRequestResponse(url));
        lock.unlock();
        m_cv.notify_one();
    }

private:
    static const int THREAD_COUNT = 2; // 工作线程数量     20个  15秒   4个   16秒

    // 工作线程函数
    void threadWorker() {
        while (true) {
            string response;
            {
                unique_lock<mutex> lock(m_mutex);
                // 队列为空且退出标志为真时，线程退出
                while (m_requests.empty() && !m_exiting) {
                    m_cv.wait(lock);
                }
                if (m_exiting) {
                    return;
                }
                response = m_requests.front();
                m_requests.pop();
            }

            // 处理业务逻辑，这里简单打印响应信息
            cout << "Processing response: " << response << endl;
        }
    }

private:
    mutex m_mutex;              // 互斥量
    condition_variable m_cv;    // 条件变量
    queue<string> m_requests;   // 任务队列
    vector<thread> threads;     // 工作线程
    bool m_exiting = false;     // 退出标志
};

int main() {
    // 获取开始时间点
    auto start = std::chrono::high_resolution_clock::now();
    initializeCurl();

    HttpProcessor httpProcessor;

    // 启动工作线程
    httpProcessor.start();

    // 发送HTTP请求
    for (int i = 0; i < 100; ++i) {
        string url = "https://www.baidu.com/"+ std::to_string(i);
        httpProcessor.sendRequest(url);
    }

    // 等待所有请求处理完成
    this_thread::sleep_for(chrono::seconds(5));

    // 停止工作线程
    httpProcessor.stop();

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    // 获取结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算运行时间
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // 输出运行时间
    //std::cout << "运行时间: " << duration.count() << " 毫秒" << std::endl;
    std::cout << "运行时间: " << duration.count() / 1000.0 << " 秒" << std::endl;
    return 0;
}
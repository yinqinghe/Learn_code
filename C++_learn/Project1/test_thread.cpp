/*������һ���򵥵�C++������ʹ�ö��̼߳���������������HTTP����
����������У����Ƕ�����һ��`Request`�ṹ���ʾHTTP�����Լ�һ��`HttpProcessor`����������Щ����`HttpProcessor`�ഴ����һ�������Ĺ����̣߳����ǵȴ���������е����󣬲������󵽴�ʱ���д�����
ͨ������`HttpProcessor.sendRequest()`��������HTTP���󣬽��������ӵ���������С�
�����̻߳᲻�ϴӶ����л�ȡ���󲢽��д��������������ʱ��ֹͣ�����̲߳��ȴ������������ʣ�������*/
#include <fstream>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

using namespace std;

CURL* curl;

// �ص����������ڴ������յ��� HTTP ��Ӧ����
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

    if (curl)
    {
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


// ����һ����������
struct Request {
    string url;
    int timeout;
};

class HttpProcessor {
public:
    void start() {
        // ����һ�������Ĺ����߳�
        for (int i = 0; i < THREAD_COUNT; ++i) {
            threads.emplace_back(bind(&HttpProcessor::threadWorker, this));
        }
    }

    void stop() {
        // ֪ͨ���й����߳��˳�
        {
            lock_guard<mutex> lock(m_mutex);
            m_exiting = true;
        }
        m_cv.notify_all();
        // �ȴ������߳��˳�
        for (auto& thread : threads) {
            thread.join();
        }
        threads.clear();
    }

    // ����HTTP����
    void sendRequest(const Request& request) {
        unique_lock<mutex> lock(m_mutex);
        m_requests.push(request);
        lock.unlock();
        m_cv.notify_one();
    }

private:
    static const int THREAD_COUNT = 4; // �����߳�����

    // �����̺߳���
    void threadWorker() {
        while (true) {
            Request request;
            {
                unique_lock<mutex> lock(m_mutex);
                // ����Ϊ�����˳���־Ϊ��ʱ���߳��˳�
                while (m_requests.empty() && !m_exiting) {
                    m_cv.wait(lock);
                }
                if (m_exiting) {
                    return;
                }
                request = m_requests.front();
                m_requests.pop();
            }
            // ����ҵ���߼�������򵥴�ӡ������Ϣ
            //cout << "Processing request: " << request.url << ", timeout=" << request.timeout << endl;
        }
    }

private:
    mutex m_mutex;              // ������
    condition_variable m_cv;    // ��������
    queue<Request> m_requests;  // �������
    vector<thread> threads;     // �����߳�
    bool m_exiting = false;     // �˳���־
};

int main() {
    HttpProcessor httpProcessor;

    // ���������߳�
    httpProcessor.start();

    // ����HTTP����
    for (int i = 0; i < 100; ++i) {
        string url = "https://www.baidu.com";
        string response = getRequestResponse(url);
        Request request{ "http://www.example.com", 5000 };
        httpProcessor.sendRequest(request);
    }

    // �ȴ��������������
    this_thread::sleep_for(chrono::seconds(5));

    // ֹͣ�����߳�
    httpProcessor.stop();
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
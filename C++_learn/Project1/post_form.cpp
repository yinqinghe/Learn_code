#include <iostream>
#include <curl/curl.h>
#include <string>

// �ص����������ڽ���HTTP��Ӧ
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

// �ص����������ڶ�ȡ�ļ�����
size_t ReadCallback(void* ptr, size_t size, size_t nmemb, void* stream) {
    FILE* file = (FILE*)stream;
    size_t bytesRead = fread(ptr, size, nmemb, file);
    return bytesRead;
}

int main() {
    CURL* curl;
    CURLcode res;

    // ��ʼ��cURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        std::string url = "http://example.com/api";  // �����URL

        // ����POST����
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // ����������
        struct curl_httppost* formPost = NULL;
        struct curl_httppost* lastPtr = NULL;

        // ���ͼƬ�ֶ�
        curl_formadd(&formPost, &lastPtr,
            CURLFORM_COPYNAME, "image",
            CURLFORM_FILE, "path/to/image.jpg",
            CURLFORM_END);

        // ���ñ�����
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formPost);

        // ���ûص�����������HTTP��Ӧ
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // �������󲢵ȴ���Ӧ
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            std::cout << "Response: " << response << std::endl;
        }

        // ����cURL��Դ
        curl_easy_cleanup(curl);
        curl_formfree(formPost);
    }

    // ȫ��cURL����
    curl_global_cleanup();

    return 0;
}
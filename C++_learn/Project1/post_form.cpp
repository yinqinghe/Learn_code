#include <iostream>
#include <curl/curl.h>
#include <string>

// 回调函数，用于接收HTTP响应
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

// 回调函数，用于读取文件数据
size_t ReadCallback(void* ptr, size_t size, size_t nmemb, void* stream) {
    FILE* file = (FILE*)stream;
    size_t bytesRead = fread(ptr, size, nmemb, file);
    return bytesRead;
}

int main() {
    CURL* curl;
    CURLcode res;

    // 初始化cURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        std::string url = "http://example.com/api";  // 请求的URL

        // 设置POST请求
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // 构建表单数据
        struct curl_httppost* formPost = NULL;
        struct curl_httppost* lastPtr = NULL;

        // 添加图片字段
        curl_formadd(&formPost, &lastPtr,
            CURLFORM_COPYNAME, "image",
            CURLFORM_FILE, "path/to/image.jpg",
            CURLFORM_END);

        // 设置表单数据
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formPost);

        // 设置回调函数来接收HTTP响应
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // 发送请求并等待响应
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            std::cout << "Response: " << response << std::endl;
        }

        // 清理cURL资源
        curl_easy_cleanup(curl);
        curl_formfree(formPost);
    }

    // 全局cURL清理
    curl_global_cleanup();

    return 0;
}
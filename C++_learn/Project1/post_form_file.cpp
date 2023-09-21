#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com"); // replace with your URL

        struct curl_httppost* post = NULL;
        struct curl_httppost* last = NULL;

        // add form data
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "field1", CURLFORM_COPYCONTENTS, "value1", CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "field2", CURLFORM_COPYCONTENTS, "value2", CURLFORM_END);

        // read file content
        std::string fileContent = readFile("D:\\Pics\\1.jpg");

        // add file content
        //curl_formadd(&post, &last, CURLFORM_COPYNAME, "file", CURLFORM_PTRCONTENTS, fileContent.c_str(), CURLFORM_CONTENTSLENGTH, fileContent.size(), CURLFORM_END);
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "file", CURLFORM_PTRCONTENTS, fileContent.c_str(), CURLFORM_CONTENTSLENGTH, fileContent.size(), CURLFORM_CONTENTTYPE, "application/octet-stream", CURLFORM_END);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        curl_easy_setopt(curl, CURLOPT_PROXY, "http://127.0.0.1:8080");


        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
        curl_formfree(post);
    }

    curl_global_cleanup();

    return 0;
}
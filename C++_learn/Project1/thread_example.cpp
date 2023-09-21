#include <iostream>
#include <vector>
#include <curl/curl.h>
#include "ctpl_stl.h"

void send_request(int id, const std::string& url) {
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
}

int main() {
    std::vector<std::string> urls(100, "http://example.com"); // replace with your URLs
    ctpl::thread_pool pool(10); // create a thread pool with 10 threads

    for (int i = 0; i < 100; ++i) {
        pool.push(send_request, urls[i]);
    }

    return 0;
}
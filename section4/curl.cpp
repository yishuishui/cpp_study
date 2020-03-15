// Copyright (c) 2020 by Chrono
//
// sudo apt-get remove libcurl4
// sudo apt-get install libcurl4-openssl-dev
//
// curl-config --libs
// curl-config --version
// curl-config --features
// curl-config --protocols
//
// g++ curl.cpp -std=c++11 -lcurl -o a.out;./a.out
// g++ curl.cpp -std=c++14 -lcurl -o a.out;./a.out

#include <iostream>

#include <curl/curl.h>

using namespace std;

// in curl.h
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata);

void case1()
{
    using curl_t = CURL;

    auto curl = curl_easy_init();

    if (!curl) {
        cout << "curl init error" << endl;
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "http://nginx.org");

    //curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

#if 1
    decltype(&write_callback) f =
        [](char *ptr, size_t size, size_t nmemb, void *userdata)
        {
            cout << "size = " << size * nmemb << endl;
            return size * nmemb;
        };
#endif

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, f);

    auto res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        cout << curl_easy_strerror(res) << endl;
    }

    curl_easy_cleanup(curl);
}

int main()
{
    //curl_global_init(CURL_GLOBAL_SSL);

    case1();

    cout << curl_version() << endl;
    cout << "libcurl demo" << endl;
}

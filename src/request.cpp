// © 2020 Joseph Cameron - All Rights Reserved

#include <jfc/wanikani_reviews_icon/config.h>
#include <jfc/wanikani_reviews_icon/request.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

#include <curl/curl.h>

using namespace jfc::wanikani_reviews_icon::request;
using namespace jfc::wanikani_reviews_icon;

static size_t WriteMemoryCallback(unsigned char *const contentPointer, 
    const size_t contentItemSize, 
    const size_t contentItemCount, 
    void *const userPointer)
{
    const size_t contentByteCount(contentItemSize *contentItemCount);

    auto pResponseBuffer(static_cast<response_data_type *const>(userPointer));

    pResponseBuffer->insert(pResponseBuffer->end(), contentPointer, contentPointer + contentByteCount);

    return contentByteCount;
}

static CURL *curl_handle;

static void init_once()
{
    static bool once(true);

    if (once)
    {
        once = false;

        // Init libcurl
        curl_global_init(CURL_GLOBAL_ALL);
   
        // Create handle for builds request
        curl_handle = curl_easy_init();

        if (!curl_handle) throw std::runtime_error("Failed to initialize a curl session.");

        // Configure the builds request
        curl_easy_setopt(curl_handle, CURLOPT_URL, 
            std::string("https://api.wanikani.com/v2/summary").c_str());
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        curl_slist *headerlist = curl_slist_append(nullptr, "Wanikani-Revision: 20170710");
        headerlist = curl_slist_append(headerlist, 
            std::string(std::string("Authorization: Bearer ") + config::get_wanikani_token()).c_str());
        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headerlist);

        curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 20L);

        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    }
}

void jfc::wanikani_reviews_icon::request::builds(jfc::wanikani_reviews_icon::request::response_handler_type aHandler,
    jfc::wanikani_reviews_icon::request::failed_handler_type aFailedHandler)
{
    init_once();

    // provide a new memory buffer to the writefunction registered in init_once
    response_data_type buffer;
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, reinterpret_cast<void *>(&buffer)); 

    // perform request
    const CURLcode curlResult = curl_easy_perform(curl_handle);

    // call appropriate response functor
    if (curlResult == CURLE_OK) aHandler(buffer);
    else aFailedHandler();
}


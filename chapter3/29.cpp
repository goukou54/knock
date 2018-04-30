#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <curl/curl.h>
#include <rapidjson/document.h>

size_t callback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    rapidjson::Document document;
    document.Parse(ptr);
    std::cout << document["query"]["pages"]["-1"]["imageinfo"][0]["url"].GetString() << std::endl;
}

int main()
{
    CURL *curl;

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL,
         "https://www.mediawiki.org/w/api.php"
         "?action=query"
         "&titles=File:Flag%20of%20the%20United%20Kingdom.svg"
         "&prop=imageinfo"
         "&iiprop=url"
         "&format=json"
    );
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    return 0;
}

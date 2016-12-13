#include <stdio.h>
#include <string.h>

#include <json/json.h>

#include <curl/curl.h>
/*
* to install lib:
* apt-cache search ^libcurl
* apt-get install <whatever_apt-cache_listed>
* apt-get install libjson0 libjson0-dev
*
* to compile:
* -ljson-c -lcurl
*/

//build a json data to post
json_object *build_request_field(int type, const char *id)
{
    struct json_object *object;
    object = json_object_new_object();
    json_object_object_add(object, "type", json_object_new_int(type));
    json_object_object_add(object, "id", json_object_new_string(id));
    return object;
}

void release_request_object(json_object *obj)
{
    json_object_put(obj);
}


int obtain_download_detail(char *url, json_object *post_object)
{
    CURL *curl;
    CURLcode res;
    const char *postthis = json_object_to_json_string_ext(post_object, JSON_C_TO_STRING_PLAIN);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);

        /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
           itself */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return 0;
}

int main(void)
{
    json_object *request = build_request_field(10, "movie id");
    obtain_download_detail("http://example.com", request);
    release_request_object(request);
    return 0;
}

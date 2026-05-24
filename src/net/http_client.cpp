#include "net/http_client.h"

#include "core/log.h"

#ifdef GAME_HAVE_CURL
#include <curl/curl.h>
#endif

#ifdef GAME_HAVE_CURL
static size_t http_write_body_callback(void* contents, size_t size, size_t nmemb, std::string* data) {
    const size_t total_size = size * nmemb;
    data->append((char*)contents, total_size);
    return total_size;
}

static size_t http_write_header_callback(char* buffer, size_t size, size_t nitems, std::string* headers) {
    const size_t total_size = size * nitems;
    headers->append(buffer, total_size);
    return total_size;
}
#endif

http_get_result http_get(pcstr url, long timeout_sec, bool capture_headers) {
    http_get_result result;

#ifdef GAME_HAVE_CURL
    if (!url || !*url) {
        logs::error("http_get: empty url");
        return result;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        logs::error("http_get: curl_easy_init failed");
        return result;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_body_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.body);
    if (capture_headers) {
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, http_write_header_callback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &result.headers);
    }
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Akhenaten/1.0");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout_sec);

    const CURLcode res = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &result.http_code);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        logs::error("http_get failed for %s: %s", url, curl_easy_strerror(res));
        return result;
    }

    result.ok = (result.http_code == 200);
#else
    (void)url;
    (void)timeout_sec;
    (void)capture_headers;
#endif

    return result;
}

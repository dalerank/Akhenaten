#include "net/http_client.h"

#include "core/log.h"

#ifdef GAME_HAVE_CURL
#include <curl/curl.h>
#include <cstdio>
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

    // Some platforms (e.g. Ubuntu/Debian) store CA certificates in locations
    // that libcurl's built-in auto-detection does not check, causing SSL
    // verification failures at runtime.  Try to locate a CA bundle file if
    // libcurl was built without a default, or the default is inaccessible.
    {
        const char *cainfo = nullptr;
        curl_easy_getinfo(curl, CURLINFO_CAINFO, &cainfo);
        if (!cainfo || !*cainfo || std::fopen(cainfo, "r") == nullptr) {
            static const char *fallback_paths[] = {
                "/etc/ssl/certs/ca-certificates.crt",
                "/etc/pki/tls/certs/ca-bundle.crt",
                "/usr/share/ssl/certs/ca-bundle.crt",
                "/usr/local/share/certs/ca-root-nss.crt",
                nullptr
            };
            for (const char **p = fallback_paths; *p; ++p) {
                std::FILE *fp = std::fopen(*p, "r");
                if (fp) {
                    std::fclose(fp);
                    curl_easy_setopt(curl, CURLOPT_CAINFO, *p);
                    break;
                }
            }
        }
    }
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

#include <curl/curl.h>

#include "HtmlTextAcquisition.hpp"

using namespace utils;

HtmlTextAcquisition::HtmlTextAcquisition() {}

QString HtmlTextAcquisition::getTextFromSource(const QString url) noexcept {
    CURL *curl;
    char errorBuffer[CURL_ERROR_SIZE];
    QString htmlContent;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HtmlTextAcquisition::writeContent);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent);

        curl_easy_perform(curl);
    }

    curl_easy_cleanup(curl);
    return htmlContent;
}

size_t HtmlTextAcquisition::writeContent(char *data, size_t size, size_t nmemb, QString &buffer) noexcept {
    size_t result = 0;

    if (data != nullptr) {
        buffer.append(data);
        result = size * nmemb;
    }

    return result;
}

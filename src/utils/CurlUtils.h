#ifndef SPOTIFY_PLUSPLUS_CURLUTILS_H
#define SPOTIFY_PLUSPLUS_CURLUTILS_H

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "../models/Error.h"

#include "CurlException.h"
#include "SpotifyException.h"

static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t startPos = 0;
    while ((startPos = str.find(from, startPos)) != std::string::npos) {
        str.replace(startPos, from.length(), to);
        startPos += to.length();
    }
    return str;
}

nlohmann::json spotifyCurlInternal(const std::string& request, const std::string& endpoint, const std::map<std::string, std::string>& options,
                                   const std::string& authToken, const std::string& body) {
    CURL* curl;

    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Could not initiate cURL" << std::endl;
        throw std::runtime_error("Could not initiate cURL");
    }

    std::string url = "https://api.spotify.com" + endpoint;
    if (!options.empty()) {
        url += "?";
        for (const auto& option : options) {
            url += option.first + "=" + option.second + '&';
        }
    }
    url = replaceAll(url, " ", "%20");

    std::string readBuffer;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);  // Can't authenticate the certificate, so disable authentication.
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.c_str());

    if (!authToken.empty()) {
        std::string header = "Authorization: Bearer " + authToken;
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }
    if (!body.empty())
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

    int rc = curl_easy_perform(curl);
    if (rc != CURLE_OK)
        throw CurlException(rc);

    long statusCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
    if (statusCode < 200 || statusCode > 204)
        throw SpotifyException(Error(nlohmann::json::parse(readBuffer)["error"]));

    curl_easy_cleanup(curl);
    if (readBuffer.empty())
        return nlohmann::json();
    return nlohmann::json::parse(readBuffer);
}

nlohmann::json spotifyGET(const std::string& endpoint, const std::map<std::string, std::string>& options, const std::string& authToken,
                          const std::string& body = "") {
    return spotifyCurlInternal("GET", endpoint, options, authToken, body);
}

nlohmann::json spotifyPUT(const std::string& endpoint, const std::map<std::string, std::string>& options, const std::string& authToken,
                          const std::string& body = "") {
    return spotifyCurlInternal("PUT", endpoint, options, authToken, body);
}

nlohmann::json spotifyDELETE(const std::string& endpoint, const std::map<std::string, std::string>& options, const std::string& authToken,
                             const std::string& body = "") {
    return spotifyCurlInternal("DELETE", endpoint, options, authToken, body);
}

nlohmann::json spotifyPOST(const std::string& endpoint, const std::map<std::string, std::string>& options, const std::string& authToken,
                           const std::string& body = "") {
    return spotifyCurlInternal("POST", endpoint, options, authToken, body);
}

std::string vectorJoin(const std::vector<std::string>& vector) {
    std::stringstream ss;
    for (size_t i = 0; i < vector.size(); ++i) {
        if (i != 0)
            ss << ",";
        ss << vector[i];
    }
    return ss.str();
}

#endif

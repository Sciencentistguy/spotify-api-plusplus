#include <fstream>
#include <iostream>
#include <sstream>

#include <curl/curl.h>

#include "../src/utils/curl_utils.h"

#include "spotify.h"

std::string getStringFromFile(const std::string& fileName) {
    std::stringstream buffer;
    std::ifstream file(fileName);
    buffer << file.rdbuf();
    file.close();
    auto s = buffer.str();
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
    return s;
}

constexpr auto base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

bool isBase64(unsigned char c) {
    return (std::isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64Encode(const std::string& in) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char charArray3[3];
    unsigned char charArray4[4];
    auto inLen = in.length();
    auto bytesToEncode = in.c_str();
    while (inLen--) {
        charArray3[i++] = *(bytesToEncode++);
        if (i == 3) {
            charArray4[0] = (charArray3[0] & 0xfc) >> 2;
            charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4);
            charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6);
            charArray4[3] = charArray3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64Chars[charArray4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            charArray3[j] = '\0';

        charArray4[0] = (charArray3[0] & 0xfc) >> 2;
        charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4);
        charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6);
        charArray4[3] = charArray3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64Chars[charArray4[j]];

        while ((i++ < 3))
            ret += '=';
    }

    return ret;
}

std::string getAccessToken() {
    std::string clientId = getStringFromFile("../client_id.txt");
    std::string clientSecret = getStringFromFile("../client_secret.txt");

    CURL* curl;
    curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Could not initiate cURL");
    }
    std::string readBuffer;

    constexpr auto url = "https://accounts.spotify.com/api/token";

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);  // Can't authenticate the certificate, so disable authentication.
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    std::string header = "Authorization: Basic " + base64Encode(clientId + ":" + clientSecret);
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, header.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    constexpr auto postData = "grant_type=client_credentials";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

    int rc = curl_easy_perform(curl);
    if(rc!=0){
        throw CurlException(rc);
    }
    nlohmann::json json = nlohmann::json::parse(readBuffer);
    return json["access_token"];
}

int main() {
    auto accessToken = getAccessToken();
    Spotify s{};
    s.setAuthToken(accessToken);

    auto album = s.getAlbum("0sNOF9WDwhWunNAHPD3Baj");
    std::cout << album->getName() << "\n";

    auto playlist = s.getPlaylist("7FFqFD03FJrbFMWPXNwiNd");
    std::cout << playlist->getName() << "\n";
    auto tracks = playlist->getTracks();
//    auto items = tracks.getItems();
    for (const auto& track : tracks.getItems()){
        std::cout << track.getTrack()->getName() << "\n";
    }

}
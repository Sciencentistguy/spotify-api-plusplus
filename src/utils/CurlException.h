#ifndef SPOTIFY_API_PLUSPLUS_CURLEXCEPTION_H
#define SPOTIFY_API_PLUSPLUS_CURLEXCEPTION_H

#include <exception>
#include <sstream>

class CurlException : public std::exception {
 public:
    explicit CurlException(int errorCode) : errorCode(errorCode) {
    }

    [[nodiscard]] const char* what() const noexcept override {
        std::stringstream errorStream;
        errorStream << "cURL error: " << errorCode;
        std::string message = errorStream.str();

        char* what = (char*) calloc(message.length(), sizeof(char));
        strcpy(what, message.c_str());
        return what;
    }

 private:
    int errorCode;
};
#endif

#ifndef SPOTIFY_API_PLUSPLUS_SPOTIFYEXCEPTION_H
#define SPOTIFY_API_PLUSPLUS_SPOTIFYEXCEPTION_H

#include <exception>
#include <sstream>
#include <utility>

#include "../models/error.h"

class SpotifyException : public std::exception {
 public:
    explicit SpotifyException(Error error) : error(std::move(error)) {
    }

    [[nodiscard]] const char* what() const noexcept override {
        char* what = (char*) calloc(error.getMessage().length(), sizeof(char));
        strcpy(what, error.getMessage().c_str());
        return what;
    }

 private:
    Error error;
};

#endif

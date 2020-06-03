#ifndef SPOTIFY_PLUSPLUS_CURSOR_H
#define SPOTIFY_PLUSPLUS_CURSOR_H

#include <string>

#include <nlohmann/json.hpp>

class Cursor {
 public:
    explicit Cursor(nlohmann::json cursorJson);

    [[nodiscard]] const std::string& getAfter() const;

 private:
    std::string after;
};

#endif

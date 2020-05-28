#ifndef SPOTIFY_PLUSPLUS_FOLLOWERS_H
#define SPOTIFY_PLUSPLUS_FOLLOWERS_H

#include <string>

#include <nlohmann/json.hpp>

class Followers {
 public:
    explicit Followers(nlohmann::json followersJson);

    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] int getTotal() const;

 private:
    std::string href;
    int total;
};

#endif

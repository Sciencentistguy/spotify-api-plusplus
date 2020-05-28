#ifndef SPOTIFY_PLUSPLUS_TRACKLINK_H
#define SPOTIFY_PLUSPLUS_TRACKLINK_H

#include <nlohmann/json.hpp>

class TrackLink {
 public:
    explicit TrackLink(nlohmann::json trackJson);

    [[nodiscard]] const std::map<std::string, std::string>& getExternalUrls() const;
    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] const std::string& getUri() const;

 private:
    std::map<std::string, std::string> externalUrls;
    std::string href;
    std::string id;
    std::string type;
    std::string uri;
};

#endif

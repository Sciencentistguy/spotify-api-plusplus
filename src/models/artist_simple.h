#ifndef SPOTIFY_PLUSPLUS_ARTISTSIMPLE_H
#define SPOTIFY_PLUSPLUS_ARTISTSIMPLE_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "followers.h"
#include "image.h"

class ArtistSimple {
 public:
    explicit ArtistSimple(nlohmann::json artistJson);

    [[nodiscard]] const std::map<std::string, std::string>& getExternalUrls() const;
    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] const std::string& getUri() const;

 private:
    std::map<std::string, std::string> externalUrls;
    std::string href;
    std::string id;
    std::string name;
    std::string type;
    std::string uri;
};

#endif

#ifndef SPOTIFY_PLUSPLUS_ARTISTSIMPLE_H
#define SPOTIFY_PLUSPLUS_ARTISTSIMPLE_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Followers.h"
#include "Image.h"

class ArtistSimple {
 public:
    ArtistSimple(nlohmann::json artistJson);

    std::map<std::string, std::string> GetExternalUrls() const;
    std::string GetHref() const;
    std::string GetId() const;
    std::string GetName() const;
    std::string GetType() const;
    std::string GetUri() const;

 private:
    std::map<std::string, std::string> externalUrls;
    std::string href;
    std::string id;
    std::string name;
    std::string type;
    std::string uri;
};

#endif

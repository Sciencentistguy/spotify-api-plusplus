#include "artist_simple.h"

ArtistSimple::ArtistSimple(nlohmann::json artistJson) {
    for (auto it = artistJson["external_urls"].begin(); it != artistJson["external_urls"].end(); ++it)
        externalUrls[it.key()] = it.value();
    href = artistJson["href"];
    id = artistJson["id"];
    name = artistJson["name"];
    type = artistJson["type"];
    uri = artistJson["uri"];
}

const std::map<std::string, std::string>& ArtistSimple::getExternalUrls() const {
    return externalUrls;
}

const std::string& ArtistSimple::getHref() const {
    return href;
}

const std::string& ArtistSimple::getId() const {
    return id;
}

const std::string& ArtistSimple::getName() const {
    return name;
}

const std::string& ArtistSimple::getType() const {
    return type;
}

const std::string& ArtistSimple::getUri() const {
    return uri;
}
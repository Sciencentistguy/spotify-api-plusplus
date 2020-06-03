#include "track_link.h"

TrackLink::TrackLink(nlohmann::json trackJson) {
    for (auto it = trackJson["external_urls"].begin(); it != trackJson["external_urls"].end(); ++it) {
        externalUrls[it.key()] = it.value();
    }
    href = trackJson["href"];
    id = trackJson["id"];
    type = trackJson["type"];
    uri = trackJson["uri"];
}

const std::map<std::string, std::string>& TrackLink::getExternalUrls() const {
    return externalUrls;
}

const std::string& TrackLink::getHref() const {
    return href;
}

const std::string& TrackLink::getId() const {
    return id;
}

const std::string& TrackLink::getType() const {
    return type;
}

const std::string& TrackLink::getUri() const {
    return uri;
}

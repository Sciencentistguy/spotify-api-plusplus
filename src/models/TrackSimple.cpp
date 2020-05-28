#include "TrackSimple.h"

#include <memory>

TrackSimple::TrackSimple(nlohmann::json trackJson) {
    for (const auto& json : trackJson["artists"])
        artists.push_back(std::make_shared<ArtistSimple>(json));
    for (const auto& market : trackJson["available_markets"])
        availableMarkets.push_back(market);
    discNumber = trackJson["disc_number"];
    durationMs = trackJson["duration_ms"];
    isExplicit = trackJson["explicit"];
    for (auto it = trackJson["external_urls"].begin(); it != trackJson["external_urls"].end(); ++it)
        externalUrls[it.key()] = it.value();
    href = trackJson["href"];
    id = trackJson["id"];
    /* is_playable and linked_from, although in the API, don't seem to exist in any of the JSON being returned */
    // playable = trackJson["is_playable"];
    // linkedFrom = std::shared_ptr<TrackLink>(new TrackLink(trackJson["linked_from"]));
    name = trackJson["name"];
    if (!trackJson["preview_url"].is_null())
        previewUrl = trackJson["preview_url"];
    trackNumber = trackJson["track_number"];
    type = trackJson["type"];
    uri = trackJson["uri"];
}

const std::vector<std::shared_ptr<ArtistSimple>>& TrackSimple::getArtists() const {
    return artists;
}

const std::vector<std::string>& TrackSimple::getAvailableMarkets() const {
    return availableMarkets;
}

int TrackSimple::getDiscNumber() const {
    return discNumber;
}

int TrackSimple::getDurationMs() const {
    return durationMs;
}

bool TrackSimple::getIsExplicit() const {
    return isExplicit;
}

const std::map<std::string, std::string>& TrackSimple::getExternalUrls() const {
    return externalUrls;
}

const std::string& TrackSimple::getHref() const {
    return href;
}

const std::string& TrackSimple::getId() const {
    return id;
}

bool TrackSimple::isPlayable() const {
    return playable;
}

std::shared_ptr<TrackLink> TrackSimple::getLinkedFrom() const {
    return linkedFrom;
}

const std::string& TrackSimple::getName() const {
    return name;
}

const std::string& TrackSimple::getPreviewUrl() const {
    return previewUrl;
}

int TrackSimple::getTrackNumber() const {
    return trackNumber;
}

const std::string& TrackSimple::getType() const {
    return type;
}

const std::string& TrackSimple::getUri() const {
    return uri;
}
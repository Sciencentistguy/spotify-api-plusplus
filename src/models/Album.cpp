#include "Album.h"

#include <memory>

#include "TrackSimple.h"

Album::Album(nlohmann::json albumJson) : AlbumSimple::AlbumSimple(albumJson) {
    for (const auto& json : albumJson["copyrights"])
        copyrights.push_back(std::make_shared<Copyright>(json));
    for (auto it = albumJson["external_ids"].begin(); it != albumJson["external_ids"].end(); ++it)
        externalIds[it.key()] = it.value();
    for (const auto & genre : albumJson["genres"])
        genres.push_back(genre);
    popularity = albumJson["popularity"];
    releaseDate = albumJson["release_date"];
    releaseDatePrecision = albumJson["release_date_precision"];
    tracks = Pager<TrackSimple>(albumJson["tracks"]);
}

Album::~Album() = default;

const std::vector<std::shared_ptr<Copyright>>& Album::getCopyrights() const {
    return copyrights;
}

const std::map<std::string, std::string>& Album::getExternalIds() const {
    return externalIds;
}

const std::vector<std::string>& Album::getGenres() const {
    return genres;
}

const std::string& Album::getLabel() const {
    return label;
}

int Album::getPopularity() const {
    return popularity;
}

const std::string& Album::getReleaseDate() const {
    return releaseDate;
}

const std::string& Album::getReleaseDatePrecision() const {
    return releaseDatePrecision;
}

const Pager<TrackSimple>& Album::getTracks() const {
    return tracks;
}

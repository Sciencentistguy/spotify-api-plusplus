#include "track.h"

#include <memory>

#include "album_simple.h"
namespace spotify {
    Track::Track(nlohmann::json trackJson) : TrackSimple::TrackSimple(trackJson) {
        album = std::make_shared<AlbumSimple>(trackJson["album"]);
        for (auto it = trackJson["external_ids"].begin(); it != trackJson["external_ids"].end(); ++it)
            externalIds[it.key()] = it.value();
        popularity = trackJson["popularity"];
    }

    Track::~Track() = default;

    const std::shared_ptr<AlbumSimple>& Track::getAlbum() const {
        return album;
    }

    const std::map<std::string, std::string>& Track::getExternalIds() const {
        return externalIds;
    }

    int Track::getPopularity() const {
        return popularity;
    }
}  // namespace spotify
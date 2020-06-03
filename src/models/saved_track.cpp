#include "saved_track.h"

#include <memory>

SavedTrack::SavedTrack(nlohmann::json trackJson) {
    addedAt = trackJson["added_at"];
    track = std::make_shared<Track>(trackJson["track"]);
}

const std::string& SavedTrack::getAddedAt() const {
    return addedAt;
}

std::shared_ptr<Track> SavedTrack::getTrack() const {
    return track;
}

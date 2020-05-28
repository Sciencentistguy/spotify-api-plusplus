#include "PlaylistTrack.h"

PlaylistTrack::PlaylistTrack(nlohmann::json trackJson) {
    addedAt = trackJson["added_at"];
    addedBy = std::shared_ptr<UserPublic>(new UserPublic(trackJson["added_by"]));
    local = trackJson["is_local"];
    track = std::shared_ptr<Track>(new Track(trackJson["track"]));
}

const std::string& PlaylistTrack::getAddedAt() const {
    return addedAt;
}

std::shared_ptr<UserPublic> PlaylistTrack::getAddedBy() const {
    return addedBy;
}

bool PlaylistTrack::isLocal() const {
    return local;
}

std::shared_ptr<Track> PlaylistTrack::getTrack() const {
    return track;
}

#ifndef SPOTIFY_PLUSPLUS_PLAYLISTTRACK_H
#define SPOTIFY_PLUSPLUS_PLAYLISTTRACK_H

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "Track.h"
#include "User.h"

class PlaylistTrack {
 public:
    explicit PlaylistTrack(nlohmann::json trackJson);

    [[nodiscard]] const std::string& getAddedAt() const;
    [[nodiscard]] std::shared_ptr<UserPublic> getAddedBy() const;
    [[nodiscard]] bool isLocal() const;
    [[nodiscard]] std::shared_ptr<Track> getTrack() const;

 private:
    std::string addedAt;
    std::shared_ptr<UserPublic> addedBy;
    bool local;
    std::shared_ptr<Track> track;
};

#endif

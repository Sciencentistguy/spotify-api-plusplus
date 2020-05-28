#ifndef SPOTIFY_PLUSPLUS_PLAYLISTTRACK_H
#define SPOTIFY_PLUSPLUS_PLAYLISTTRACK_H

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "Track.h"
#include "User.h"

class PlaylistTrack {
 public:
    PlaylistTrack(nlohmann::json trackJson);

    std::string GetAddedAt() const;
    std::shared_ptr<UserPublic> GetAddedBy() const;
    bool IsLocal() const;
    std::shared_ptr<Track> GetTrack() const;

 private:
    std::string addedAt;
    std::shared_ptr<UserPublic> addedBy;
    bool isLocal;
    std::shared_ptr<Track> track;
};

#endif

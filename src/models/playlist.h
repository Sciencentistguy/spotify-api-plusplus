#ifndef SPOTIFY_PLUSPLUS_PLAYLIST_H
#define SPOTIFY_PLUSPLUS_PLAYLIST_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "followers.h"
#include "image.h"
#include "pager.h"
#include "playlist_simple.h"
#include "playlist_track.h"
#include "user.h"

class Playlist : public PlaylistSimple {
 public:
    explicit Playlist(nlohmann::json playlistJson);

    [[nodiscard]] const std::string& getDescription() const;
    [[nodiscard]] std::shared_ptr<Followers> getFollowers() const;

 private:
    std::string description;
    std::shared_ptr<Followers> followers;
};

#endif

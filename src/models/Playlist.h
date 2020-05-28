#ifndef SPOTIFY_PLUSPLUS_PLAYLIST_H
#define SPOTIFY_PLUSPLUS_PLAYLIST_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Followers.h"
#include "Image.h"
#include "Pager.h"
#include "PlaylistSimple.h"
#include "PlaylistTrack.h"
#include "User.h"

class Playlist : public PlaylistSimple {
 public:
    Playlist(nlohmann::json playlistJson);

    std::string GetDescription() const;
    std::shared_ptr<Followers> GetFollowers() const;

 private:
    std::string description;
    std::shared_ptr<Followers> followers;
};

#endif

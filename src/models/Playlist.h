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
    explicit Playlist(nlohmann::json playlistJson);

    [[nodiscard]] const std::string& getDescription() const;
    [[nodiscard]] std::shared_ptr<Followers> getFollowers() const;

 private:
    std::string description;
    std::shared_ptr<Followers> followers;
};

#endif

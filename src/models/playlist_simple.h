#ifndef SPOTIFY_PLUSPLUS_PLAYLISTSIMPLE_H
#define SPOTIFY_PLUSPLUS_PLAYLISTSIMPLE_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "followers.h"
#include "image.h"
#include "pager.h"
#include "playlist_track.h"
#include "user.h"

class PlaylistSimple {
 public:
    explicit PlaylistSimple(nlohmann::json playlistJson);

    [[nodiscard]] bool isCollaborative() const;
    [[nodiscard]] const std::map<std::string, std::string>& getExternalUrls() const;
    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Image>>& getImages() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::shared_ptr<UserPublic>& getOwner() const;
    [[nodiscard]] bool getIsPublic() const;
    [[nodiscard]] const std::string& getSnapshotId() const;
    [[nodiscard]] const Pager<PlaylistTrack>& getTracks() const;
    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] const std::string& getUri() const;

 private:
    bool collaborative;
    std::map<std::string, std::string> externalUrls;
    std::string href;
    std::string id;
    std::vector<std::shared_ptr<Image>> images;
    std::string name;
    std::shared_ptr<UserPublic> owner;
    bool isPublic;
    std::string snapshotId;
    Pager<PlaylistTrack> tracks;
    std::string type;
    std::string uri;
};

#endif

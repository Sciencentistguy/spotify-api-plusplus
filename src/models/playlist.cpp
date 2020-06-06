#include "playlist.h"

#include <memory>
namespace spotify {
    Playlist::Playlist(nlohmann::json playlistJson) : PlaylistSimple::PlaylistSimple(playlistJson) {
        if (!playlistJson["description"].is_null())
            description = playlistJson["description"];
        followers = std::make_shared<Followers>(playlistJson["followers"]);
    }

    const std::string& Playlist::getDescription() const {
        return description;
    }

    std::shared_ptr<Followers> Playlist::getFollowers() const {
        return followers;
    }
}  // namespace spotify
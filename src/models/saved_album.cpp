#include "saved_album.h"

#include <memory>
namespace spotify {
    SavedAlbum::SavedAlbum(nlohmann::json albumJson) {
        addedAt = albumJson["added_at"];
        album = std::make_shared<Album>(albumJson["album"]);
    }

    const std::string& SavedAlbum::getAddedAt() const {
        return addedAt;
    }

    std::shared_ptr<Album> SavedAlbum::getAlbum() const {
        return album;
    }
}
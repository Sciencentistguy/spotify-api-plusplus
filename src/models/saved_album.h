#ifndef SPOTIFY_PLUSPLUS_SAVEDALBUM_H
#define SPOTIFY_PLUSPLUS_SAVEDALBUM_H

#include <string>

#include <nlohmann/json.hpp>

#include "album.h"

class SavedAlbum {
 public:
    explicit SavedAlbum(nlohmann::json albumJson);

    [[nodiscard]] const std::string& getAddedAt() const;
    [[nodiscard]] std::shared_ptr<Album> getAlbum() const;

 private:
    std::string addedAt;
    std::shared_ptr<Album> album;
};

#endif

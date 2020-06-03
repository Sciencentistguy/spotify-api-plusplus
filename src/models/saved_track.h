#ifndef SPOTIFY_PLUSPLUS_SAVEDTRACK_H
#define SPOTIFY_PLUSPLUS_SAVEDTRACK_H

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "track.h"

class SavedTrack {
 public:
    explicit SavedTrack(nlohmann::json trackJson);

    [[nodiscard]] const std::string& getAddedAt() const;
    [[nodiscard]] std::shared_ptr<Track> getTrack() const;

 private:
    std::string addedAt;
    std::shared_ptr<Track> track;
};

#endif

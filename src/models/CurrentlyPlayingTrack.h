#ifndef SPOTIFY_API_PLUSPLUS_CURRENTLYPLAYINGTRACK_H
#define SPOTIFY_API_PLUSPLUS_CURRENTLYPLAYINGTRACK_H

#include <nlohmann/json.hpp>

#include "Context.h"
#include "Track.h"

class CurrentlyPlayingTrack {
 public:
    explicit CurrentlyPlayingTrack(nlohmann::json currentlyPlayingJson);

    [[nodiscard]] const Context& GetContext() const;
    [[nodiscard]] int GetTimestamp() const;
    [[nodiscard]] int GetProgressMs() const;
    [[nodiscard]] bool IsPlaying() const;
    [[nodiscard]] const Track& GetItem() const;

 private:
    Context context;
    int timestamp;
    int progressMs;
    bool isPlaying;
    Track item;
};

#endif

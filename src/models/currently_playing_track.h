#ifndef SPOTIFY_API_PLUSPLUS_CURRENTLY_PLAYING_TRACK_H
#define SPOTIFY_API_PLUSPLUS_CURRENTLY_PLAYING_TRACK_H

#include <nlohmann/json.hpp>

#include "context.h"
#include "track.h"
namespace spotify {
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
}  // namespace spotify
#endif

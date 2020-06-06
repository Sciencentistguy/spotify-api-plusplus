#ifndef SPOTIFY_API_PLUSPLUS_PLAY_HISTORY_OBJECT_H
#define SPOTIFY_API_PLUSPLUS_PLAY_HISTORY_OBJECT_H

#include <nlohmann/json.hpp>

#include "context.h"
#include "track_simple.h"
namespace spotify {
    class PlayHistoryObject {
     public:
        explicit PlayHistoryObject(nlohmann::json playHistoryJson);

        [[nodiscard]] const TrackSimple& getTrack() const;
        [[nodiscard]] const std::string& getPlayedAt() const;
        [[nodiscard]] const Context& getContext() const;

     private:
        TrackSimple track;
        std::string playedAt;
        Context context;
    };
}  // namespace spotify

#endif

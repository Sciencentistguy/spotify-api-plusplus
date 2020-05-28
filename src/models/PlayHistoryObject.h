#ifndef SPOTIFY_API_PLUSPLUS_PLAYHISTORYOBJECT_H
#define SPOTIFY_API_PLUSPLUS_PLAYHISTORYOBJECT_H

#include <nlohmann/json.hpp>

#include "Context.h"
#include "TrackSimple.h"

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

#endif

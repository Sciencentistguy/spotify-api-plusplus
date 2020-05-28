#ifndef SPOTIFY_API_PLUSPLUS_PLAYHISTORYOBJECT_H
#define SPOTIFY_API_PLUSPLUS_PLAYHISTORYOBJECT_H

#include <nlohmann/json.hpp>

#include "Context.h"
#include "TrackSimple.h"

class PlayHistoryObject {
 public:
    PlayHistoryObject(nlohmann::json playHistoryJson);

    TrackSimple GetTrack() const;
    std::string GetPlayedAt() const;
    Context GetContext() const;

 private:
    TrackSimple track;
    std::string playedAt;
    Context context;
};

#endif

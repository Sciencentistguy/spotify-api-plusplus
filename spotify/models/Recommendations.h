#ifndef SPOTIFY_PLUSPLUS_RECCOMENDATIONS_H
#define SPOTIFY_PLUSPLUS_RECCOMENDATIONS_H

#include <vector>
#include <memory>
#include "RecommendationsSeed.h"
#include "Track.h"
#include <spotify/utils/json.h>

class Recommendations
{
public:
    Recommendations(nlohmann::json reccomendationsJson);

    std::vector<std::shared_ptr<RecommendationsSeed>> GetSeeds();
    std::vector<std::shared_ptr<Track>> GetTracks();

private:
    std::vector<std::shared_ptr<RecommendationsSeed>> seeds;
    std::vector<std::shared_ptr<Track>> tracks;
};


#endif
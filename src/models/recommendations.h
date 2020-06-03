#ifndef SPOTIFY_PLUSPLUS_RECCOMENDATIONS_H
#define SPOTIFY_PLUSPLUS_RECCOMENDATIONS_H

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include "recommendations_seed.h"
#include "track.h"

class Recommendations {
 public:
    explicit Recommendations(nlohmann::json reccomendationsJson);

    [[nodiscard]] const std::vector<std::shared_ptr<RecommendationsSeed>>& getSeeds() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Track>>& getTracks() const;

 private:
    std::vector<std::shared_ptr<RecommendationsSeed>> seeds;
    std::vector<std::shared_ptr<Track>> tracks;
};

#endif

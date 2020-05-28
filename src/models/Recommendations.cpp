#include "Recommendations.h"

#include <memory>

Recommendations::Recommendations(nlohmann::json reccomendationsJson) {
    for (const auto& json : reccomendationsJson["seeds"])
        seeds.push_back(std::make_shared<RecommendationsSeed>(json));
    for (const auto& json : reccomendationsJson["tracks"])
        tracks.push_back(std::make_shared<Track>(json));
}

const std::vector<std::shared_ptr<RecommendationsSeed>>& Recommendations::getSeeds() const {
    return seeds;
}

const std::vector<std::shared_ptr<Track>>& Recommendations::getTracks() const {
    return tracks;
}

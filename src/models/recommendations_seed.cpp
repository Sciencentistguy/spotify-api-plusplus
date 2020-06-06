#include "recommendations_seed.h"
namespace spotify {
    RecommendationsSeed::RecommendationsSeed(nlohmann::json reccomendationsJson) {
        afterFilteringSize = reccomendationsJson["afterFilteringSize"];
        afterRelinkingSize = reccomendationsJson["afterRelinkingSize"];
        href = reccomendationsJson["href"];
        id = reccomendationsJson["id"];
        initialPoolSize = reccomendationsJson["initialPoolSize"];
        type = reccomendationsJson["type"];
    }

    int RecommendationsSeed::getAfterFilteringSize() const {
        return afterFilteringSize;
    }

    int RecommendationsSeed::getAfterRelinkingSize() const {
        return afterRelinkingSize;
    }

    const std::string& RecommendationsSeed::getHref() const {
        return href;
    }

    const std::string& RecommendationsSeed::getId() const {
        return id;
    }

    int RecommendationsSeed::getInitialPoolSize() const {
        return initialPoolSize;
    }

    const std::string& RecommendationsSeed::getType() const {
        return type;
    }
}  // namespace spotify
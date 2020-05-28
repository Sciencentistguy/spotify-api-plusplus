#ifndef SPOTIFY_PLUSPLUS_RECOMMENDATIONSSEED_H
#define SPOTIFY_PLUSPLUS_RECOMMENDATIONSSEED_H

#include <string>

#include <nlohmann/json.hpp>

class RecommendationsSeed {
 public:
    explicit RecommendationsSeed(nlohmann::json reccomendationsJson);

    [[nodiscard]] int getAfterFilteringSize() const;
    [[nodiscard]] int getAfterRelinkingSize() const;
    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] int getInitialPoolSize() const;
    [[nodiscard]] const std::string& getType() const;

 private:
    int afterFilteringSize;
    int afterRelinkingSize;
    std::string href;
    std::string id;
    int initialPoolSize;
    std::string type;
};

#endif

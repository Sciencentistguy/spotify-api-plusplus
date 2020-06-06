#ifndef SPOTIFY_PLUSPLUS_AUDIOFEATURES_H
#define SPOTIFY_PLUSPLUS_AUDIOFEATURES_H

#include <string>

#include <nlohmann/json.hpp>
namespace spotify {
    class AudioFeatures {
     public:
        explicit AudioFeatures(nlohmann::json audioFeaturesJson);

        [[nodiscard]] float getAcousticness() const;
        [[nodiscard]] const std::string& getAnalysisUrl() const;
        [[nodiscard]] float getDanceability() const;
        [[nodiscard]] int getDurationMs() const;
        [[nodiscard]] float getEnergy() const;
        [[nodiscard]] const std::string& getId() const;
        [[nodiscard]] float getInstrumentalness() const;
        [[nodiscard]] int getKey() const;
        [[nodiscard]] float getLiveness() const;
        [[nodiscard]] float getLoudness() const;
        [[nodiscard]] int getMode() const;
        [[nodiscard]] float getSpeechiness() const;
        [[nodiscard]] float getTempo() const;
        [[nodiscard]] int getTimeSignature() const;
        [[nodiscard]] const std::string& getTrackHref() const;
        [[nodiscard]] const std::string& getType() const;
        [[nodiscard]] const std::string& getUri() const;
        [[nodiscard]] float getValence() const;

     private:
        float acousticness;
        std::string analysisUrl;
        float danceability;
        int durationMs;
        float energy;
        std::string id;
        float instrumentalness;
        int key;
        float liveness;
        float loudness;
        int mode;
        float speechiness;
        float tempo;
        int timeSignature;
        std::string trackHref;
        std::string type;
        std::string uri;
        float valence;
    };
}  // namespace spotify
#endif

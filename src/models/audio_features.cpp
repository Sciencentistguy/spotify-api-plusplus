#include "audio_features.h"
namespace spotify {
    AudioFeatures::AudioFeatures(nlohmann::json audioFeaturesJson) {
        acousticness = audioFeaturesJson["acousticness"];
        analysisUrl = audioFeaturesJson["analysis_url"];
        danceability = audioFeaturesJson["danceability"];
        durationMs = audioFeaturesJson["duration_ms"];
        energy = audioFeaturesJson["energy"];
        id = audioFeaturesJson["id"];
        instrumentalness = audioFeaturesJson["instrumentalness"];
        key = audioFeaturesJson["key"];
        liveness = audioFeaturesJson["liveness"];
        loudness = audioFeaturesJson["loudness"];
        mode = audioFeaturesJson["mode"];
        speechiness = audioFeaturesJson["speechiness"];
        tempo = audioFeaturesJson["tempo"];
        timeSignature = audioFeaturesJson["time_signature"];
        trackHref = audioFeaturesJson["track_href"];
        type = audioFeaturesJson["type"];
        uri = audioFeaturesJson["uri"];
        valence = audioFeaturesJson["valence"];
    }

    float AudioFeatures::getAcousticness() const {
        return acousticness;
    }

    const std::string& AudioFeatures::getAnalysisUrl() const {
        return analysisUrl;
    }

    float AudioFeatures::getDanceability() const {
        return danceability;
    }

    int AudioFeatures::getDurationMs() const {
        return durationMs;
    }

    float AudioFeatures::getEnergy() const {
        return energy;
    }

    const std::string& AudioFeatures::getId() const {
        return id;
    }

    float AudioFeatures::getInstrumentalness() const {
        return instrumentalness;
    }

    int AudioFeatures::getKey() const {
        return key;
    }

    float AudioFeatures::getLiveness() const {
        return liveness;
    }

    float AudioFeatures::getLoudness() const {
        return loudness;
    }

    int AudioFeatures::getMode() const {
        return mode;
    }

    float AudioFeatures::getSpeechiness() const {
        return speechiness;
    }

    float AudioFeatures::getTempo() const {
        return tempo;
    }

    int AudioFeatures::getTimeSignature() const {
        return timeSignature;
    }

    const std::string& AudioFeatures::getTrackHref() const {
        return trackHref;
    }

    const std::string& AudioFeatures::getType() const {
        return type;
    }

    const std::string& AudioFeatures::getUri() const {
        return uri;
    }

    float AudioFeatures::getValence() const {
        return valence;
    }
}  // namespace spotify
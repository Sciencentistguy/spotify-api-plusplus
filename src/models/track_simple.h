#ifndef SPOTIFY_PLUSPLUS_TRACKSIMPLE_H
#define SPOTIFY_PLUSPLUS_TRACKSIMPLE_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "artist.h"
#include "track_link.h"

class TrackSimple {
 public:
    explicit TrackSimple(nlohmann::json trackJson);

    [[nodiscard]] const std::vector<std::shared_ptr<ArtistSimple>>& getArtists() const;
    [[nodiscard]] const std::vector<std::string>& getAvailableMarkets() const;
    [[nodiscard]] int getDiscNumber() const;
    [[nodiscard]] int getDurationMs() const;
    [[nodiscard]] bool getIsExplicit() const;
    [[nodiscard]] const std::map<std::string, std::string>& getExternalUrls() const;
    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] bool isPlayable() const;
    [[nodiscard]] std::shared_ptr<TrackLink> getLinkedFrom() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getPreviewUrl() const;
    [[nodiscard]] int getTrackNumber() const;
    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] const std::string& getUri() const;

 private:
    std::vector<std::shared_ptr<ArtistSimple>> artists;
    std::vector<std::string> availableMarkets;
    int discNumber;
    int durationMs;
    bool isExplicit;
    std::map<std::string, std::string> externalUrls;
    std::string href;
    std::string id;
    bool playable;
    std::shared_ptr<TrackLink> linkedFrom;
    std::string name;
    std::string previewUrl;
    int trackNumber;
    std::string type;
    std::string uri;
};

#endif

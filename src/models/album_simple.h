#ifndef SPOTIFY_PLUSPLUS_ALBUMSIMPE_H
#define SPOTIFY_PLUSPLUS_ALBUMSIMPE_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "artist_simple.h"
#include "copyright.h"
#include "image.h"
#include "pager.h"

class AlbumSimple {
 public:
    explicit AlbumSimple(nlohmann::json albumJson);

    [[nodiscard]] const std::string& getAlbumType() const;
    [[nodiscard]] const std::vector<std::shared_ptr<ArtistSimple>>& getArtists() const;
    [[nodiscard]] const std::vector<std::string>& getAvailableMarkets() const;
    [[nodiscard]] const std::map<std::string, std::string>& getExternalUrls() const;
    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Image>>& getImages() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] const std::string& getUri() const;

 private:
    std::string albumType;
    std::vector<std::shared_ptr<ArtistSimple>> artists;
    std::vector<std::string> availableMarkets;
    std::map<std::string, std::string> externalUrls;
    std::string href;
    std::string id;
    std::vector<std::shared_ptr<Image>> images;
    std::string name;
    std::string type;
    std::string uri;
};

#endif

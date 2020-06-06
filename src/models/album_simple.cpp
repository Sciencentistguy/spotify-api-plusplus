#include "album_simple.h"

#include <memory>
namespace spotify {
    AlbumSimple::AlbumSimple(nlohmann::json albumJson) {
        albumType = albumJson["album_type"];
        for (const auto& json : albumJson["artists"])
            artists.push_back(std::make_shared<ArtistSimple>(json));
        for (const auto& market : albumJson["available_markets"])
            availableMarkets.push_back(market);
        for (auto it = albumJson["external_urls"].begin(); it != albumJson["external_urls"].end(); ++it)
            externalUrls[it.key()] = it.value();
        href = albumJson["href"];
        id = albumJson["id"];
        for (const auto& json : albumJson["images"])
            images.push_back(std::make_shared<Image>(json));
        name = albumJson["name"];
        type = albumJson["type"];
        uri = albumJson["uri"];
    }

    const std::string& AlbumSimple::getAlbumType() const {
        return albumType;
    }

    const std::vector<std::shared_ptr<ArtistSimple>>& AlbumSimple::getArtists() const {
        return artists;
    }

    const std::vector<std::string>& AlbumSimple::getAvailableMarkets() const {
        return availableMarkets;
    }

    const std::map<std::string, std::string>& AlbumSimple::getExternalUrls() const {
        return externalUrls;
    }

    const std::string& AlbumSimple::getHref() const {
        return href;
    }

    const std::string& AlbumSimple::getId() const {
        return id;
    }

    const std::vector<std::shared_ptr<Image>>& AlbumSimple::getImages() const {
        return images;
    }

    const std::string& AlbumSimple::getName() const {
        return name;
    }

    const std::string& AlbumSimple::getType() const {
        return type;
    }

    const std::string& AlbumSimple::getUri() const {
        return uri;
    }
}  // namespace spotify
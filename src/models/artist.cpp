#include "artist.h"

#include <memory>
namespace spotify {
    Artist::Artist(nlohmann::json artistJson) : ArtistSimple::ArtistSimple(artistJson) {
        followers = std::make_shared<Followers>(artistJson["followers"]);
        for (const auto& genre : artistJson["genres"])
            genres.push_back(genre);
        for (const auto& json : artistJson["images"])
            images.push_back(std::make_shared<Image>(json));
        popularity = artistJson["popularity"];
    }

    std::shared_ptr<Followers> Artist::getFollowers() const {
        return followers;
    }

    const std::vector<std::string>& Artist::getGenres() const {
        return genres;
    }

    const std::vector<std::shared_ptr<Image>>& Artist::getImages() const {
        return images;
    }

    int Artist::getPopularity() const {
        return popularity;
    }
}  // namespace spotify
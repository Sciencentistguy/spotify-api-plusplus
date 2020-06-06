#ifndef SPOTIFY_PLUSPLUS_ARTIST_H
#define SPOTIFY_PLUSPLUS_ARTIST_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "artist_simple.h"
#include "followers.h"
#include "image.h"
namespace spotify {
    class Artist : public ArtistSimple {
     public:
        explicit Artist(nlohmann::json artistJson);

        [[nodiscard]] std::shared_ptr<Followers> getFollowers() const;
        [[nodiscard]] const std::vector<std::string>& getGenres() const;
        [[nodiscard]] const std::vector<std::shared_ptr<Image>>& getImages() const;
        [[nodiscard]] int getPopularity() const;

     private:
        std::shared_ptr<Followers> followers;
        std::vector<std::string> genres;
        std::vector<std::shared_ptr<Image>> images;
        int popularity;
    };
}  // namespace spotify
#endif

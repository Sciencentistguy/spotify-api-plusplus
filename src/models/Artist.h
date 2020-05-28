#ifndef SPOTIFY_PLUSPLUS_ARTIST_H
#define SPOTIFY_PLUSPLUS_ARTIST_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "ArtistSimple.h"
#include "Followers.h"
#include "Image.h"

class Artist : public ArtistSimple {
 public:
    Artist(nlohmann::json artistJson);

    std::shared_ptr<Followers> GetFollowers() const;
    std::vector<std::string> GetGenres() const;
    std::vector<std::shared_ptr<Image>> GetImages() const;
    int GetPopularity() const;

 private:
    std::shared_ptr<Followers> followers;
    std::vector<std::string> genres;
    std::vector<std::shared_ptr<Image>> images;
    int popularity;
};

#endif

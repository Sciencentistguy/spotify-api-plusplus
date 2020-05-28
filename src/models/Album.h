#ifndef SPOTIFY_PLUSPLUS_ALBUM_H
#define SPOTIFY_PLUSPLUS_ALBUM_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "AlbumSimple.h"
#include "Artist.h"
#include "Copyright.h"
#include "Image.h"
#include "Pager.h"

class TrackSimple;

class Album : public AlbumSimple {
 public:
    explicit Album(nlohmann::json albumJson);
    ~Album();

    [[nodiscard]] const std::vector<std::shared_ptr<Copyright>>& getCopyrights() const;
    [[nodiscard]] const std::map<std::string, std::string>& getExternalIds() const;
    [[nodiscard]] const std::vector<std::string>& getGenres() const;
    [[nodiscard]] const std::string& getLabel() const;
    [[nodiscard]] int getPopularity() const;
    [[nodiscard]] const std::string& getReleaseDate() const;
    [[nodiscard]] const std::string& getReleaseDatePrecision() const;
    [[nodiscard]] const Pager<TrackSimple>& getTracks() const;

 private:
    std::vector<std::shared_ptr<Copyright>> copyrights;
    std::map<std::string, std::string> externalIds;
    std::vector<std::string> genres;
    std::string label;
    int popularity;
    std::string releaseDate;
    std::string releaseDatePrecision;
    Pager<TrackSimple> tracks;
};

#endif

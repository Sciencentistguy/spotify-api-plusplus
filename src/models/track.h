#ifndef SPOTIFY_PLUSPLUS_TRACK_H
#define SPOTIFY_PLUSPLUS_TRACK_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "album_simple.h"
#include "artist.h"
#include "track_link.h"
#include "track_simple.h"

namespace spotify {
    class Track : public TrackSimple {
     public:
        explicit Track(nlohmann::json trackJson);
        ~Track();

        [[nodiscard]] const std::shared_ptr<AlbumSimple>& getAlbum() const;
        [[nodiscard]] const std::map<std::string, std::string>& getExternalIds() const;
        [[nodiscard]] int getPopularity() const;

     private:
        std::shared_ptr<AlbumSimple> album;
        std::map<std::string, std::string> externalIds;
        int popularity;
    };
}  // namespace spotify
#endif

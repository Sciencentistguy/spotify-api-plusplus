#ifndef SPOTIFY_PLUSPLUS_IMAGE_H
#define SPOTIFY_PLUSPLUS_IMAGE_H

#include <string>

#include <nlohmann/json.hpp>
namespace spotify {
    class Image {
     public:
        explicit Image(nlohmann::json imageJson);

        [[nodiscard]] int getHeight() const;
        [[nodiscard]] const std::string& getUrl() const;
        [[nodiscard]] int getWidth() const;

     private:
        int height;
        std::string url;
        int width;
    };
}  // namespace spotify
#endif

#include "image.h"
namespace spotify {
    Image::Image(nlohmann::json imageJson) {
        if (!imageJson["height"].is_null())
            height = imageJson["height"];
        url = imageJson["url"];
        if (!imageJson["width"].is_null())
            width = imageJson["width"];
    }

    int Image::getHeight() const {
        return height;
    }

    const std::string& Image::getUrl() const {
        return url;
    }

    int Image::getWidth() const {
        return width;
    }
}  // namespace spotify
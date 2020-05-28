#ifndef SPOTIFY_PLUSPLUS_CATEGORY_H
#define SPOTIFY_PLUSPLUS_CATEGORY_H

#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Image.h"

class Category {
 public:
    explicit Category(nlohmann::json copyrightJson);

    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Image>>& getIcons() const;
    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] const std::string& getName() const;

 private:
    std::string href;
    std::vector<std::shared_ptr<Image>> icons;
    std::string id;
    std::string name;
};

#endif

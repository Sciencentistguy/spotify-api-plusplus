#ifndef SPOTIFY_PLUSPLUS_CATEGORY_H
#define SPOTIFY_PLUSPLUS_CATEGORY_H

#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Image.h"

class Category {
 public:
    Category(nlohmann::json copyrightJson);

    std::string GetHref() const;
    std::vector<std::shared_ptr<Image>> GetIcons() const;
    std::string GetId() const;
    std::string GetName() const;

 private:
    std::string href;
    std::vector<std::shared_ptr<Image>> icons;
    std::string id;
    std::string name;
};

#endif

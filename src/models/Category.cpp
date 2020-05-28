#include "Category.h"

#include <memory>

Category::Category(nlohmann::json categoryJson) {
    href = categoryJson["href"];
    for (const auto& json : categoryJson["icons"])
        icons.push_back(std::make_shared<Image>(json));
    id = categoryJson["id"];
    name = categoryJson["name"];
}

const std::string& Category::getHref() const {
    return href;
}

const std::vector<std::shared_ptr<Image>>& Category::getIcons() const {
    return icons;
}

const std::string& Category::getId() const {
    return id;
}

const std::string& Category::getName() const {
    return name;
}

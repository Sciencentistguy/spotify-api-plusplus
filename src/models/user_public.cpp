#include "user_public.h"

#include <memory>

UserPublic::UserPublic(nlohmann::json userJson) {
    if (!userJson["display_name"].is_null())
        displayName = userJson["display_name"];
    for (auto it = userJson["external_urls"].begin(); it != userJson["external_urls"].end(); ++it)
        externalUrls[it.key()] = it.value();
    followers = std::make_shared<Followers>(userJson["followers"]);
    href = userJson["href"];
    id = userJson["id"];
    for (const auto& json : userJson["images"])
        images.push_back(std::make_shared<Image>(json));
    type = userJson["type"];
    uri = userJson["uri"];
}

const std::string& UserPublic::getDisplayName() const {
    return displayName;
}

const std::map<std::string, std::string>& UserPublic::getExternalUrls() const {
    return externalUrls;
}

std::shared_ptr<Followers> UserPublic::getFollowers() const {
    return followers;
}

const std::string& UserPublic::getHref() const {
    return href;
}

const std::string& UserPublic::getId() const {
    return id;
}

const std::vector<std::shared_ptr<Image>>& UserPublic::getImages() const {
    return images;
}

const std::string& UserPublic::getType() const {
    return type;
}

const std::string& UserPublic::getUri() const {
    return uri;
}
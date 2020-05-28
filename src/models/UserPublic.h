#ifndef SPOTIFY_PLUSPLUS_USERPUBLIC_H
#define SPOTIFY_PLUSPLUS_USERPUBLIC_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Followers.h"
#include "Image.h"

class UserPublic {
 public:
    explicit UserPublic(nlohmann::json userJson);

    [[nodiscard]] const std::string& getDisplayName() const;
    [[nodiscard]] const std::map<std::string, std::string>& getExternalUrls() const;
    [[nodiscard]] std::shared_ptr<Followers> getFollowers() const;
    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Image>>& getImages() const;
    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] const std::string& getUri() const;

 private:
    std::string displayName;
    std::map<std::string, std::string> externalUrls;
    std::shared_ptr<Followers> followers;
    std::string href;
    std::string id;
    std::vector<std::shared_ptr<Image>> images;
    std::string type;
    std::string uri;
};

#endif

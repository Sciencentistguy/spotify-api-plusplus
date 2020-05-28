#ifndef SPOTIFY_PLUSPLUS_USER_H
#define SPOTIFY_PLUSPLUS_USER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Followers.h"
#include "Image.h"
#include "UserPublic.h"

class User : public UserPublic {
 public:
    explicit User(nlohmann::json userJson);

    [[nodiscard]] const std::string& getBirthdate() const;
    [[nodiscard]] const std::string& getCountry() const;
    [[nodiscard]] const std::string& getEmail() const;
    [[nodiscard]] const std::string& getProduct() const;

 private:
    std::string birthdate;
    std::string country;
    std::string email;
    std::string product;
};

#endif

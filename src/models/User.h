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
    User(nlohmann::json userJson);

    std::string GetBirthdate() const;
    std::string GetCountry() const;
    std::string GetEmail() const;
    std::string GetProduct() const;

 private:
    std::string birthdate;
    std::string country;
    std::string email;
    std::string product;
};

#endif

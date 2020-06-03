#include "user.h"

User::User(nlohmann::json userJson) : UserPublic::UserPublic(userJson) {
    birthdate = userJson["birthdate"];
    country = userJson["country"];
    email = userJson["email"];
    product = userJson["product"];
}

const std::string& User::getBirthdate() const {
    return birthdate;
}

const std::string& User::getCountry() const {
    return country;
}

const std::string& User::getEmail() const {
    return email;
}

const std::string& User::getProduct() const {
    return product;
}

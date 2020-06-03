#ifndef SPOTIFY_API_PLUSPLUS_CONTEXT_H
#define SPOTIFY_API_PLUSPLUS_CONTEXT_H

#include <nlohmann/json.hpp>

class Context {
 public:
    explicit Context(nlohmann::json contextJson);

    [[nodiscard]] const std::string& getUri() const;
    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::map<std::string, std::string>& getExternalUrls() const;
    [[nodiscard]] const std::string& getType() const;

 private:
    std::string uri;
    std::string href;
    std::map<std::string, std::string> externalUrls;
    std::string type;
};

#endif

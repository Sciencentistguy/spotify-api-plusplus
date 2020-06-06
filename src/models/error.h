#ifndef SPOTIFY_PLUSPLUS_ERROR_H
#define SPOTIFY_PLUSPLUS_ERROR_H

#include <string>

#include <nlohmann/json.hpp>
namespace spotify {
    class Error {
     public:
        Error(nlohmann::json pagerJson);

        [[nodiscard]] int getStatus() const;
        [[nodiscard]] const std::string& getMessage() const;

     private:
        int status;
        std::string message;
    };
}  // namespace spotify
#endif

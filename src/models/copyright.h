#ifndef SPOTIFY_PLUSPLUS_COPYRIGHT_H
#define SPOTIFY_PLUSPLUS_COPYRIGHT_H

#include <string>

#include <nlohmann/json.hpp>
namespace spotify {
    class Copyright {
     public:
        explicit Copyright(nlohmann::json copyrightJson);

        [[nodiscard]] const std::string& getText() const;
        [[nodiscard]] const std::string& getType() const;

     private:
        std::string text;
        std::string type;
    };
}
#endif

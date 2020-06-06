#ifndef SPOTIFY_API_PLUSPLUS_DEVICE_H
#define SPOTIFY_API_PLUSPLUS_DEVICE_H

#include <nlohmann/json.hpp>
namespace spotify {
    class Device {
     public:
        explicit Device(nlohmann::json deviceJson);

        [[nodiscard]] const std::string& getId() const;
        [[nodiscard]] bool isActive() const;
        [[nodiscard]] bool isRestricted() const;
        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] const std::string& getType() const;
        [[nodiscard]] int getVolumePercent() const;

     private:
        std::string id;
        bool active;
        bool restricted;
        std::string name;
        std::string type;
        int volumePercent;
    };
}  // namespace spotify

#endif

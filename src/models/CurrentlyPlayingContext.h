#ifndef SPOTIFY_API_PLUSPLUS_CURRENTLYPLAYINGCONTEXT_H
#define SPOTIFY_API_PLUSPLUS_CURRENTLYPLAYINGCONTEXT_H

#include <nlohmann/json.hpp>

#include "Context.h"
#include "Device.h"
#include "Track.h"

class CurrentlyPlayingContext {
 public:
    explicit CurrentlyPlayingContext(nlohmann::json currentlyPlayingJson);

    [[nodiscard]] const Device& getDevice() const;
    [[nodiscard]] const std::string& getRepeatState() const;
    [[nodiscard]] bool getShuffleState() const;
    [[nodiscard]] const Context& getContext() const;
    [[nodiscard]] int getTimestamp() const;
    [[nodiscard]] int getProgressMs() const;
    [[nodiscard]] bool getIsPlaying() const;
    [[nodiscard]] const Track& getItem() const;
    [[nodiscard]] bool isPlaying() const;

 private:
    Device device;
    std::string repeatState;
    bool shuffleState;
    Context context;
    int timestamp;
    int progressMs;
    bool playing;
    Track item;
};

#endif

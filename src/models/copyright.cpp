#include "copyright.h"
namespace spotify {
    Copyright::Copyright(nlohmann::json copyrightJson) {
        text = copyrightJson["text"];
        type = copyrightJson["type"];
    }

    const std::string& Copyright::getText() const {
        return text;
    }

    const std::string& Copyright::getType() const {
        return type;
    }
}  // namespace spotify
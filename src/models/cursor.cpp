#include "cursor.h"
namespace spotify {
    Cursor::Cursor(nlohmann::json cursorJson) {
        if (!cursorJson["after"].is_null())
            after = cursorJson["after"];
    }

    const std::string& Cursor::getAfter() const {
        return after;
    }
}  // namespace spotify
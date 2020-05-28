#include "Error.h"

Error::Error(nlohmann::json pagerJson) {
    status = pagerJson["status"];
    message = pagerJson["message"];
}

int Error::getStatus() const {
    return status;
}

const std::string& Error::getMessage() const {
    return message;
}
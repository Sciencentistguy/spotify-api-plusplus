#include "Context.h"
Context::Context(nlohmann::json contextJson) {
    uri = contextJson["uri"];
    href = contextJson["href"];
    for (auto it = contextJson["external_urls"].begin(); it != contextJson["external_urls"].end(); ++it)
        externalUrls[it.key()] = it.value();
    uri = contextJson["uri"];
    type = contextJson["type"];

}
const std::string& Context::getHref() const {
    return href;
}
const std::string& Context::getUri() const {
    return uri;
}
const std::map<std::string, std::string>& Context::getExternalUrls() const {
    return externalUrls;
}
const std::string& Context::getType() const {
    return type;
}

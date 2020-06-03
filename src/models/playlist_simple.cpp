#include "playlist_simple.h"

#include <memory>

PlaylistSimple::PlaylistSimple(nlohmann::json playlistJson) {
    collaborative = playlistJson["collaborative"];
    for (auto it = playlistJson["external_urls"].begin(); it != playlistJson["external_urls"].end(); ++it)
        externalUrls[it.key()] = it.value();
    href = playlistJson["href"];
    id = playlistJson["id"];
    for (const auto& json : playlistJson["images"])
        images.push_back(std::make_shared<Image>(json));
    name = playlistJson["name"];
    owner = std::make_shared<UserPublic>(playlistJson["owner"]);
    if (playlistJson["public"].is_null())
        isPublic = false;
    else
        isPublic = playlistJson["public"];
    snapshotId = playlistJson["snapshot_id"];
    tracks = Pager<PlaylistTrack>(playlistJson["tracks"]);
    type = playlistJson["type"];
    uri = playlistJson["uri"];
}

bool PlaylistSimple::isCollaborative() const {
    return collaborative;
}

const std::map<std::string, std::string>& PlaylistSimple::getExternalUrls() const {
    return externalUrls;
}

const std::string& PlaylistSimple::getHref() const {
    return href;
}

const std::string& PlaylistSimple::getId() const {
    return id;
}

const std::vector<std::shared_ptr<Image>>& PlaylistSimple::getImages() const {
    return images;
}

const std::string& PlaylistSimple::getName() const {
    return name;
}

const std::shared_ptr<UserPublic>& PlaylistSimple::getOwner() const {
    return owner;
}

bool PlaylistSimple::getIsPublic() const {
    return isPublic;
}

const std::string& PlaylistSimple::getSnapshotId() const {
    return snapshotId;
}

const Pager<PlaylistTrack>& PlaylistSimple::getTracks() const {
    return tracks;
}

const std::string& PlaylistSimple::getType() const {
    return type;
}

const std::string& PlaylistSimple::getUri() const {
    return uri;
}
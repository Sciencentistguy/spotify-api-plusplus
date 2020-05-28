#include "SpotifyAPI.h"

#include <iostream>
#include <memory>

#include <curl/curl.h>
#include <utils/CurlUtils.h>

SpotifyAPI::SpotifyAPI() {
    curl_global_init(CURL_GLOBAL_ALL);
}

void SpotifyAPI::setAuthToken(const std::string& token) {
    this->authToken = token;
}

std::shared_ptr<Album> SpotifyAPI::getAlbum(const std::string& albumId, const options_t& options) {
    return std::make_shared<Album>(spotifyGET("/v1/albums/" + albumId, options, authToken));
}

std::vector<std::shared_ptr<Album>> SpotifyAPI::getAlbums(const std::vector<std::string>& albumIds, const options_t& options) {
    std::vector<std::shared_ptr<Album>> albums;
    albums.reserve(albumIds.size());
    for (const auto& albumId : albumIds) {
        albums.push_back(getAlbum(albumId, options));
    }
    return albums;
}

Pager<TrackSimple> SpotifyAPI::getAlbumTracks(const std::string& albumId, const options_t& options) {
    return Pager<TrackSimple>(spotifyGET("/v1/albums/" + albumId + "/tracks", options, authToken));
}

std::shared_ptr<Artist> SpotifyAPI::getArtist(const std::string& artistId, const options_t& options) {
    return std::make_shared<Artist>(spotifyGET("/v1/artists/" + artistId, options, authToken));
}

std::vector<std::shared_ptr<Artist>> SpotifyAPI::getArtists(const std::vector<std::string>& artistIds, const options_t& options) {
    std::vector<std::shared_ptr<Artist>> artists;
    artists.reserve(artistIds.size());
    for (const auto& artistId : artistIds)
        artists.push_back(getArtist(artistId));
    return artists;
}

Pager<AlbumSimple> SpotifyAPI::getArtistAlbums(const std::string& artistId, const options_t& options) {
    return Pager<AlbumSimple>(spotifyGET("/v1/artists/" + artistId + "/albums", options, authToken));
}

std::vector<std::shared_ptr<Track>> SpotifyAPI::getArtistTopTracks(const std::string& artistId, const std::string& country, options_t options) {
    std::vector<std::shared_ptr<Track>> tracks;
    options["country"] = country;
    nlohmann::json json = spotifyGET("/v1/artists/" + artistId + "/top-tracks", options, authToken);
    for (const auto& trackJson : json["tracks"]) {
        tracks.push_back(std::make_shared<Track>(trackJson));
    }
    return tracks;
}

std::vector<std::shared_ptr<Artist>> SpotifyAPI::getArtistRelatedArtists(const std::string& artistId, const options_t& options) {
    std::vector<std::shared_ptr<Artist>> artists;
    nlohmann::json json = spotifyGET("/v1/artists/" + artistId + "/related-artists", options, authToken);
    for (const auto& artistJson : json["artists"])
        artists.push_back(std::make_shared<Artist>(artistJson));
    return artists;
}

std::shared_ptr<AudioFeatures> SpotifyAPI::getAudioFeatures(const std::string& trackId, const options_t& options) {
    return std::make_shared<AudioFeatures>(spotifyGET("/v1/audio-features/" + trackId, options, authToken));
}

std::vector<std::shared_ptr<AudioFeatures>> SpotifyAPI::getAudioFeatures(const std::vector<std::string>& trackIds, const options_t& options) {
    std::vector<std::shared_ptr<AudioFeatures>> audioFeatures;
    audioFeatures.reserve(trackIds.size());
    for (const std::string& trackId : trackIds)
        audioFeatures.push_back(getAudioFeatures(trackId, options));
    return audioFeatures;
}

Pager<PlaylistSimple> SpotifyAPI::getFeaturedPlaylists(const options_t& options) {
    // TODO Add access to message variable
    return Pager<PlaylistSimple>(spotifyGET("/v1/browse/featured-playlists", options, authToken)["playlists"]);
}

Pager<AlbumSimple> SpotifyAPI::getNewReleases(const options_t& options) {
    return Pager<AlbumSimple>(spotifyGET("/v1/browse/new-releases", options, authToken)["albums"]);
}

Pager<Category> SpotifyAPI::getCategories(const options_t& options) {
    return Pager<Category>(spotifyGET("/v1/browse/categories", options, authToken)["categories"]);
}

std::shared_ptr<Category> SpotifyAPI::getCategory(const std::string& categoryId, const options_t& options) {
    return std::make_shared<Category>(spotifyGET("/v1/browse/categories/" + categoryId, options, authToken));
}

Pager<PlaylistSimple> SpotifyAPI::getCategoryPlaylists(const std::string& categoryId, const options_t& options) {
    return Pager<PlaylistSimple>(spotifyGET("/v1/browse/categories/" + categoryId + "/playlists", options, authToken)["playlists"]);
}

std::shared_ptr<User> SpotifyAPI::getMe(const options_t& options) {
    return std::make_shared<User>(spotifyGET("/v1/me", options, authToken));
}

CursorPager<Artist> SpotifyAPI::getMyFollowedArtists(options_t options) {
    options["type"] = "artist";
    return CursorPager<Artist>(spotifyGET("/v1/me/following", options, authToken)["artists"]);
}

void SpotifyAPI::followArtist(const std::string& artistId, options_t options) {
    options["type"] = "artist";
    options["ids"] = artistId;
    spotifyPUT("/v1/me/following", options, authToken);
}

void SpotifyAPI::followUser(const std::string& userId, options_t options) {
    options["type"] = "user";
    options["ids"] = userId;
    spotifyPUT("/v1/me/following", options, authToken);
}

void SpotifyAPI::unfollowArtist(const std ::string& artistId, options_t options) {
    options["type"] = "artist";
    options["ids"] = artistId;
    spotifyDELETE("/v1/me/following", options, authToken);
}

void SpotifyAPI::unfollowUser(const std::string& userId, options_t options) {
    options["type"] = "user";
    options["ids"] = userId;
    spotifyDELETE("/v1/me/following", options, authToken);
}

bool SpotifyAPI::checkFollowingArtist(const std::string& artistId, options_t options) {
    options["type"] = "artist";
    options["ids"] = artistId;
    return spotifyGET("/v1/me/following/contains", options, authToken)[0];
}

bool SpotifyAPI::checkFollowingUser(const std::string& userId, options_t options) {
    options["type"] = "user";
    options["ids"] = userId;
    return spotifyGET("/v1/me/following/contains", options, authToken)[0];
}

void SpotifyAPI::followPlaylist(const std::string& ownerId, const std::string& playlistId, const options_t& options) {
    spotifyPUT("/v1/users/" + ownerId + "/playlists/" + playlistId + "/followers", options, authToken);
}

void SpotifyAPI::unfollowPlaylist(const std::string& ownerId, const std::string& playlistId, const options_t& options) {
    spotifyDELETE("/v1/users/" + ownerId + "/playlists/" + playlistId + "/followers", options, authToken);
}

void SpotifyAPI::saveTracks(const std::vector<std::string>& trackIds, options_t options) {
    options["ids"] = vectorJoin(trackIds);
    spotifyPUT("/v1/me/tracks", options, authToken);
}

Pager<SavedTrack> SpotifyAPI::getMySavedTracks(const options_t& options) {
    return Pager<SavedTrack>(spotifyGET("/v1/me/tracks", options, authToken));
}

void SpotifyAPI::removeSavedTracks(const std::vector<std::string>& trackIds, options_t options) {
    options["ids"] = vectorJoin(trackIds);
    spotifyDELETE("/v1/me/tracks", options, authToken);
}

bool SpotifyAPI::checkSavedTracks(const std::vector<std::string>& trackIds, options_t options) {
    options["ids"] = vectorJoin(trackIds);
    return spotifyGET("/v1/me/tracks/contains", options, authToken)[0];
}

void SpotifyAPI::saveAlbums(const std::vector<std::string>& albumIds, options_t options) {
    options["ids"] = vectorJoin(albumIds);
    spotifyPUT("/v1/me/albums", options, authToken);
}

Pager<SavedAlbum> SpotifyAPI::getMySavedAlbums(const options_t& options) {
    return Pager<SavedAlbum>(spotifyGET("/v1/me/albums", options, authToken));
}

void SpotifyAPI::removeSavedAlbums(const std::vector<std::string>& albumIds, options_t options) {
    options["ids"] = vectorJoin(albumIds);
    spotifyDELETE("/v1/me/albums", options, authToken);
}

bool SpotifyAPI::checkSavedAlbums(const std::vector<std::string>& albumIds, options_t options) {
    options["ids"] = vectorJoin(albumIds);
    return spotifyGET("/v1/me/albums/contains", options, authToken)[0];
}

Pager<Artist> SpotifyAPI::getMyTopArtists(const options_t& options) {
    return Pager<Artist>(spotifyGET("/v1/me/top/artists", options, authToken));
}

Pager<Track> SpotifyAPI::getMyTopTracks(const options_t& options) {
    return Pager<Track>(spotifyGET("/v1/me/top/tracks", options, authToken));
}

Recommendations SpotifyAPI::getRecommendations(const options_t& options) {
    return Recommendations(spotifyGET("/v1/recommendations", options, authToken));
}

Pager<AlbumSimple> SpotifyAPI::searchAlbums(const std::string& query, options_t options) {
    options["type"] = "album";
    options["q"] = query;
    return Pager<AlbumSimple>(spotifyGET("/v1/search", options, authToken)["albums"]);
}

Pager<Artist> SpotifyAPI::searchArtists(const std::string& query, options_t options) {
    options["type"] = "artist";
    options["q"] = query;
    return Pager<Artist>(spotifyGET("/v1/search", options, authToken)["artists"]);
}

Pager<PlaylistSimple> SpotifyAPI::searchPlaylists(const std::string& query, options_t options) {
    options["type"] = "playlist";
    options["q"] = query;
    return Pager<PlaylistSimple>(spotifyGET("/v1/search", options, authToken)["playlists"]);
}

Pager<Track> SpotifyAPI::searchTracks(const std::string& query, options_t options) {
    options["type"] = "track";
    options["q"] = query;
    return Pager<Track>(spotifyGET("/v1/search", options, authToken)["tracks"]);
}

std::shared_ptr<Track> SpotifyAPI::getTrack(const std::string& trackId, const options_t& options) {
    return std::make_shared<Track>(spotifyGET("/v1/tracks/" + trackId, options, authToken));
}

std::vector<std::shared_ptr<Track>> SpotifyAPI::getTracks(const std::vector<std::string>& trackIds, const options_t& options) {
    std::vector<std::shared_ptr<Track>> tracks;
    tracks.reserve(trackIds.size());
    for (const auto& trackId : trackIds)
        tracks.push_back(getTrack(trackId, options));
    return tracks;
}

std::shared_ptr<UserPublic> SpotifyAPI::getUser(const std::string& userId, const options_t& options) {
    return std::make_shared<UserPublic>(spotifyGET("/v1/users/" + userId, options, authToken));
}

Pager<PlaylistSimple> SpotifyAPI::getUserPlaylists(const std::string& userId, const options_t& options) {
    return Pager<PlaylistSimple>(spotifyGET("/v1/users/" + userId + "/playlists", options, authToken));
}

Pager<PlaylistSimple> SpotifyAPI::getMyPlaylists(const options_t& options) {
    return Pager<PlaylistSimple>(spotifyGET("/v1/me/playlists", options, authToken));
}

std::shared_ptr<Playlist> SpotifyAPI::getPlaylist(const std::string& userId, const std::string& playlistId, const options_t& options) {
    return std::make_shared<Playlist>(spotifyGET("/v1/users/" + userId + "/playlists/" + playlistId, options, authToken));
}

Pager<PlaylistTrack> SpotifyAPI::getPlaylistTracks(const std::string& userId, const std::string& playlistId, const options_t& options) {
    return Pager<PlaylistTrack>(spotifyGET("/v1/users/" + userId + "/playlists/" + playlistId + "/tracks", options, authToken));
}

std::shared_ptr<Playlist> SpotifyAPI::createPlaylist(const std::string& userId, const std::string& name, const options_t& options) {
    nlohmann::json bodyJson;
    bodyJson["name"] = name;
    for (auto option : options)
        bodyJson[option.first] = option.second;

    return std::make_shared<Playlist>(spotifyPOST("/v1/users/" + userId + "/playlists", options_t(), authToken, bodyJson.dump(4)));
}

void SpotifyAPI::editPlaylist(const std::string& userId, const std::string& playlistId, const options_t& options) {
    nlohmann::json bodyJson;
    for (const auto& option : options)
        bodyJson[option.first] = option.second;

    spotifyPUT("/v1/users/" + userId + "/playlists/" + playlistId, options_t(), authToken, bodyJson.dump(4));
}

void SpotifyAPI::addTracksToPlaylist(const std::string& userId, const std::string& playlistId, const std::vector<std::string>& trackUris, options_t options) {
    options["uris"] = vectorJoin(trackUris);
    spotifyPOST("/v1/users/" + userId + "/playlists/" + playlistId + "/tracks", options, authToken);
}

void SpotifyAPI::removeTracksFromPlaylist(const std::string& userId, const std::string& playlistId, const std::vector<std::string>& trackUris,
                                          std::string snapshotId) {
    nlohmann::json bodyJson;
    for (std::string trackId : trackUris) {
        nlohmann::json uriJson;
        uriJson["uri"] = trackId;
        bodyJson["tracks"].push_back(uriJson);
    }
    if (!snapshotId.empty())
        bodyJson["snapshot_id"] = snapshotId;

    spotifyDELETE("/v1/users/" + userId + "/playlists/" + playlistId + "/tracks", options_t(), authToken, bodyJson.dump(4));
}

void SpotifyAPI::removeTracksFromPlaylist(const std::string& userId, const std::string& playlistId,
                                          const std::map<std::string, std::vector<int>>& trackUrisToPositions, std::string snapshotId) {
    nlohmann::json bodyJson;
    for (const auto& trackIdToPositions : trackUrisToPositions) {
        nlohmann::json uriJson;
        uriJson["uri"] = trackIdToPositions.first;
        for (int position : trackIdToPositions.second)
            uriJson["positions"].push_back(position);
        bodyJson["tracks"].push_back(uriJson);
    }
    if (!snapshotId.empty())
        bodyJson["snapshot_id"] = snapshotId;

    spotifyDELETE("/v1/users/" + userId + "/playlists/" + playlistId + "/tracks", options_t(), authToken, bodyJson.dump(4));
}

void SpotifyAPI::removeTracksFromPlaylist(const std::string& userId, const std::string& playlistId, const std::vector<int>& positions,
                                          const std::string& snapshotId) {
    nlohmann::json bodyJson;
    for (int position : positions)
        bodyJson["positions"].push_back(position);
    bodyJson["snapshot_id"] = snapshotId;

    spotifyDELETE("/v1/users/" + userId + "/playlists/" + playlistId + "/tracks", options_t(), authToken, bodyJson.dump(4));
}

void SpotifyAPI::reorderPlaylistTracks(const std::string& userId, const std::string& playlistId, const int rangeStart, const int insertBefore, const options_t& options) {
    nlohmann::json bodyJson;
    bodyJson["range_start"] = rangeStart;
    bodyJson["insert_before"] = insertBefore;
    for (auto option : options)
        bodyJson[option.first] = option.second;

    spotifyPUT("/v1/users/" + userId + "/playlists/" + playlistId + "/tracks", options_t(), authToken, bodyJson.dump(4));
}

void SpotifyAPI::replacePlaylistTracks(const std::string& userId, const std::string& playlistId, const std::vector<std::string>& trackUris, options_t options) {
    options["uris"] = vectorJoin(trackUris);
    spotifyPUT("/v1/users/" + userId + "/playlists/" + playlistId + "/tracks", options, authToken);
}

bool SpotifyAPI::checkUserFollowingPlaylist(const std::string& userId, const std::string& playlistId, const std::vector<std::string>& userIds, options_t options) {
    // TODO Support multiple users
    options["ids"] = vectorJoin(userIds);
    return spotifyGET("/v1/users/" + userId + "/playlists/" + playlistId + "/followers/contains", options, authToken)[0];
}

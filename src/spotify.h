#ifndef SPOTIFY_PLUSPLUS_SPOTIFYSERVICE_H
#define SPOTIFY_PLUSPLUS_SPOTIFYSERVICE_H

#include <string>

#include "models/album.h"
#include "models/audio_features.h"
#include "models/category.h"
#include "models/currently_playing_context.h"
#include "models/currently_playing_track.h"
#include "models/cursor_pager.h"
#include "models/device.h"
#include "models/play_history_object.h"
#include "models/playlist.h"
#include "models/recommendations.h"
#include "models/saved_album.h"
#include "models/saved_track.h"
#include "models/track.h"

typedef std::map<std::string, std::string> options_t;
class Spotify {
 public:
    Spotify();

    void setAuthToken(const std::string& token);

    std::shared_ptr<Album> getAlbum(const std::string& albumId, const options_t& options = options_t());

    std::vector<std::shared_ptr<Album>> getAlbums(const std::vector<std::string>& albumIds, const options_t& options = options_t());

    Pager<TrackSimple> getAlbumTracks(const std::string& albumId, const options_t& options = options_t());

    std::shared_ptr<Artist> getArtist(const std::string& artistId, const options_t& options = options_t());

    std::vector<std::shared_ptr<Artist>> getArtists(const std::vector<std::string>& artistIds, const options_t& options = options_t());

    Pager<AlbumSimple> getArtistAlbums(const std::string& artistId, const options_t& options = options_t());

    std::vector<std::shared_ptr<Track>> getArtistTopTracks(const std::string& artistId, const std::string& country, options_t options = options_t());

    std::vector<std::shared_ptr<Artist>> getArtistRelatedArtists(const std::string& artistId, const options_t& options = options_t());

    std::shared_ptr<AudioFeatures> getAudioFeatures(const std::string& trackId, const options_t& options = options_t());

    std::vector<std::shared_ptr<AudioFeatures>> getAudioFeatures(const std::vector<std::string>& trackIds, const options_t& options = options_t());

    Pager<PlaylistSimple> getFeaturedPlaylists(const options_t& options = options_t());

    Pager<AlbumSimple> getNewReleases(const options_t& options = options_t());

    Pager<Category> getCategories(const options_t& options = options_t());

    std::shared_ptr<Category> getCategory(const std::string& categoryId, const options_t& options = options_t());

    Pager<PlaylistSimple> getCategoryPlaylists(const std::string& categoryId, const options_t& options = options_t());

    std::shared_ptr<User> getMe(const options_t& options = options_t());

    CursorPager<Artist> getMyFollowedArtists(options_t options = options_t());

    void followArtist(const std::string& artistId, options_t options = options_t());

    void followUser(const std::string& userId, options_t options = options_t());

    void unfollowArtist(const std::string& artistId, options_t options = options_t());

    void unfollowUser(const std::string& userId, options_t options = options_t());

    bool checkFollowingArtist(const std::string& artistId, options_t options = options_t());

    bool checkFollowingUser(const std::string& userId, options_t options = options_t());

    void followPlaylist(const std::string& ownerId, const std::string& playlistId, const options_t& options = options_t());

    void unfollowPlaylist(const std::string& ownerId, const std::string& playlistId, const options_t& options = options_t());

    void saveTracks(const std::vector<std::string>& trackIds, options_t options = options_t());

    Pager<SavedTrack> getMySavedTracks(const options_t& options = options_t());

    void removeSavedTracks(const std::vector<std::string>& trackIds, options_t options = options_t());

    bool checkSavedTracks(const std::vector<std::string>& trackIds, options_t options = options_t());

    void saveAlbums(const std::vector<std::string>& albumIds, options_t options = options_t());

    Pager<SavedAlbum> getMySavedAlbums(const options_t& options = options_t());

    void removeSavedAlbums(const std::vector<std::string>& albumIds, options_t options = options_t());

    bool checkSavedAlbums(const std::vector<std::string>& albumIds, options_t options = options_t());

    Pager<Artist> getMyTopArtists(const options_t& options = options_t());

    Pager<Track> getMyTopTracks(const options_t& options = options_t());

    Recommendations getRecommendations(const options_t& options = options_t());

    Pager<AlbumSimple> searchAlbums(const std::string& query, options_t options = options_t());

    Pager<Artist> searchArtists(const std::string& query, options_t options = options_t());

    Pager<PlaylistSimple> searchPlaylists(const std::string& query, options_t options = options_t());

    Pager<Track> searchTracks(const std::string& query, options_t options = options_t());

    std::shared_ptr<Track> getTrack(const std::string& trackId, const options_t& options = options_t());

    std::vector<std::shared_ptr<Track>> getTracks(const std::vector<std::string>& trackIds, const options_t& options = options_t());

    std::shared_ptr<UserPublic> getUser(const std::string& userId, const options_t& options = options_t());

    Pager<PlaylistSimple> getUserPlaylists(const std::string& userId, const options_t& options = options_t());

    Pager<PlaylistSimple> getMyPlaylists(const options_t& options = options_t());

    std::shared_ptr<Playlist> getPlaylist(const std::string& userId, const std::string& playlistId, const options_t& options = options_t());
    std::shared_ptr<Playlist> getPlaylist(const std::string& playlistId, const options_t& options = options_t());

    Pager<PlaylistTrack> getPlaylistTracks(const std::string& userId, const std::string& playlistId, const options_t& options = options_t());

    std::shared_ptr<Playlist> createPlaylist(const std::string& userId, const std::string& name, const options_t& options = options_t());

    void editPlaylist(const std::string& userId, const std::string& playlistId, const options_t& options = options_t());

    void addTracksToPlaylist(const std::string& userId, const std::string& playlistId, const std::vector<std::string>& trackUris,
                             options_t options = options_t());

    void removeTracksFromPlaylist(const std::string& userId, const std::string& playlistId, const std::vector<std::string>& trackUris,
                                  std::string snapshotId = "");

    void removeTracksFromPlaylist(const std::string& userId, const std::string& playlistId,
                                  const std::map<std::string, std::vector<int>>& trackUrisToPositions, std::string snapshotId = "");

    void removeTracksFromPlaylist(const std::string& userId, const std::string& playlistId, const std::vector<int>& positions, const std::string& snapshotId);

    void reorderPlaylistTracks(const std::string& userId, const std::string& playlistId, int rangeStart, int insertBefore,
                               const options_t& options = options_t());

    void replacePlaylistTracks(const std::string& userId, const std::string& playlistId, const std::vector<std::string>& trackUris,
                               options_t options = options_t());

    bool checkUserFollowingPlaylist(const std::string& userId, const std::string& playlistId, const std::vector<std::string>& userIds,
                                    options_t options = options_t());

    void uploadCustomPlaylistCover(std::string userId, std::string playlistId, std::string contentType, std::string image, options_t options = options_t());

    CursorPager<PlayHistoryObject> getMyRecentlyPlayed(options_t options = options_t());

    std::vector<std::shared_ptr<Device>> getMyDevices(options_t options = options_t());

    std::shared_ptr<CurrentlyPlayingContext> getMyCurrentPlayback(options_t options = options_t());

    std::shared_ptr<CurrentlyPlayingTrack> getMyCurrentPlayingTrack(options_t options = options_t());

    void transferMyPlayback(std::string deviceId, options_t options = options_t());

    void resume(options_t options = options_t());

    void pause(options_t options = options_t());

    void skipToNext(options_t options = options_t());

    void skipToPrevious(options_t options = options_t());

    void setRepeat(std::string state, options_t options = options_t());

    void setVolume(int volumePercent, options_t options = options_t());

    void toggleShuffle(bool state, options_t options = options_t());

 private:
    std::string authToken;
};

#endif

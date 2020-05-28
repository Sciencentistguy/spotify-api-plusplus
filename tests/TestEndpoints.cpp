#include <fstream>

#include "SpotifyAPI.h"

#include <curl/curl.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utils/CurlUtils.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"
class TestEndpoints : public ::testing::Test {
 protected:
    static SpotifyAPI sharedApi;
    SpotifyAPI api;
    void SetUp() override {
        api = TestEndpoints::sharedApi;
    }

    static void setUpTestCase() {
        sharedApi = SpotifyAPI();

        std::string refreshToken = getStringFromFile("../refresh_token.txt");
        std::string clientId = getStringFromFile("../client_id.txt");
        std::string clientSecret = getStringFromFile("../client_secret.txt");

        CURL* curl;
        curl = curl_easy_init();
        if (!curl) {
            std::cerr << "Could not initiate cURL" << std::endl;
            return;
        }

        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl, CURLOPT_URL, "https://accounts.spotify.com/api/token");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);  // Can't authenticate the certificate, so disable authentication.
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        std::string postData = "grant_type=refresh_token&client_id=" + clientId + "&client_secret=" + clientSecret;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        int rc = curl_easy_perform(curl);
        if (rc != CURLE_OK)
            throw CurlException(rc);
        curl_easy_cleanup(curl);

        nlohmann::json json = nlohmann::json::parse(readBuffer);
        std::string accessToken = json["access_token"];

        std::cout << accessToken << std::endl;

        sharedApi.setAuthToken(accessToken);
    }

 private:
    static std::string getStringFromFile(const std::string& fileName) {
        std::stringstream buffer;
        std::ifstream file(fileName);
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
};
SpotifyAPI TestEndpoints::sharedApi;

TEST_F(TestEndpoints, GetAlbumTest) {
    std::shared_ptr<Album> album = api.getAlbum("0sNOF9WDwhWunNAHPD3Baj");
    ASSERT_STREQ(album->getName().c_str(), "She's So Unusual");
}

TEST_F(TestEndpoints, GetAlbumsTest) {
    std::vector<std::shared_ptr<Album>> albums = api.getAlbums({"41MnTivkwTO3UUJ8DrqEJJ", "6JWc4iAiJ9FjyK0B59ABb4", "6UXCm6bOO4gFlDQZV5yL37"});
    ASSERT_THAT(albums, testing::ElementsAre(
                            testing::Property(&std::shared_ptr<Album>::operator*,
                                              testing::Property(&Album::getName, testing::StrEq("The Best Of Keane (Deluxe Edition)"))),
                            testing::Property(&std::shared_ptr<Album>::operator*, testing::Property(&Album::getName, testing::StrEq("Strangeland"))),
                            testing::Property(&std::shared_ptr<Album>::operator*, testing::Property(&Album::getName, testing::StrEq("Night Train")))));
}

TEST_F(TestEndpoints, GetAlbumTracksTest) {
    Pager<TrackSimple> tracks = api.getAlbumTracks("6akEvsycLGftJxYudPjmqK");
    ASSERT_STREQ(tracks.getItems()[0].getName().c_str(), "All I Want");
    ASSERT_EQ(tracks.getTotal(), 11);
}

TEST_F(TestEndpoints, GetArtistTest) {
    std::shared_ptr<Artist> artist = api.getArtist("0OdUWJ0sBjDrqHygGUXeCF");
    ASSERT_STREQ(artist->getName().c_str(), "Band of Horses");
}

TEST_F(TestEndpoints, GetArtistsTest) {
    std::vector<std::shared_ptr<Artist>> artists = api.getArtists({"0oSGxfWSnnOXhD2fKuz2Gy", "3dBVyJ7JuOMt4GE9607Qin"});
    ASSERT_THAT(artists, testing::ElementsAre(
                             testing::Property(&std::shared_ptr<Artist>::operator*, testing::Property(&Artist::getName, testing::StrEq("David Bowie"))),
                             testing::Property(&std::shared_ptr<Artist>::operator*, testing::Property(&Artist::getName, testing::StrEq("T. Rex")))));
}

TEST_F(TestEndpoints, GetArtistAlbumsTest) {
    Pager<AlbumSimple> albums = api.getArtistAlbums("1vCWHaC5f2uS3yhpwWbIA6");
    ASSERT_THAT(albums.getItems(),
                testing::Contains(testing::Property(&AlbumSimple::getName, testing::StrEq("Taste The Feeling (Avicii Vs. Conrad Sewell)"))));
}

TEST_F(TestEndpoints, GetArtistTopTracksTest) {
    std::vector<std::shared_ptr<Track>> tracks = api.getArtistTopTracks("43ZHCT0cAZBISjO8DG9PnE", "US");
    // An artist's top tracks change over time, so we can't test specific tracks.
    // If the function doesn't return an error, and 10 tracks are returned, the function is probably working as intended
    ASSERT_EQ(tracks.size(), 10);
}

TEST_F(TestEndpoints, GetArtistRelatedArtistsTest) {
    std::vector<std::shared_ptr<Artist>> artists = api.getArtistRelatedArtists("43ZHCT0cAZBISjO8DG9PnE");
    // Similar to the above test, related artists change, so just test the number of artists returned
    ASSERT_EQ(artists.size(), 20);
}

TEST_F(TestEndpoints, GetAudioFeaturesTest) {
    std::shared_ptr<AudioFeatures> features = api.getAudioFeatures("06AKEBrKUckW0KREUWRnvT");
    ASSERT_FLOAT_EQ(features->getDanceability(), 0.735);
    ASSERT_EQ(features->getDurationMs(), 255349);
}

TEST_F(TestEndpoints, GetAudioFeaturesTest2) {
    std::vector<std::shared_ptr<AudioFeatures>> features =
        api.getAudioFeatures((std::vector<std::string>){"06AKEBrKUckW0KREUWRnvT", "2NRANZE9UCmPAS5XVbXL40"});
    ASSERT_EQ(features[0]->getDurationMs(), 255349);
    ASSERT_EQ(features[1]->getDurationMs(), 187800);
}

TEST_F(TestEndpoints, GetFeaturedPlaylistsTest) {
    Pager<PlaylistSimple> playlists = api.getFeaturedPlaylists();
    ASSERT_EQ(playlists.getLimit(), 20);
}

TEST_F(TestEndpoints, GetNewReleasesTest) {
    Pager<AlbumSimple> albums = api.getNewReleases();
    ASSERT_EQ(albums.getLimit(), 20);
}

TEST_F(TestEndpoints, GetCategoriesTest) {
    Pager<Category> categories = api.getCategories();
    ASSERT_EQ(categories.getLimit(), 20);
}

TEST_F(TestEndpoints, GetCategoryTest) {
    std::shared_ptr<Category> category = api.getCategory("party");
    ASSERT_STREQ(category->getName().c_str(), "Party");
}

TEST_F(TestEndpoints, GetCategoryPlaylistsTest) {
    Pager<PlaylistSimple> playlists = api.getCategoryPlaylists("party");
    ASSERT_EQ(playlists.getLimit(), 20);
}

TEST_F(TestEndpoints, GetMeTest) {
    std::shared_ptr<User> me = api.getMe();
    ASSERT_STREQ(me->getType().c_str(), "user");
}

TEST_F(TestEndpoints, MyFollowedArtistsTest) {
    // Follow Band of Horses and check to make sure that MyFollowedArtists contains it
    api.followArtist("0OdUWJ0sBjDrqHygGUXeCF");
    std::vector<Artist> followed = api.getMyFollowedArtists().getItems();
    ASSERT_THAT(followed, testing::Contains(testing::Property(&Artist::getName, testing::StrEq("Band of Horses"))));
    ASSERT_TRUE(api.checkFollowingArtist("0OdUWJ0sBjDrqHygGUXeCF"));

    // Unfollow Band of Horses and check to make sure that MyFollowedArtists no longer contains it
    api.unfollowArtist("0OdUWJ0sBjDrqHygGUXeCF");
    followed = api.getMyFollowedArtists().getItems();
    ASSERT_THAT(followed, testing::Not(testing::Contains(testing::Property(&Artist::getName, testing::StrEq("Band of Horses")))));
    ASSERT_FALSE(api.checkFollowingArtist("0OdUWJ0sBjDrqHygGUXeCF"));
}

TEST_F(TestEndpoints, MyFollowedUsersTest) {
    api.followUser("exampleuser01");
    ASSERT_TRUE(api.checkFollowingUser("exampleuser01"));

    api.unfollowUser("exampleuser01");
    ASSERT_FALSE(api.checkFollowingUser("exampleuser01"));
}

TEST_F(TestEndpoints, MyFollowedPlaylistsTest) {
    api.followPlaylist("jmperezperez", "2v3iNvBX8Ay1Gt2uXtUKUT");
    ASSERT_TRUE(api.checkUserFollowingPlaylist("jmperezperez", "2v3iNvBX8Ay1Gt2uXtUKUT", {api.getMe()->getId()}));

    api.unfollowPlaylist("jmperezperez", "2v3iNvBX8Ay1Gt2uXtUKUT");
    ASSERT_FALSE(api.checkUserFollowingPlaylist("jmperezperez", "2v3iNvBX8Ay1Gt2uXtUKUT", {api.getMe()->getId()}));
}

TEST_F(TestEndpoints, MySavedTracksTest) {
    api.saveTracks({"3n3Ppam7vgaVa1iaRUc9Lp"});
    Pager<SavedTrack> tracks = api.getMySavedTracks();
    ASSERT_THAT(tracks.getItems(),
                testing::Contains(testing::Property(&SavedTrack::getTrack, testing::Property(&std::shared_ptr<Track>::operator*, testing::Property(
                                                                                                 &Track::getName, testing::StrEq("Mr. Brightside"))))));
    ASSERT_TRUE(api.checkSavedTracks({"3n3Ppam7vgaVa1iaRUc9Lp"}));

    api.removeSavedTracks({"3n3Ppam7vgaVa1iaRUc9Lp"});
    tracks = api.getMySavedTracks();
    ASSERT_THAT(tracks.getItems(), testing::Not(testing::Contains(testing::Property(
                                       &SavedTrack::getTrack, testing::Property(&std::shared_ptr<Track>::operator*,
                                                                                testing::Property(&Track::getName, testing::StrEq("Mr. Brightside")))))));
    ASSERT_FALSE(api.checkSavedTracks({"3n3Ppam7vgaVa1iaRUc9Lp"}));
}

TEST_F(TestEndpoints, MySavedAlbumsTest) {
    api.saveAlbums({"0sNOF9WDwhWunNAHPD3Baj"});
    Pager<SavedAlbum> albums = api.getMySavedAlbums();
    ASSERT_THAT(albums.getItems(),
                testing::Contains(testing::Property(&SavedAlbum::getAlbum, testing::Property(&std::shared_ptr<Album>::operator*, testing::Property(
                                                                                                 &Album::getName, testing::StrEq("She's So Unusual"))))));
    ASSERT_TRUE(api.checkSavedAlbums({"0sNOF9WDwhWunNAHPD3Baj"}));

    api.removeSavedAlbums({"0sNOF9WDwhWunNAHPD3Baj"});
    albums = api.getMySavedAlbums();
    ASSERT_THAT(albums.getItems(), testing::Not(testing::Contains(testing::Property(
                                       &SavedAlbum::getAlbum, testing::Property(&std::shared_ptr<Album>::operator*,
                                                                                testing::Property(&Album::getName, testing::StrEq("She's So Unusual")))))));
    ASSERT_FALSE(api.checkSavedAlbums({"0sNOF9WDwhWunNAHPD3Baj"}));
}

TEST_F(TestEndpoints, MyTopArtistsTest) {
    Pager<Artist> artists = api.getMyTopArtists();
    ASSERT_EQ(artists.getLimit(), 20);
}

TEST_F(TestEndpoints, MyTopTracksTest) {
    Pager<Track> tracks = api.getMyTopTracks();
    ASSERT_EQ(tracks.getLimit(), 20);
}

TEST_F(TestEndpoints, RecommendationsTest) {
    std::map<std::string, std::string> options;
    options["seed_artists"] = "4NHQUGzhtTLFvgF5SZesLK";
    options["seed_tracks"] = "0c6xIDDpzE81m2q797ordA";
    options["min_energy"] = "0.4";
    options["min_popularity"] = "50";
    options["market"] = "US";

    Recommendations recommendations = api.getRecommendations(options);
    ASSERT_EQ(recommendations.getTracks().size(), 20);
}

TEST_F(TestEndpoints, SearchAlbumsTest) {
    Pager<AlbumSimple> albums = api.searchAlbums("Adventure");

    ASSERT_THAT(albums.getItems(), testing::Contains(testing::Property(&AlbumSimple::getName, testing::StrEq("Adventure (Deluxe)"))));
}

TEST_F(TestEndpoints, SearchArtistsTest) {
    Pager<Artist> artists = api.searchArtists("Killers");

    ASSERT_THAT(artists.getItems(), testing::Contains(testing::Property(&ArtistSimple::getName, testing::StrEq("The Killers"))));
}

TEST_F(TestEndpoints, SearchPlaylistsTest) {
    Pager<PlaylistSimple> playlists = api.searchPlaylists("Today's Top Hits");

    ASSERT_THAT(playlists.getItems(), testing::Contains(testing::Property(&PlaylistSimple::getName, testing::StrEq("Today's Top Hits"))));
}

TEST_F(TestEndpoints, SearchTracksTest) {
    Pager<Track> tracks = api.searchTracks("Brightside");

    ASSERT_THAT(tracks.getItems(), testing::Contains(testing::Property(&TrackSimple::getName, testing::StrEq("Mr. Brightside"))));
}

TEST_F(TestEndpoints, GetTrackTest) {
    std::shared_ptr<Track> track = api.getTrack("3n3Ppam7vgaVa1iaRUc9Lp");
    ASSERT_STREQ(track->getName().c_str(), "Mr. Brightside");
}

TEST_F(TestEndpoints, GetTracksTest) {
    std::vector<std::shared_ptr<Track>> tracks = api.getTracks({"3n3Ppam7vgaVa1iaRUc9Lp", "3twNvmDtFQtAd5gMKedhLD"});
    ASSERT_THAT(tracks, testing::ElementsAre(
                            testing::Property(&std::shared_ptr<Track>::operator*, testing::Property(&Track::getName, testing::StrEq("Mr. Brightside"))),
                            testing::Property(&std::shared_ptr<Track>::operator*, testing::Property(&Track::getName, testing::StrEq("Somebody Told Me")))));
}

TEST_F(TestEndpoints, GetUserTest) {
    std::shared_ptr<UserPublic> user = api.getUser("tuggareutangranser");
    ASSERT_STREQ(user->getDisplayName().c_str(), "Lilla Namo");
}

TEST_F(TestEndpoints, EditPlaylistsTest) {
    std::shared_ptr<User> me = api.getMe();

    // Create a playlist and make sure the playlist is properly returned with the correct attributes
    std::shared_ptr<Playlist> playlist = api.createPlaylist(me->getId(), "Test Playlist");
    ASSERT_STREQ(playlist->getName().c_str(), "Test Playlist");

    // Make sure the playlist is followed on being created
    Pager<PlaylistSimple> myPlaylists = api.getMyPlaylists();
    ASSERT_THAT(myPlaylists.getItems(), testing::Contains(testing::Property(&PlaylistSimple::getName, testing::StrEq("Test Playlist"))));

    // Add tracks and make sure they are in the list of playlist tracks
    api.addTracksToPlaylist(me->getId(), playlist->getId(), {"spotify:track:3n3Ppam7vgaVa1iaRUc9Lp", "spotify:track:3twNvmDtFQtAd5gMKedhLD"});
    Pager<PlaylistTrack> tracks = api.getPlaylistTracks(me->getId(), playlist->getId());
    ASSERT_THAT(tracks.getItems(),
                testing::ElementsAre(
                    testing::Property(&PlaylistTrack::getTrack, testing::Property(&std::shared_ptr<Track>::operator*,
                                                                                  testing::Property(&Track::getName, testing::StrEq("Mr. Brightside")))),
                    testing::Property(&PlaylistTrack::getTrack, testing::Property(&std::shared_ptr<Track>::operator*,
                                                                                  testing::Property(&Track::getName, testing::StrEq("Somebody Told Me"))))));

    // Remove one of the tracks and make sure it is no longer in the playlist
    api.removeTracksFromPlaylist(me->getId(), playlist->getId(), {"spotify:track:3n3Ppam7vgaVa1iaRUc9Lp"});
    tracks = api.getPlaylistTracks(me->getId(), playlist->getId());
    ASSERT_THAT(tracks.getItems(), testing::ElementsAre(testing::Property(
                                       &PlaylistTrack::getTrack, testing::Property(&std::shared_ptr<Track>::operator*,
                                                                                   testing::Property(&Track::getName, testing::StrEq("Somebody Told Me"))))));

    // Unfollow the playlist
    api.unfollowPlaylist(me->getId(), playlist->getId());
    myPlaylists = api.getMyPlaylists();
    ASSERT_THAT(myPlaylists.getItems(), testing::Not(testing::Contains(testing::Property(&PlaylistSimple::getName, testing::StrEq("Test Playlist")))));
}
#pragma clang diagnostic pop


#include "SoundCloud.h"

StatusType SoundCloud::AddArtist(int artistID) {
    if (artistID<=0){
        return INVALID_INPUT;
    }
    if(artists_table.find(artistID)){
        return FAILURE;
    }
    Artist* new_artist;
    try{
        new_artist = new Artist(artistID);
    }
    catch (std::bad_alloc &){
        return ALLOCATION_ERROR;
    }
    if (!artists_table.insert(artistID,new_artist)){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType SoundCloud::RemoveArtist(int artistID) {
    if (artistID<=0){
        return INVALID_INPUT;
    }
    if (artists_table.find(artistID) == nullptr || artists_table.find(artistID)->getNumSongs()!= 0){
        return FAILURE;
    }
    artists_table.remove(artistID);
    return SUCCESS;
}

StatusType SoundCloud::AddSong(int artistID, int songID) {
    if (artistID <=0 || songID <=0){
        return INVALID_INPUT;
    }
    Artist* found_artist = artists_table.find(artistID);
    if (!found_artist){
        return FAILURE;
    }
    if(found_artist->searchSong(songID) != nullptr){
        return FAILURE;
    }
    //add to two artist trees

    if(!found_artist->addSong(songID)){
        return ALLOCATION_ERROR;
    }
    //add to all songs tree
    SongAll* new_song;
    try{
        new_song = new SongAll(artistID,songID);
    }
    catch (std::bad_alloc &) {
        return ALLOCATION_ERROR;
    }
    all_songs_tree.insert(new_song);

    //add pointer to main tree from artist data
    found_artist->linkMainTree(new_song,songID);
    return SUCCESS;
}

StatusType SoundCloud::RemoveSong(int artistID, int songID) {
    if (artistID <=0 || songID <=0){
        return INVALID_INPUT;
    }
    Artist* found_artist = artists_table.find(artistID);
    if (!found_artist){
        return FAILURE;
    }
    if(found_artist->searchSong(songID) == nullptr){
        return FAILURE;
    }
    //remove from main tree
    all_songs_tree.remove(found_artist->searchSong(songID)->getMainTreePtr());

    //remove from trees under artist
    found_artist->removeSong(songID);

    return SUCCESS;
}

StatusType SoundCloud::AddToSongCount(int artistID, int songID, int count) {
    if (artistID <=0 || songID <=0 || count<=0){
        return INVALID_INPUT;
    }
    Artist* found_artist = artists_table.find(artistID);
    if (!found_artist){
        return FAILURE;
    }
    SongID* current_song = found_artist->searchSong(songID);
    if (!current_song){
        return FAILURE;
    }
    int current_count = current_song->getNumStreams();
    current_count += count;
    SongAll* updated_song;
    try {
        updated_song = new SongAll(artistID,songID,current_count);
    }
    catch (std::bad_alloc &) {
        return ALLOCATION_ERROR;
    }
    all_songs_tree.remove(current_song->getMainTreePtr());
    all_songs_tree.insert(updated_song);

    if(!found_artist->updateCount(songID,current_count)){
        return ALLOCATION_ERROR;
    }
    found_artist->linkMainTree(updated_song,songID);
    return SUCCESS;
}

StatusType SoundCloud::GetArtistBestSong(int artistID, int *songID) {
    if (artistID <= 0 || songID == nullptr){
        return INVALID_INPUT;
    }
    Artist* found_artist = artists_table.find(artistID);
    if (!found_artist || found_artist->getNumSongs() == 0) {
        return FAILURE;
    }
    *songID = found_artist->getBestSong();
    return SUCCESS;
}

StatusType SoundCloud::GetRecommendedSongInPlace(int rank, int *artistID, int *songID) {

    if (artistID == nullptr || songID == nullptr || rank <= 0 ){
        return INVALID_INPUT;
    }
    if (all_songs_tree.getNumNodes()<rank){
        return FAILURE;
    }
    SongAll* wanted_song = all_songs_tree.select(rank);
    *artistID = wanted_song->getArtistID();
    *songID = wanted_song->getSongID();
    return SUCCESS;
}

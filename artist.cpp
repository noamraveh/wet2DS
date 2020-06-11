#include "artist.h"

Artist::Artist(int artistID) :id(artistID), num_songs(0),best_song(0){
    songs_tree_rank = new AVLTree<SongRank>();
    songs_tree_index = new AVLTree<SongID>();
}

Artist::~Artist() {
    delete songs_tree_index;
    delete songs_tree_rank;
}

SongID *Artist::searchSong(int songID) {
    SongID search_data(songID);
    return songs_tree_index->findData(&search_data);
}

bool Artist::addSong(int song_id){
    SongRank* new_song_rank;
    SongID* new_song_id;
    //create data and add to rank tree
    try{
        new_song_rank = new SongRank(song_id);
    }
    catch(std::bad_alloc&){
        return false;
    }
    songs_tree_rank->insert(new_song_rank);
    //create data and add to id tree
    try{
        new_song_id = new SongID(song_id);
    }
    catch(std::bad_alloc&){
        delete new_song_rank;
        return false;
    }
    songs_tree_index->insert(new_song_id);

    //add ptr to rank tree in id tree
    new_song_id->linkRankTree(new_song_rank);
    best_song = songs_tree_rank->getMin()->getID();
    num_songs++;
    return true;
}
void Artist::removeSong(int song_id) {
    SongID search_song(song_id);
    SongID* found_song = songs_tree_index->findData(&search_song);
    songs_tree_rank->remove(found_song->getRankTreePtr());
    songs_tree_index->remove(found_song);
    if (songs_tree_rank->getNumNodes() == 0)
        best_song =0;
    else
        best_song = songs_tree_rank->getMin()->getID();
    num_songs--;
}

int Artist::getNumSongs() {
    return num_songs;
}

void Artist::linkMainTree(SongAll *new_song, int song_id) {
    searchSong(song_id)->linkMainTree(new_song);
}

bool Artist::updateCount(int songID, int count) {//create data and add to rank tree
    SongID search_song(songID);
    SongID* found_song = songs_tree_index->findData(&search_song);
    found_song->updateStreams(count);
    SongRank* new_song_rank;
    try{
        new_song_rank = new SongRank(songID,count);
    }
    catch(std::bad_alloc&){
        return false;
    }
    songs_tree_rank->remove(found_song->getRankTreePtr());
    songs_tree_rank->insert(new_song_rank);

    //add ptr to rank tree in id tree
    found_song->linkRankTree(new_song_rank);
    best_song = songs_tree_rank->getMin()->getID();
    return true;
}

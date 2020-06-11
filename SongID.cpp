#include "SongID.h"

SongID::SongID(int song_id, int num_streams) :song_id(song_id),num_streams(0),song_rank_tree_ptr(nullptr),all_songs_tree_ptr(nullptr){}

void SongID::linkMainTree(SongAll *all_songs_data) {
    all_songs_tree_ptr = all_songs_data;
}

void SongID::linkRankTree(SongRank *new_song_rank) {
    song_rank_tree_ptr = new_song_rank;
}

SongRank *SongID::getRankTreePtr() {
    return song_rank_tree_ptr;
}

SongAll *SongID::getMainTreePtr() {
    return all_songs_tree_ptr;
}

int SongID::getNumStreams() {
    return num_streams;
}

bool SongID::operator<(const SongID &song) {
    return song_id < song.song_id;
}

bool SongID::operator==(const SongID &song) {
    return song_id == song.song_id;
}

void SongID::updateStreams(int new_count) {
    num_streams = new_count;
}

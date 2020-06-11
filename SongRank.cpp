#include "SongRank.h"

SongRank::SongRank(int song_id, int num_streams) :song_id(song_id),num_streams(num_streams){}

bool SongRank::operator<(const SongRank &song) {
    if (num_streams>song.num_streams){
        return true;
    }
    else if(num_streams<song.num_streams){
        return false;
    }
    else{ // num streams is equal, checking according to song id
        return song_id < song.song_id;
    }
}

bool SongRank::operator==(const SongRank &song) {
    return num_streams==song.num_streams && song_id==song.song_id;
}

int SongRank::getID() {
    return song_id;
}


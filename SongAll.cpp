#include "SongAll.h"

SongAll::SongAll(int artist_id, int song_id, int num_streams) : artist_id(artist_id),song_id(song_id),num_streams(num_streams){}

bool SongAll::operator<(const SongAll &song) {
    if (num_streams>song.num_streams){
        return true;
    }
    else if(num_streams<song.num_streams){
        return false;
    }
    else{ // num streams is equal, checking according to artist id and then song id
        if (artist_id<song.artist_id){
            return true;
        }
        else if(artist_id>song.artist_id){
            return false;
        }
        else{ // artist id is equal, checking according to song id
            return song_id < song.song_id;
        }
    }
}

bool SongAll::operator==(const SongAll &song) {
    return num_streams==song.num_streams && artist_id==song.artist_id && song_id == song.song_id;
}

int SongAll::getArtistID() {
    return artist_id;
}

int SongAll::getSongID() {
    return song_id;
}

int SongAll::getNumStreams() {
    return num_streams;
}

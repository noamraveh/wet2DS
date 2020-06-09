//
//data for songs tree sorted by song id
//

#ifndef WET2DS_SONGID_H
#define WET2DS_SONGID_H

#include "SongRank.h"
#include "SongAll.h"

class SongID{
    int song_id;
    int num_streams;
    SongRank* song_rank_tree_ptr;
    SongAll* all_songs_tree_ptr;
public:
    //ctor
    SongID(int song_id,int num_streams=0):song_id(song_id),num_streams(0){};
    //dtor
    //operator <
    //opertator ==
    //get num streams

    void linkMainTree(SongAll* all_songs_data){
        all_songs_tree_ptr = all_songs_data;
    }

    void linkRankTree(SongRank *new_song_rank) {
        song_rank_tree_ptr = new_song_rank;
    }

    SongRank *getRankTreePtr() {
        return song_rank_tree_ptr;
    }

    SongAll *getMainTreePtr() {
        return all_songs_tree_ptr;
    }

    int getNumStreams() {
        return num_streams;
    }

    void updateCount(int count) {

    }
};
#endif //WET2DS_SONGID_H

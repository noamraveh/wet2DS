//
// Created by Noam Raveh on 08/06/2020.
//

#ifndef WET2DS_ARTIST_H
#define WET2DS_ARTIST_H
#include "AVLRankTreeFinal.h"
#include "SongRank.h"
#include "SongID.h"
#include "SongAll.h"

class Artist{
    int id;
    int num_songs;
    int best_song;
    AVLTree<SongID>* songs_tree_index;
    AVLTree<SongRank>* songs_tree_rank;
public:
    //ctor
    explicit Artist(int artistID);
    //dtor
    ~Artist();
    //get best songs
    int getBestSong(){
        return best_song;
    }
    //find song
    SongID* searchSong(int songID);

    bool addSong(int song_id);

    void removeSong(int song_id);

    int getNumSongs();

    void linkMainTree(SongAll *new_song,int song_id);

    bool updateCount(int songID, int count);
};

#endif //WET2DS_ARTIST_H

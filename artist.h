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
    Artist(int artistID):id(artistID), num_songs(0),best_song(0){}
    //dtor
    ~Artist()= default;
    //get best songs
    //get num songs
    //find song
    SongID* searchSong(int songID){
        SongID search_data(songID);
        return songs_tree_index->findData(&search_data);
    }

    void addSong(int song_id){

        SongRank* new_song_rank = new SongRank(song_id);
        songs_tree_rank->insert(new_song_rank);

        SongID* new_song_id = new SongID(song_id);
        songs_tree_index->insert(new_song_id);

        new_song_id->linkRankTree(new_song_rank);
    }

    //add song to 3 trees
    //remove song from all 3 trees
    int getNumSongs() {
        return num_songs;
    }

    void linkMainTree(SongAll *new_song,int song_id) {
        searchSong(song_id)->linkMainTree(new_song);
    }
};

#endif //WET2DS_ARTIST_H

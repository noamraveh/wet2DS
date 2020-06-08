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
        //create data and add to rank tree
        SongRank* new_song_rank = new SongRank(song_id);
        songs_tree_rank->insert(new_song_rank);
        //create data and add to id tree
        SongID* new_song_id = new SongID(song_id);
        songs_tree_index->insert(new_song_id);
        //add ptr to rank tree in id tree
        new_song_id->linkRankTree(new_song_rank);
        num_songs++;
    }

    void removeSong(int song_id) {
        SongID search_song(song_id);
        SongID* found_song = songs_tree_index->findData(&search_song);
        songs_tree_rank->remove(found_song->getRankTreePtr());
        songs_tree_index->remove(found_song);
        best_song = songs_tree_rank->getMin()->getID();
        num_songs--;
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

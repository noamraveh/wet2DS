//
// Created by Noam Raveh on 08/06/2020.
//

#ifndef WET2DS_SOUNDCLOUD_H
#define WET2DS_SOUNDCLOUD_H

#include "HashTable.h"
#include "artist.h"
#include "SongAll.h"
#include "AVLRankTreeFinal.h"
#include "library2.h"

class SoundCloud{
    HashTable<Artist> artists_table;
    AVLTree<SongAll> all_songs_tree;

public:
    //ctor
    SoundCloud()= default;

    //dtor
    ~SoundCloud() = default;

    //add Artist
    StatusType AddArtist(int artistID){
        if (artistID<=0){
            return INVALID_INPUT;
        }
        if(artists_table.find(artistID)){
            return FAILURE;
        }
        auto new_artist = new Artist(artistID);
        artists_table.insert(artistID,new_artist);
        return SUCCESS;
    }

    StatusType RemoveArtist(int artistID){
        if (artistID<=0){
            return INVALID_INPUT;
        }
        if (artists_table.find(artistID) == nullptr || artists_table.find(artistID)->getNumSongs()!= 0){
            return FAILURE;
        }
        artists_table.remove(artistID);
        return SUCCESS;
    }
    StatusType AddSong (int artistID, int songID){
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
        found_artist->addSong(songID);

        //add to all songs tree
        SongAll* new_song = new SongAll(artistID,songID);
        all_songs_tree.insert(new_song);

        //add pointer to main tree from artist data
        found_artist->linkMainTree(new_song,songID);
        return SUCCESS;
    }
    StatusType RemoveSong(int artistID,int songID){
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
        found_artist->removeSong(songID);
        all_songs_tree.remove(found_artist->searchSong(songID)->getMainTreePtr());
        return SUCCESS;
    }

    StatusType AddToSongCount(int artistID,int songID, int count){
        if (artistID <=0 || songID <=0 || count<=0){
            return INVALID_INPUT;
        }
        Artist* found_artist = artists_table.find(artistID);
        if (!found_artist){
            return FAILURE;
        }
        found_artist.addToSongCount();
        return SUCCESS;
    }

};
#endif //WET2DS_SOUNDCLOUD_H

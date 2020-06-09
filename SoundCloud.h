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
    explicit SoundCloud():artists_table(HashTable<Artist>(7)){}
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
        //remove from main tree
        all_songs_tree.remove(found_artist->searchSong(songID)->getMainTreePtr());

        //remove from trees under artist
        found_artist->removeSong(songID);

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
        SongID* current_song = found_artist->searchSong(songID);
        if (!current_song){
            return FAILURE;
        }
        int current_count = current_song->getNumStreams();
        current_count += count;
        SongAll* updated_song = new SongAll(artistID,songID,current_count);
        all_songs_tree.remove(current_song->getMainTreePtr());
        all_songs_tree.insert(updated_song);

        found_artist->updateCount(songID,current_count);
        found_artist->linkMainTree(updated_song,songID);
        return SUCCESS;
    }

    StatusType GetArtistBestSong(int artistID, int *songID){
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
    StatusType GetRecommendedSongInPlace(int rank, int *artistID, int *songID){
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




};
#endif //WET2DS_SOUNDCLOUD_H

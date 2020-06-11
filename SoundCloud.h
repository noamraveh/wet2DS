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
    StatusType AddArtist(int artistID);

    StatusType RemoveArtist(int artistID);

    StatusType AddSong (int artistID, int songID);

    StatusType RemoveSong(int artistID,int songID);

    StatusType AddToSongCount(int artistID,int songID, int count);

    StatusType GetArtistBestSong(int artistID, int *songID);

    StatusType GetRecommendedSongInPlace(int rank, int *artistID, int *songID);

};
#endif //WET2DS_SOUNDCLOUD_H

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
    explicit SongID(int song_id,int num_streams=0);
    //dtor
    ~SongID()= default;

    void linkMainTree(SongAll* all_songs_data);

    void linkRankTree(SongRank *new_song_rank);

    SongRank *getRankTreePtr();

    SongAll *getMainTreePtr();

    int getNumStreams();

    //operator <
    bool operator<(const SongID &song);

    //operator ==
    bool operator==(const SongID &song);

    void updateStreams(int new_count);
};
#endif //WET2DS_SONGID_H

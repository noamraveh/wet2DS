//
// data for songs tree sorted by rank
//

#ifndef WET2DS_SONGRANK_H
#define WET2DS_SONGRANK_H
class SongRank{
    int song_id;
    int num_streams;
public:
    //ctor
    SongRank(int song_id,int num_streams=0):song_id(song_id),num_streams(num_streams){};
    //dtor
    //operator <
    //operator ==
};
#endif //WET2DS_SONGRANK_H

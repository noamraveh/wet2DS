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
    explicit SongRank(int song_id,int num_streams=0);
    //dtor
    ~SongRank()= default;
    //operator <
    bool operator<(const SongRank &song);
    //operator ==
    bool operator==(const SongRank& song);

    int getID();
};
#endif //WET2DS_SONGRANK_H

//
//data for all songs tree
//

#ifndef WET2DS_SONGALL_H
#define WET2DS_SONGALL_H
class SongAll{
    int artist_id;
    int song_id;
    int num_streams;
public:

    //ctor
    SongAll(int artist_id,int song_id,int num_streams = 0): artist_id(artist_id),song_id(song_id),num_streams(num_streams){};
    //dtor
    //operator <
    //operator ==
};
#endif //WET2DS_SONGALL_H

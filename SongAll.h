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
    SongAll(int artist_id,int song_id,int num_streams = 0);;
    //dtor
    //operator <
    bool operator<(const SongAll& song);
    //operator ==
    bool operator==(const SongAll& song);
    int getArtistID();
    int getSongID();
    int getNumStreams();
};
#endif //WET2DS_SONGALL_H

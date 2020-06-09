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
    bool operator<(const SongRank &song){
        if (num_streams>song.num_streams){
            return true;
        }
        else if(num_streams<song.num_streams){
            return false;
        }
        else{ // num streams is equal, checking according to song id
            return song_id < song.song_id;
        }
    }
    //operator ==
    bool operator==(const SongRank& song){
        return num_streams==song.num_streams && song_id==song.song_id;
    }

    int getID() {
        return song_id;
    }
};
#endif //WET2DS_SONGRANK_H

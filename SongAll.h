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
    SongAll(int artist_id,int song_id,int num_streams = 0): artist_id(artist_id),song_id(song_id),num_streams(num_streams){}
    //dtor
    ~SongAll() = default;

    //operator <
    bool operator<(const SongAll& song){
        if (num_streams>song.num_streams){
            return true;
        }
        else if(num_streams<song.num_streams){
            return false;
        }
        else{ // num streams is equal, checking according to artist id and then song id
            if (artist_id<song.artist_id){
                return true;
            }
            else if(artist_id>song.artist_id){
                return false;
            }
            else{ // artist id is equal, checking according to song id
                return song_id < song.song_id;
            }
        }
    }
    //operator ==
    bool operator==(const SongAll& song){
        return num_streams==song.num_streams && artist_id==song.song_id && song_id == song.song_id;
    }

};
#endif //WET2DS_SONGALL_H

#include "library2.h"
#include "SoundCloud.h"


void *Init(){
    auto *DS = new SoundCloud();
    return (void*) DS;
}
StatusType AddArtist(void *DS, int artistID){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((SoundCloud*)DS)->AddArtist(artistID);
}

StatusType RemoveArtist(void *DS, int artistID){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((SoundCloud*)DS)->RemoveArtist(artistID);
}


StatusType AddSong(void *DS, int artistID, int songID){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((SoundCloud*)DS)->AddSong(artistID,songID);
}

StatusType RemoveSong(void *DS, int artistID, int songID){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((SoundCloud*)DS)->RemoveSong(artistID,songID);
}


StatusType AddToSongCount(void *DS, int artistID, int songID, int count){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((SoundCloud*)DS)->AddToSongCount(artistID,songID,count);
}

StatusType GetArtistBestSong(void *DS, int artistID, int *songId){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((SoundCloud*)DS)->GetArtistBestSong(artistID,songId);
}

StatusType GetRecommendedSongInPlace(void *DS, int rank, int *artistId, int *songId){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((SoundCloud*)DS)->GetRecommendedSongInPlace(rank,artistId,songId);
}

void Quit(void** DS){
    if(*DS != nullptr){
        delete ((SoundCloud *)*DS);
        *DS = nullptr;
    }
}
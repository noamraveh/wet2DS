cmake_minimum_required(VERSION 3.15)
project(wet2DS)

set(CMAKE_CXX_STANDARD 11)

add_executable(wet2DS main.cpp artist.h SongID.h SongRank.h SongAll.h SoundCloud.cpp SoundCloud.h)
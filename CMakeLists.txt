cmake_minimum_required(VERSION 3.21)
project(test_vote C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(test_vote
        Condorcet.c
        Condorcet.h
        Main.c
        Main.h
        Uninominal.c
        Uninominal.h
        utilitaires.c
        utilitaires.h)

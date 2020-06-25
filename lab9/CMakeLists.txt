cmake_minimum_required(VERSION 3.15)
project(untitled2 C)

set(CMAKE_C_STANDARD 99)
add_executable(lab9 main-race.c)
add_executable(lab9_1 main-deadlock.c)
add_executable(lab9_2 main-deadlock-global.c)
add_executable(lab9_3 main-signal.c)
add_executable(lab9_4 main-signal-cv.c)
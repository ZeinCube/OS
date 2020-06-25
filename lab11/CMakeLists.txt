cmake_minimum_required(VERSION 3.15)
project(untitled2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab11 main-common.c main-header.h mythreads.h vector-deadlock.c vector-avoid-hold-and-wait.c)
add_executable(lab11_1 vector-global-order.c vector-header.h vector-nolock.c vector-try-wait.c)
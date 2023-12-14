cmake_minimum_required(VERSION 3.26)
project(tema3)

set(CMAKE_CXX_STANDARD 17)

add_executable(tema3 main.c
        state_manager.c
        state_manager.h
        string_utils.c
        string_utils.h
        image.c
        image.h
        utils.c
        utils.h
        statics.h)

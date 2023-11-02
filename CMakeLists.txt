cmake_minimum_required(VERSION 3.22)
project(infinite_product C)
project(codeinvim C)
project(gigel_and_the_checkboard C)
project(nanogram_checker C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(infinite_product
        infinite_product.c
        math_utils.h
        math_utils.c
        utils.h
        utils.c)

add_executable(codeinvim
        codeinvim.c
        points_utils.h
        points_utils.c
        nanogram_checker.c
        utils.h
        utils.c
)

add_executable(gigel_and_the_checkboard
        gigel_and_the_checkboard.c
        board_utils.h
        board_utils.c
        utils.h
        utils.c
)

add_executable(nanogram_checker
        nanogram_checker.c
        utils.h
        utils.c
        nanogram_utils.h
        nanogram_utils.c)

target_link_libraries(infinite_product -lm)

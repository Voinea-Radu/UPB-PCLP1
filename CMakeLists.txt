cmake_minimum_required(VERSION 3.22)
project(infinite_product C)
project(codeinvim C)
project(gigel_and_the_checkboard C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(infinite_product
        infinite_product.c
        math_util.h
        math_util.c)

add_executable(codeinvim
        codeinvim.c
        punctaje_util.h
        punctaje_util.c
)

add_executable(gigel_and_the_checkboard
        gigel_and_the_checkboard.c
        tabla_util.h
        tabla_util.c
)

target_link_libraries(infinite_product -lm)

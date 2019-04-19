cmake_minimum_required(VERSION 3.13)
project(pac_superman C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES libgraphics/exceptio.c libgraphics/genlib.c libgraphics/graphics.c
        libgraphics/random.c libgraphics/simpio.c libgraphics/strlib.c test.c sprite.c sprite.h vector2.c vector2.h example_sprite.c example_sprite.h)

include_directories(libgraphics)

add_executable(pac_superman ${SOURCE_FILES})

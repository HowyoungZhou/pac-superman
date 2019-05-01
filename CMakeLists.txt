cmake_minimum_required(VERSION 3.13)
project(pac_superman C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES libgraphics/exceptio.c libgraphics/genlib.c libgraphics/graphics.c libgraphics/random.c
        libgraphics/simpio.c libgraphics/strlib.c engine/sprite.c engine/sprite.h utils/vector2.c utils/vector2.h
        sprites/example_sprite.c sprites/example_sprite.h engine/engine.c engine/engine.h main.c utils/drawing.c
        utils/drawing.h engine/sprites_list.c engine/sprites_list.h engine/animator.c engine/animator.h
        utils/exceptions.c sprites/example_animated_sprite.c sprites/example_animated_sprite.h engine/controller.c
        engine/controller.h sprites/example_controllable_sprite.c sprites/example_controllable_sprite.h
        engine/collider.c engine/collider.h sprites/example_collidable_sprite.c sprites/example_collidable_sprite.h)

include_directories(libgraphics)
include_directories(engine)
include_directories(sprites)
include_directories(utils)

add_executable(pac_superman ${SOURCE_FILES})

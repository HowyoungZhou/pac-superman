cmake_minimum_required(VERSION 3.13)
project(pac_superman C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES libgraphics/exceptio.c libgraphics/genlib.c libgraphics/graphics.c libgraphics/random.c
        libgraphics/simpio.c libgraphics/strlib.c engine/sprite.c engine/sprite.h utils/vector2.c utils/vector2.h
        sprites/example_sprite.c sprites/example_sprite.h engine/engine.c engine/engine.h main.c utils/drawing.c
        utils/drawing.h engine/animator.c engine/animator.h
        utils/exceptions.c sprites/example_animated_sprite.c sprites/example_animated_sprite.h engine/controller.c
        engine/controller.h sprites/example_controllable_sprite.c sprites/example_controllable_sprite.h
        engine/collider.c engine/collider.h sprites/example_collidable_sprite.c sprites/example_collidable_sprite.h
        sprites/pellet.c sprites/pellet.h utils/colors.c utils/colors.h ui/imgui.c utils/linked_list.c
        utils/linked_list.h ui/button.c ui/button.h utils/events.c utils/events.h ui/menu.c ui/menu.h
        ui/game_menu.c ui/game_menu.h sprites/pacman_sprite.c sprites/pacman_sprite.h engine/scene.c
        engine/scene.h scenes/game_scene.c scenes/game_scene.h ui/style.h engine/assets.c engine/assets.h
        sprites/example_bitmap_sprite.c sprites/example_bitmap_sprite.h)

include_directories(libgraphics)
include_directories(engine)
include_directories(sprites)
include_directories(scenes)
include_directories(utils)
include_directories(ui)

add_executable(pac_superman ${SOURCE_FILES})

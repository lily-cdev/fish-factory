cmake_minimum_required(VERSION 3.16)
project(Fish_Factory LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "compiler (C) failed to initialise :(")
endif()

if(NOT CMAKE_CXX_COMPILER)
    message(FATAL_ERROR "compiler (CXX) failed to initialise :(")
endif()

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
add_subdirectory(external/SDL3)
set(BUILD_SHARED_LIBS OFF)
set(SDLTTF_VENDORED ON)
set(SDLTTF_PLUTOSVG OFF)
add_subdirectory(external/SDL3_ttf)

add_executable(Fish_Factory
	internal/core/fish_factory.c
	internal/source/other/transitions.c
	internal/source/other/ui.c
	internal/source/other/parser.c
	internal/source/other/tools.c
	internal/source/other/machines.c
	internal/source/connectables/general.c
	internal/source/connectables/wires.c
	internal/source/connectables/pipes.c
	internal/source/ui/actions.c
	internal/source/ui/general.c
	internal/source/ui/application.c
	internal/source/ui/logs.c
	internal/source/ui/other.c
	internal/source/ui/settings.c
	internal/source/interface/tutorials.c
	internal/source/interface/general.c
	internal/source/interface/terminals.c
	internal/source/grid/updates.c
	internal/source/grid/machines.c
	internal/source/grid/movement.c
	internal/source/actions/menus.c
	internal/source/actions/none.c
	internal/source/placing/cultivators.c
	internal/source/placing/extractors.c
	internal/source/placing/generators.c
	internal/source/placing/other.c
	internal/source/placing/processors.c
	internal/source/placing/transporters.c
	internal/source/prompts/actions.c
	internal/source/prompts/catalog.c
	internal/source/prompts/cheats.c
	internal/source/prompts/daily_report.c
	internal/source/prompts/help.c
	internal/source/prompts/machines.c
	internal/source/prompts/shop.c
	internal/source/prepping/actions.c
	internal/source/prepping/cleanup.c
	internal/source/prepping/definitions.c
	internal/source/prepping/other.c
	internal/source/prepping/preconfigs.c
	internal/source/prepping/preloaders.c
	internal/source/prepping/subloaders.c
	internal/source/prepping/text.c
	internal/source/prepping/setup.c
	internal/source/prepping/lang.c
	internal/source/data/audio.c
	internal/source/data/saving.c
	internal/source/data/settings.c
	internal/source/rendering/supplier.c
	internal/source/rendering/tiles.c
	internal/source/rendering/effects.c
	internal/source/rendering/ocean.c
	internal/source/rendering/particles.c
	internal/source/rendering/pyramid.c
	internal/source/cycling/cultivators.c
	internal/source/cycling/extractors.c
	internal/source/cycling/generators.c
	internal/source/cycling/other.c
	internal/source/cycling/processors.c
	internal/source/cycling/transporters.c
	internal/source/items/tools.c
	internal/source/items/fish.c
	internal/source/items/definitions.c
	internal/source/items/recipes.c
	internal/source/items/setup.c
	internal/precompiled/images.c
	internal/precompiled/tools.c
	external/miniaudio/miniaudio.c
	modules/resource.rc
)

target_include_directories(Fish_Factory PRIVATE
    internal/core
    internal/precompiled
	internal/headers
)

target_include_directories(Fish_Factory PUBLIC
    external
	external/SDL3/include
	external/SDL3_ttf/include
)

target_link_libraries(Fish_Factory PRIVATE SDL3::SDL3-static SDL3_ttf::SDL3_ttf-static)
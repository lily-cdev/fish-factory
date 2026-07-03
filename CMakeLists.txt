cmake_minimum_required(VERSION 3.16)
project(Fish_Factory LANGUAGES C CXX)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(PREPROCESSOR "${CMAKE_SOURCE_DIR}/pre2processor.py")
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


function(add_presource TARGET SOURCE_FILE)
	get_filename_component(NAME_WE ${SOURCE_FILE} NAME_WE)
	get_filename_component(EXT ${SOURCE_FILE} EXT)
	get_filename_component(ABS_SRC ${SOURCE_FILE} ABSOLUTE BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
	set(OUT "${CMAKE_CURRENT_BINARY_DIR}/traced/${NAME_WE}${EXT}")
	add_custom_command(
		OUTPUT ${OUT} COMMAND ${Python3_EXECUTABLE} ${PREPROCESSOR} ${ABS_SRC} ${OUT} DEPENDS ${ABS_SRC} ${PREPROCESSOR}
		COMMENT "processing ${SOURCE_FILE}" VERBATIM
	)
	target_sources(${TARGET} PRIVATE ${OUT})
	target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

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
	internal/source/other/tools.c
	internal/source/other/machines.c
	internal/source/other/parser.c
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
	internal/source/placing/generators.c
	internal/source/placing/other.c
	internal/source/placing/transporters.c
	internal/source/prompts/actions.c
	internal/source/prompts/catalog.c
	internal/source/prompts/genetics.c
	internal/source/prompts/cheats.c
	internal/source/prompts/daily_report.c
	internal/source/prompts/help.c
	internal/source/prompts/machines.c
	internal/source/prompts/shop.c
	internal/source/prepping/actions.c
	internal/source/prepping/cleanup.c
	internal/source/prepping/definitions.c
	internal/source/prepping/other.c
	internal/source/prepping/subloaders.c
	internal/source/prepping/text.c
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
	internal/source/cycling/generators.c
	internal/source/cycling/other.c
	internal/source/cycling/transporters.c
	internal/source/items/tools.c
	internal/source/items/fish.c
	internal/source/items/recipes.c
	internal/precompiled/images.c
	external/miniaudio/miniaudio.c
	modules/resource.rc
)

add_presource(Fish_Factory internal/source/prepping/preloaders.c)
add_presource(Fish_Factory internal/source/prepping/setup.c)

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
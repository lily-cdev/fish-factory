cmake_minimum_required(VERSION 3.16)
project(Fish_Factory LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_CXX_COMPILER)
    message(FATAL_ERROR "CXX compiler failed to initialise")
endif()

if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "C compiler failed to initialise")
endif()

add_executable(Fish_Factory
    internal/core/fish_factory.cxx
	internal/source/audio.c
	internal/source/machines.c
	internal/source/updates.c
	internal/source/interface.cxx
	internal/source/pipes.c
	internal/source/terminals.cxx
	internal/source/transitions.c
	internal/source/tutorials.c
	internal/source/tutorials.cxx
	internal/source/ui.c
	internal/source/ui.cxx
	internal/source/wires.c
	internal/source/actions/cheats.cxx
	internal/source/actions/machines.cxx
	internal/source/actions/menus.cxx
	internal/source/actions/none.c
	internal/source/grid/cultivators.c
	internal/source/grid/decorations.c
	internal/source/grid/extractors.c
	internal/source/grid/generators.c
	internal/source/grid/other.c
	internal/source/grid/processors.c
	internal/source/grid/transporters.c
	internal/source/prompts/catalog.cxx
	internal/source/prompts/cheats.cxx
	internal/source/prompts/daily_report.c
	internal/source/prompts/help.cxx
	internal/source/prompts/machines.cxx
	internal/source/prompts/shop.cxx
	internal/source/prepping/cleanup.c
	internal/source/prepping/definitions.c
	internal/source/prepping/machines.c
	internal/source/prepping/other.c
	internal/source/prepping/preconfigs.c
	internal/source/prepping/preloaders.c
	internal/source/prepping/subloaders.c
	internal/source/prepping/text.c
	internal/source/prepping/tools.c
	internal/source/prepping/ui.c
	internal/source/prepping/setup.c
	internal/source/data/saving.c
	internal/source/data/settings.c
	internal/source/data/lang.c
	internal/source/rendering/tiles.c
	internal/source/rendering/effects.c
	internal/source/rendering/ocean.c
	internal/source/rendering/pyramid.c
	internal/source/items/tools.c
	internal/source/items/fish.c
	internal/source/items/definitions.c
	internal/source/items/recipes.c
	internal/source/items/setup.c
	internal/precompiled/images.c
	internal/precompiled/tools.c
	modules/neutral/resource.rc
)

target_include_directories(Fish_Factory PRIVATE
    internal/core
    internal/precompiled
	internal/headers
)

target_include_directories(Fish_Factory PUBLIC
    external/include
)

if (UNIX)
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
	else()
	endif()
else()
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_libraries(Fish_Factory PRIVATE
			"${CMAKE_SOURCE_DIR}/external/lib/win64/SDL3.lib"
			"${CMAKE_SOURCE_DIR}/external/lib/win64/SDL3_ttf.lib"
		)
	else()
		target_link_libraries(Fish_Factory PRIVATE
			"${CMAKE_SOURCE_DIR}/external/lib/win32/SDL3.lib"
			"${CMAKE_SOURCE_DIR}/external/lib/win32/SDL3_ttf.lib"
		)
	endif()
endif()

target_link_libraries(Fish_Factory PRIVATE)
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
    internal/core/preloader.cxx
	internal/source/audio.c
	internal/source/data.cxx
	internal/source/fish.cxx
	internal/source/machines.cxx
	internal/source/rendering.cxx
	internal/source/interface.cxx
	internal/source/items.cxx
	internal/source/pipes.cxx
	internal/source/recipes.cxx
	internal/source/terminals.cxx
	internal/source/transitions.c
	internal/source/tutorials.cxx
	internal/source/ui.cxx
	internal/source/wires.cxx
	internal/source/actions/cheats.cxx
	internal/source/actions/machines.cxx
	internal/source/actions/menus.cxx
	internal/source/actions/none.cxx
	internal/source/grid/cultivators.cxx
	internal/source/grid/decorations.cxx
	internal/source/grid/extractors.cxx
	internal/source/grid/generators.cxx
	internal/source/grid/other.cxx
	internal/source/grid/processors.cxx
	internal/source/grid/transporters.cxx
	internal/source/prompts/catalog.cxx
	internal/source/prompts/cheats.cxx
	internal/source/prompts/daily_report.cxx
	internal/source/prompts/help.cxx
	internal/source/prompts/machines.cxx
	internal/source/prompts/shop.cxx
	internal/source/prepping/cleanup.c
	internal/source/prepping/definitions.c
	internal/source/prepping/machines.c
	internal/source/prepping/other.c
	internal/source/prepping/preloaders.c
	internal/source/prepping/ui.c
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
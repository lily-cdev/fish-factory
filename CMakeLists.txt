cmake_minimum_required(VERSION 3.16)
project(Fish_Factory LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "compiler failed to initialise :(")
endif()

add_executable(Fish_Factory
    internal/core/fish_factory.c
	internal/source/pipes.c
	internal/source/transitions.c
	internal/source/wires.c
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
	internal/source/actions/cheats.c
	internal/source/actions/machines.c
	internal/source/actions/menus.c
	internal/source/actions/none.c
	internal/source/placing/cultivators.c
	internal/source/placing/decorations.c
	internal/source/placing/extractors.c
	internal/source/placing/generators.c
	internal/source/placing/other.c
	internal/source/placing/processors.c
	internal/source/placing/transporters.c
	internal/source/prompts/catalog.c
	internal/source/prompts/cheats.c
	internal/source/prompts/daily_report.c
	internal/source/prompts/help.c
	internal/source/prompts/machines.c
	internal/source/prompts/shop.c
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
	internal/source/data/audio.c
	internal/source/data/saving.c
	internal/source/data/settings.c
	internal/source/data/lang.c
	internal/source/rendering/supplier.c
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
	external/include/miniaudio/miniaudio.c
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
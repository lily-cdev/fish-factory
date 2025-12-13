cmake_minimum_required(VERSION 3.16)
project(Fish_Factory LANGUAGES C CXX)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_CXX_COMPILER)
    message(FATAL_ERROR "compiler failed to initialise")
endif()

add_executable(Fish_Factory
    internal/core/Fish_Factory.cxx
    internal/core/Preloader.cxx
	internal/source/Audio_Handler.cxx
	internal/source/Data_Handler.cxx
	internal/source/Fish_Handler.cxx
	internal/source/Grid_Handler.cxx
	internal/source/Render_Handler.cxx
	internal/source/Interface_Handler.cxx
	internal/source/Item_Handler.cxx
	internal/source/Pipe_Handler.cxx
	internal/source/Recipe_Handler.cxx
	internal/source/Terminal_Handler.cxx
	internal/source/Transition_Handler.cxx
	internal/source/Tutorial_Handler.cxx
	internal/source/UI_Handler.cxx
	internal/source/Wire_Handler.cxx
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
			"${CMAKE_SOURCE_DIR}/external/lib/win64/SDL3_image.lib"
		)
	else()
		target_link_libraries(Fish_Factory PRIVATE
			"${CMAKE_SOURCE_DIR}/external/lib/win32/SDL3.lib"
			"${CMAKE_SOURCE_DIR}/external/lib/win32/SDL3_ttf.lib"
			"${CMAKE_SOURCE_DIR}/external/lib/win32/SDL3_image.lib"
		)
	endif()
endif()

target_precompile_headers(Fish_Factory PRIVATE
	"internal/precompiled/Core.h"
	"internal/precompiled/Wrapper.hpp"
)

target_link_libraries(Fish_Factory PRIVATE)
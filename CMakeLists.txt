cmake_minimum_required(VERSION 3.16)
project(Fish_Factory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_CXX_COMPILER)
    message(FATAL_ERROR "compiler failed to initialise")
endif()

add_executable(Fish_Factory
    internal/core/Fish_Factory.cpp
    internal/core/Preloader.cpp
	internal/source/Audio_Handler.cpp
	internal/source/Data_Handler.cpp
	internal/source/Fish_Handler.cpp
	internal/source/Grid_Handler.cpp
	internal/source/Render_Handler.cpp
	internal/source/Interface_Handler.cpp
	internal/source/Item_Handler.cpp
	internal/source/Pipe_Handler.cpp
	internal/source/Recipe_Handler.cpp
	internal/source/Terminal_Handler.cpp
	internal/source/Transition_Handler.cpp
	internal/source/Tutorial_Handler.cpp
	internal/source/UI_Handler.cpp
	internal/source/Wire_Handler.cpp
	modules/neutral/resource.rc
)

target_include_directories(Fish_Factory PRIVATE
    internal/core
    internal/precompiled
	internal/headers
)

target_include_directories(Fish_Factory PUBLIC
    external
)

target_precompile_headers(Fish_Factory PRIVATE
	"internal/precompiled/Core.h"
	"internal/precompiled/Wrapper.hpp"
)

target_link_libraries(Fish_Factory PRIVATE
	"${CMAKE_SOURCE_DIR}/modules/lib/SDL3.lib"
	"${CMAKE_SOURCE_DIR}/modules/lib/SDL3_ttf.lib"
	"${CMAKE_SOURCE_DIR}/modules/lib/SDL3_image.lib"
)
# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/external/SDL3_ttf")
  file(MAKE_DIRECTORY "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/external/SDL3_ttf")
endif()
file(MAKE_DIRECTORY
  "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/_deps/sdl3_ttf_mirror-build"
  "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/_deps/sdl3_ttf_mirror-subbuild/sdl3_ttf_mirror-populate-prefix"
  "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/_deps/sdl3_ttf_mirror-subbuild/sdl3_ttf_mirror-populate-prefix/tmp"
  "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/_deps/sdl3_ttf_mirror-subbuild/sdl3_ttf_mirror-populate-prefix/src/sdl3_ttf_mirror-populate-stamp"
  "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/_deps/sdl3_ttf_mirror-subbuild/sdl3_ttf_mirror-populate-prefix/src"
  "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/_deps/sdl3_ttf_mirror-subbuild/sdl3_ttf_mirror-populate-prefix/src/sdl3_ttf_mirror-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/_deps/sdl3_ttf_mirror-subbuild/sdl3_ttf_mirror-populate-prefix/src/sdl3_ttf_mirror-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/kayla/Documents/Programming/Programs/C++/Fish_Factory/build/_deps/sdl3_ttf_mirror-subbuild/sdl3_ttf_mirror-populate-prefix/src/sdl3_ttf_mirror-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

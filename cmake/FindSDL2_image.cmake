# Distributed under the OSI-approved BSD 3-Clause License. See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindSDL2_image
# -------------
#
# Locate SDL2_image library
#
# This module defines:
#
# ::
#
# SDL2_IMAGE_LIBRARIES, the name of the library to link against
# SDL2_IMAGE_INCLUDE_DIRS, where to find the headers
# SDL2_IMAGE_FOUND, if false, do not try to link against
# SDL2_IMAGE_VERSION_STRING - human-readable string containing the
# version of SDL2_image
#
#
#
# For backward compatibility the following variables are also set:
#
# ::
#
# SDL2IMAGE_LIBRARY (same value as SDL2_IMAGE_LIBRARIES)
# SDL2IMAGE_INCLUDE_DIR (same value as SDL2_IMAGE_INCLUDE_DIRS)
# SDL2IMAGE_FOUND (same value as SDL2_IMAGE_FOUND)
#
#
#
# $SDLDIR is an environment variable that would correspond to the
# ./configure --prefix=$SDLDIR used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(SDL2_ARCH_64 TRUE)
  set(SDL2_PROCESSOR_ARCH "x64")
else()
  set(SDL2_ARCH_64 FALSE)
  set(SDL2_PROCESSOR_ARCH "x86")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

if(MINGW AND DEFINED SDL_EXT_DIR)
    if(SDL2_ARCH_64)
	  set(SDL_MINGW_EXT_DIR "${SDL_EXT_DIR}/x86_64-w64-mingw32")
    else()
	  set(SDL_MINGW_EXT_DIR "${SDL_EXT_DIR}/i686-w64-mingw32")
	endif()
endif()

SET(SDL2_SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
    /home/linuxbrew/.linuxbrew/opt/sdl2_image # bazzite with homebrew
    ${SDL_EXT_DIR}
    ${SDL_MINGW_EXT_DIR}
)

if (VITA)
    SET(SDL2_SEARCH_PATHS $ENV{VITASDK}/arm-vita-eabi)
endif()

if(NOT SDL2_IMAGE_INCLUDE_DIR AND SDL2IMAGE_INCLUDE_DIR)
  set(SDL2_IMAGE_INCLUDE_DIR ${SDL2IMAGE_INCLUDE_DIR} CACHE PATH "directory cache entry initialized from old variable name")
endif()

if(NOT SDL2_IMAGE_INCLUDE_DIR AND APPLE)
  # Try to find the include in the SDL2_image framework bundle
  # This fixes CMake finding the header from SDL_image 1.2 when both 1.2 and 2.0 are installed
  find_path(SDL2_IMAGE_INCLUDE_DIR SDL2_image/SDL_image.h
    HINTS
      ENV SDL2IMAGEDIR
      ENV SDL2DIR
    PATH_SUFFIXES include include/SDL2
    PATHS ${SDL2_SEARCH_PATHS}
  )
  if (SDL2_IMAGE_INCLUDE_DIR)
    set(SDL2_IMAGE_INCLUDE_DIR "${SDL2_IMAGE_INCLUDE_DIR}/Headers")
  endif()
endif()

if(NOT APPLE OR NOT EXISTS "${SDL2_IMAGE_INCLUDE_DIR}/SDL_image.h")
  find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h
    HINTS
      ENV SDL2IMAGEDIR
      ENV SDL2DIR
    PATH_SUFFIXES include include/SDL2
    PATHS ${SDL2_SEARCH_PATHS}
  )
endif()

if(NOT SDL2_IMAGE_LIBRARY AND SDL2IMAGE_LIBRARY)
  set(SDL2_IMAGE_LIBRARY ${SDL2IMAGE_LIBRARY} CACHE FILEPATH "file cache entry initialized from old variable name")
endif()

find_library(SDL2_IMAGE_LIBRARY
  NAMES SDL2_image
  HINTS
    ENV SDL2IMAGEDIR
    ENV SDL2DIR
  PATH_SUFFIXES lib64 lib lib/${SDL2_PROCESSOR_ARCH}
  PATHS ${SDL2_SEARCH_PATHS}
)

if(SDL2_IMAGE_INCLUDE_DIR AND EXISTS "${SDL2_IMAGE_INCLUDE_DIR}/SDL_image.h")
    file(STRINGS "${SDL2_IMAGE_INCLUDE_DIR}/SDL_image.h" SDL2_IMAGE_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_IMAGE_MAJOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL2_IMAGE_INCLUDE_DIR}/SDL_image.h" SDL2_IMAGE_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_IMAGE_MINOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL2_IMAGE_INCLUDE_DIR}/SDL_image.h" SDL2_IMAGE_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_IMAGE_PATCHLEVEL[ \t]+[0-9]+$")
    string(REGEX REPLACE "^#define[ \t]+SDL_IMAGE_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_IMAGE_VERSION_MAJOR "${SDL2_IMAGE_VERSION_MAJOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL_IMAGE_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_IMAGE_VERSION_MINOR "${SDL2_IMAGE_VERSION_MINOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL_IMAGE_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_IMAGE_VERSION_PATCH "${SDL2_IMAGE_VERSION_PATCH_LINE}")
    set(SDL2_IMAGE_VERSION_STRING ${SDL2_IMAGE_VERSION_MAJOR}.${SDL2_IMAGE_VERSION_MINOR}.${SDL2_IMAGE_VERSION_PATCH})
    unset(SDL2_IMAGE_VERSION_MAJOR_LINE)
    unset(SDL2_IMAGE_VERSION_MINOR_LINE)
    unset(SDL2_IMAGE_VERSION_PATCH_LINE)
    unset(SDL2_IMAGE_VERSION_MAJOR)
    unset(SDL2_IMAGE_VERSION_MINOR)
    unset(SDL2_IMAGE_VERSION_PATCH)
endif()


set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY})
set(SDL2_IMAGE_INCLUDE_DIRS ${SDL2_IMAGE_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_image
                                  REQUIRED_VARS SDL2_IMAGE_LIBRARIES SDL2_IMAGE_INCLUDE_DIRS
                                  VERSION_VAR SDL2_IMAGE_VERSION_STRING)

# for backward compatiblity
set(SDL2IMAGE_LIBRARY ${SDL2_IMAGE_LIBRARIES})
set(SDL2IMAGE_INCLUDE_DIR ${SDL2_IMAGE_INCLUDE_DIRS})
set(SDL2IMAGE_FOUND ${SDL2_IMAGE_FOUND})

mark_as_advanced(SDL2_IMAGE_LIBRARY SDL2_IMAGE_INCLUDE_DIR)

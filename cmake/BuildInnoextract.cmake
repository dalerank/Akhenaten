# Build innoextract as a separate ExternalProject (not linked into akhenaten).
# Default: download Boost-free fork innoextract-nb and build it for the host platform.
# Override with -DINNOEXTRACT_SOURCE_DIR=... or a sibling ../innoextract checkout.
# Output: ${CMAKE_BINARY_DIR}/tools/innoextract/bin/innoextract[.exe]
#
# Tool deps (liblzma zlib bzip2): system packages, or innoextract FetchContent fallback.

include(ExternalProject)

set(INNOEXTRACT_GIT_REPOSITORY "https://github.com/dalerank/innoextract-nb.git"
    CACHE STRING "Git repository for innoextract helper sources")
# Track innoextract-nb main tip (not a pinned commit).
set(INNOEXTRACT_GIT_TAG "main"
    CACHE STRING "Git tag/branch/commit for innoextract helper sources")

set(INNOEXTRACT_SOURCE_DIR "" CACHE PATH
    "Optional local innoextract sources (skips git download when set / sibling ../innoextract exists)")

set(_innoextract_use_local FALSE)
if(INNOEXTRACT_SOURCE_DIR AND EXISTS "${INNOEXTRACT_SOURCE_DIR}/CMakeLists.txt")
    set(_innoextract_use_local TRUE)
else()
    get_filename_component(_akhenaten_parent "${CMAKE_SOURCE_DIR}" DIRECTORY)
    if(EXISTS "${_akhenaten_parent}/innoextract/CMakeLists.txt")
        set(INNOEXTRACT_SOURCE_DIR "${_akhenaten_parent}/innoextract")
        set(_innoextract_use_local TRUE)
        message(STATUS "innoextract: using sibling sources at ${INNOEXTRACT_SOURCE_DIR}")
    endif()
endif()

set(INNOEXTRACT_PREFIX "${CMAKE_BINARY_DIR}/external/innoextract")
set(INNOEXTRACT_INSTALL_DIR "${CMAKE_BINARY_DIR}/tools/innoextract")
set(INNOEXTRACT_EXE_NAME "innoextract${CMAKE_EXECUTABLE_SUFFIX}")
set(INNOEXTRACT_EXE "${INNOEXTRACT_INSTALL_DIR}/bin/${INNOEXTRACT_EXE_NAME}")

set(INNOEXTRACT_EXT_CONFIG "${CMAKE_BUILD_TYPE}")
if(NOT INNOEXTRACT_EXT_CONFIG OR INNOEXTRACT_EXT_CONFIG STREQUAL "None")
    set(INNOEXTRACT_EXT_CONFIG "Release")
endif()
if(CMAKE_CONFIGURATION_TYPES)
    # Multi-config generators: build a single Release tool binary (no debug CRT deps).
    set(INNOEXTRACT_EXT_CONFIG "Release")
endif()

# Shared system libs — static archives (libz.a etc.) are often missing on macOS/Windows
# without a package manager. innoextract's own default is OFF on Unix / ON on Win32.
set(INNOEXTRACT_CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${INNOEXTRACT_EXT_CONFIG}
    -DCMAKE_INSTALL_PREFIX=${INNOEXTRACT_INSTALL_DIR}
    -DUSE_STATIC_LIBS=OFF
    -DUSE_LZMA=ON
    -DBUILD_TESTS=OFF
    -DDEVELOPER=OFF
    -DCMAKE_POLICY_DEFAULT_CMP0091=NEW
)

if(CMAKE_C_COMPILER)
    list(APPEND INNOEXTRACT_CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER})
endif()
if(CMAKE_CXX_COMPILER)
    list(APPEND INNOEXTRACT_CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER})
endif()
if(CMAKE_OSX_ARCHITECTURES)
    list(APPEND INNOEXTRACT_CMAKE_ARGS -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES})
endif()
if(CMAKE_OSX_DEPLOYMENT_TARGET)
    list(APPEND INNOEXTRACT_CMAKE_ARGS -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET})
endif()

message(STATUS "innoextract: system liblzma/zlib/bzip2, or FetchContent inside innoextract")

set(INNOEXTRACT_EP_EXTRA_ARGS "")
if(CMAKE_CONFIGURATION_TYPES)
    list(APPEND INNOEXTRACT_EP_EXTRA_ARGS
        BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${INNOEXTRACT_EXT_CONFIG} --parallel
        INSTALL_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${INNOEXTRACT_EXT_CONFIG} --target install
    )
endif()

if(_innoextract_use_local)
    message(STATUS "innoextract: SOURCE_DIR=${INNOEXTRACT_SOURCE_DIR} (local)")
    ExternalProject_Add(innoextract_ext
        SOURCE_DIR ${INNOEXTRACT_SOURCE_DIR}
        BINARY_DIR ${INNOEXTRACT_PREFIX}/build
        PREFIX ${INNOEXTRACT_PREFIX}
        INSTALL_DIR ${INNOEXTRACT_INSTALL_DIR}
        CMAKE_ARGS ${INNOEXTRACT_CMAKE_ARGS}
        ${INNOEXTRACT_EP_EXTRA_ARGS}
        BUILD_BYPRODUCTS ${INNOEXTRACT_EXE}
        UPDATE_COMMAND ""
        DOWNLOAD_COMMAND ""
    )
else()
    message(STATUS "innoextract: downloading ${INNOEXTRACT_GIT_REPOSITORY} @ ${INNOEXTRACT_GIT_TAG}")
    ExternalProject_Add(innoextract_ext
        GIT_REPOSITORY ${INNOEXTRACT_GIT_REPOSITORY}
        GIT_TAG ${INNOEXTRACT_GIT_TAG}
        GIT_PROGRESS TRUE
        BINARY_DIR ${INNOEXTRACT_PREFIX}/build
        PREFIX ${INNOEXTRACT_PREFIX}
        INSTALL_DIR ${INNOEXTRACT_INSTALL_DIR}
        CMAKE_ARGS ${INNOEXTRACT_CMAKE_ARGS}
        ${INNOEXTRACT_EP_EXTRA_ARGS}
        BUILD_BYPRODUCTS ${INNOEXTRACT_EXE}
        # Keep tracking branch tips (e.g. main); local SOURCE_DIR path disables update above.
    )
endif()

message(STATUS "innoextract: BINARY_DIR=${INNOEXTRACT_PREFIX}/build")
message(STATUS "innoextract: INSTALL_DIR=${INNOEXTRACT_INSTALL_DIR}")

# Convenience target: build only the tool
add_custom_target(innoextract DEPENDS innoextract_ext)

# After akhenaten builds, copy tool next to the game binary / working directory.
function(akhenaten_copy_innoextract)
    if(NOT TARGET ${GAME})
        return()
    endif()

    add_dependencies(${GAME} innoextract_ext)

    add_custom_command(TARGET ${GAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${INNOEXTRACT_EXE}"
            "$<TARGET_FILE_DIR:${GAME}>/${INNOEXTRACT_EXE_NAME}"
        COMMENT "Copy innoextract next to ${GAME}"
        VERBATIM
    )

    set(_copy_dests "${CMAKE_BINARY_DIR}")
    if(DEFINED GAME_WORKING_DIRECTORY)
        list(APPEND _copy_dests "${GAME_WORKING_DIRECTORY}")
    endif()

    foreach(_dest IN LISTS _copy_dests)
        add_custom_command(TARGET ${GAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${_dest}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${INNOEXTRACT_EXE}"
                "${_dest}/${INNOEXTRACT_EXE_NAME}"
            COMMENT "Copy innoextract to ${_dest}"
            VERBATIM
        )
    endforeach()
endfunction()

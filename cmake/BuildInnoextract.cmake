# Build innoextract as a separate ExternalProject (not linked into akhenaten).
# Default: download Boost-free fork innoextract-nb and build it for the host platform.
# Override with -DINNOEXTRACT_SOURCE_DIR=... or a sibling ../innoextract checkout.
# Output: ${CMAKE_BINARY_DIR}/tools/innoextract/bin/innoextract[.exe]
#
# Tool deps (liblzma zlib bzip2): system packages, or optional vcpkg on Windows.

include(ExternalProject)

set(INNOEXTRACT_GIT_REPOSITORY "https://github.com/dalerank/innoextract-nb.git"
    CACHE STRING "Git repository for innoextract helper sources")
# Pin to a known-good tip of innoextract-nb (update intentionally).
set(INNOEXTRACT_GIT_TAG "9971ddb6ff9dca19f6baed2237c1b335884e47b5"
    CACHE STRING "Git tag/commit for innoextract helper sources")

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

# Optional vcpkg only for the helper tool (not used by akhenaten.exe).
set(INNOEXTRACT_VCPKG_ROOT "" CACHE PATH "Optional vcpkg root used only for building innoextract")
if(NOT INNOEXTRACT_VCPKG_ROOT)
    if(DEFINED ENV{VCPKG_ROOT} AND EXISTS "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        set(INNOEXTRACT_VCPKG_ROOT "$ENV{VCPKG_ROOT}")
    elseif(EXISTS "D:/Work/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(INNOEXTRACT_VCPKG_ROOT "D:/Work/vcpkg")
    endif()
endif()

set(INNOEXTRACT_VCPKG_TRIPLET "x64-windows-static" CACHE STRING "vcpkg triplet for innoextract (Windows)")

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

set(INNOEXTRACT_CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${INNOEXTRACT_EXT_CONFIG}
    -DCMAKE_INSTALL_PREFIX=${INNOEXTRACT_INSTALL_DIR}
    -DUSE_STATIC_LIBS=ON
    -DUSE_LZMA=ON
    -DBUILD_TESTS=OFF
    -DDEVELOPER=OFF
    -DCMAKE_POLICY_DEFAULT_CMP0091=NEW
)

if(INNOEXTRACT_VCPKG_ROOT)
    if(NOT EXISTS "${INNOEXTRACT_VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        message(FATAL_ERROR "INNOEXTRACT_VCPKG_ROOT is set but toolchain not found: ${INNOEXTRACT_VCPKG_ROOT}")
    endif()
    list(APPEND INNOEXTRACT_CMAKE_ARGS
        -DCMAKE_TOOLCHAIN_FILE=${INNOEXTRACT_VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
        -DVCPKG_TARGET_TRIPLET=${INNOEXTRACT_VCPKG_TRIPLET}
        -DVCPKG_MANIFEST_MODE=OFF
    )
    if(INNOEXTRACT_VCPKG_TRIPLET MATCHES "static")
        if(INNOEXTRACT_EXT_CONFIG STREQUAL "Debug")
            list(APPEND INNOEXTRACT_CMAKE_ARGS -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebug)
        else()
            list(APPEND INNOEXTRACT_CMAKE_ARGS -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded)
        endif()
    endif()
    message(STATUS "innoextract: using vcpkg at ${INNOEXTRACT_VCPKG_ROOT} (${INNOEXTRACT_VCPKG_TRIPLET})")
else()
    message(STATUS
        "innoextract: no vcpkg — ExternalProject will use system liblzma/zlib/bzip2 (find_package)")
endif()

if(CMAKE_C_COMPILER)
    list(APPEND INNOEXTRACT_CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER})
endif()
if(CMAKE_CXX_COMPILER)
    list(APPEND INNOEXTRACT_CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER})
endif()

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
        UPDATE_COMMAND ""
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

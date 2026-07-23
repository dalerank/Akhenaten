# Build unshield as a separate ExternalProject (InstallShield CAB extractor).
# Used when Installer/*.exe is not Inno Setup (e.g. Sierra/InstallShield Pharaoh demo).
# Source: sibling ../unshield or UNSHIELD_SOURCE_DIR.
# Deps (zlib): system packages via find_package.

include(ExternalProject)

set(UNSHIELD_SOURCE_DIR "" CACHE PATH "Path to unshield sources (default: ../unshield)")
if(NOT UNSHIELD_SOURCE_DIR)
    get_filename_component(_akhenaten_parent "${CMAKE_SOURCE_DIR}" DIRECTORY)
    set(UNSHIELD_SOURCE_DIR "${_akhenaten_parent}/unshield")
endif()

if(NOT EXISTS "${UNSHIELD_SOURCE_DIR}/CMakeLists.txt")
    message(STATUS "unshield: sources not found at ${UNSHIELD_SOURCE_DIR} — InstallShield fallback disabled")
    set(AKHENATEN_HAS_UNSHIELD FALSE)
    return()
endif()

set(AKHENATEN_HAS_UNSHIELD TRUE)

set(UNSHIELD_PREFIX "${CMAKE_BINARY_DIR}/external/unshield")
set(UNSHIELD_INSTALL_DIR "${CMAKE_BINARY_DIR}/tools/unshield")
set(UNSHIELD_EXE_NAME "unshield${CMAKE_EXECUTABLE_SUFFIX}")

set(UNSHIELD_EXT_CONFIG "${CMAKE_BUILD_TYPE}")
if(NOT UNSHIELD_EXT_CONFIG OR UNSHIELD_EXT_CONFIG STREQUAL "None")
    set(UNSHIELD_EXT_CONFIG "Release")
endif()
if(CMAKE_CONFIGURATION_TYPES)
    set(UNSHIELD_EXT_CONFIG "Release")
endif()

if(CMAKE_CONFIGURATION_TYPES)
    set(UNSHIELD_BUILT_REL "src/${UNSHIELD_EXT_CONFIG}/${UNSHIELD_EXE_NAME}")
else()
    set(UNSHIELD_BUILT_REL "src/${UNSHIELD_EXE_NAME}")
endif()
set(UNSHIELD_EXE "${UNSHIELD_INSTALL_DIR}/${UNSHIELD_EXE_NAME}")

set(UNSHIELD_CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${UNSHIELD_EXT_CONFIG}
    -DCMAKE_INSTALL_PREFIX=${UNSHIELD_INSTALL_DIR}
    -DBUILD_STATIC=ON
    -DUSE_OUR_OWN_MD5=ON
    -DBUILD_TESTING=OFF
    -DCMAKE_POLICY_DEFAULT_CMP0091=NEW
)

if(CMAKE_C_COMPILER)
    list(APPEND UNSHIELD_CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER})
endif()
if(CMAKE_CXX_COMPILER)
    list(APPEND UNSHIELD_CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER})
endif()
if(CMAKE_OSX_ARCHITECTURES)
    list(APPEND UNSHIELD_CMAKE_ARGS -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES})
endif()
if(CMAKE_OSX_DEPLOYMENT_TARGET)
    list(APPEND UNSHIELD_CMAKE_ARGS -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET})
endif()

message(STATUS "unshield: SOURCE_DIR=${UNSHIELD_SOURCE_DIR}")
message(STATUS "unshield: BINARY_DIR=${UNSHIELD_PREFIX}/build")
message(STATUS "unshield: ExternalProject uses system zlib (find_package)")

ExternalProject_Add(unshield_ext
    SOURCE_DIR ${UNSHIELD_SOURCE_DIR}
    BINARY_DIR ${UNSHIELD_PREFIX}/build
    PREFIX ${UNSHIELD_PREFIX}
    INSTALL_DIR ${UNSHIELD_INSTALL_DIR}
    CMAKE_ARGS ${UNSHIELD_CMAKE_ARGS}
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${UNSHIELD_EXT_CONFIG} --parallel
    INSTALL_COMMAND ${CMAKE_COMMAND} -E make_directory ${UNSHIELD_INSTALL_DIR}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                <BINARY_DIR>/${UNSHIELD_BUILT_REL}
                ${UNSHIELD_EXE}
    BUILD_BYPRODUCTS ${UNSHIELD_EXE}
    UPDATE_COMMAND ""
    DOWNLOAD_COMMAND ""
)

add_custom_target(unshield DEPENDS unshield_ext)

function(akhenaten_copy_unshield)
    if(NOT TARGET ${GAME} OR NOT AKHENATEN_HAS_UNSHIELD)
        return()
    endif()
    add_dependencies(${GAME} unshield_ext)
    add_custom_command(TARGET ${GAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${UNSHIELD_EXE}"
            "$<TARGET_FILE_DIR:${GAME}>/${UNSHIELD_EXE_NAME}"
        COMMENT "Copy unshield next to ${GAME}"
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
                "${UNSHIELD_EXE}"
                "${_dest}/${UNSHIELD_EXE_NAME}"
            COMMENT "Copy unshield to ${_dest}"
            VERBATIM
        )
    endforeach()
endfunction()

cmake_minimum_required(VERSION 3.13...3.26)
project(mujs C)

file(GLOB SOURCES_LIST "*.c")

add_library(${PROJECT_NAME} ${SOURCES_LIST})

set(EXTMUJS_INCLUDE_DIR ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(EXTMUJS_LIBRARY ${PROJECT_NAME}
    CACHE INTERNAL "${PROJECT_NAME}: Library Name" FORCE)
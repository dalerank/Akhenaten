project(extpng)

file(GLOB PNG_FILES "*.c")

include_directories(${PROJECT_SOURCE_DIR}/../zlib)
add_library(${PROJECT_NAME} STATIC ${PNG_FILES})

set(EXTPNG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(EXTPNG_LIBRARY ${PROJECT_NAME}
    CACHE INTERNAL "${PROJECT_NAME}: Library Name" FORCE)

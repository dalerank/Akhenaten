project(extexpat)

file(GLOB EXPAT_FILES "*.c")

add_library(${PROJECT_NAME} STATIC ${EXPAT_FILES})

if(NOT WIN32)
    add_compile_definitions(XML_DEV_URANDOM)
endif()

set(EXTEXPAT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(EXTEXPAT_LIBRARY ${PROJECT_NAME}
    CACHE INTERNAL "${PROJECT_NAME}: Library Name" FORCE)

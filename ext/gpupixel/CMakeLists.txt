cmake_minimum_required(VERSION 3.13...3.26)
project(gpupixel CXX)

file(GLOB CORE_FILES ${PROJECT_SOURCE_DIR}/core/*.cc)
file(GLOB FILTER_FILES ${PROJECT_SOURCE_DIR}/filter/*.cc)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cc)
file(GLOB TARGET_FILES ${PROJECT_SOURCE_DIR}/target/*.cc)
file(GLOB UTILS_FILES ${PROJECT_SOURCE_DIR}/utils/*.cc)

set(SOURCES_LIST 
     ${CORE_FILES}
     ${FILTER_FILES}
     ${SOURCE_FILES}
     ${TARGET_FILES}
     ${UTILS_FILES}	 
)

if (MSVC)

elseif()
  add_compile_definitions("-Wno-absolute-value")
endif()

add_library(${PROJECT_NAME} STATIC ${SOURCES_LIST})
include_directories(${PROJECT_SOURCE_DIR}/core)

if (WIN32 OR UNIX OR APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC GPUPIXEL_GL_SHADER)
elseif (ANDROID OR IOS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC GPUPIXEL_GLES_SHADER)
endif()

set(GPUPIXEL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/core
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(GPUPIXEL_LIBRARY ${PROJECT_NAME}
    CACHE INTERNAL "${PROJECT_NAME}: Library Name" FORCE)

# Link Tracy if it's available
if(TARGET Tracy::TracyClient)
    target_link_libraries(${PROJECT_NAME} PUBLIC Tracy::TracyClient)
endif()
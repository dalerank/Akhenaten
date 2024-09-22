cmake_minimum_required(VERSION 3.0)
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

add_library(${PROJECT_NAME} ${SOURCES_LIST})

set(GPUPIXEL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/core
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(GPUPIXEL_LIBRARY ${PROJECT_NAME}
    CACHE INTERNAL "${PROJECT_NAME}: Library Name" FORCE)

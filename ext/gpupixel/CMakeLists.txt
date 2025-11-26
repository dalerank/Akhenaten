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

add_library(${PROJECT_NAME} STATIC ${SOURCES_LIST})
include_directories(${PROJECT_SOURCE_DIR}/core)

if (MSVC)
    # Suppress warning C4005: macro redefinition
    target_compile_options(${PROJECT_NAME} PRIVATE /wd4005)
else()
  # Suppress warning about macro redefinition
  target_compile_options(${PROJECT_NAME} PRIVATE -Wno-macro-redefined)
endif()

if (WIN32 OR UNIX OR APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC GPUPIXEL_GL_SHADER)
    # Find OpenGL for Linux/Unix systems
    if(UNIX AND NOT APPLE)
        find_package(OpenGL QUIET)
        if(OpenGL_FOUND)
            target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
        else()
            # Fallback: try to find OpenGL headers manually
            find_path(OPENGL_INCLUDE_DIR GL/gl.h
                PATHS
                    /usr/include
                    /usr/local/include
                    /opt/local/include
            )
            if(OPENGL_INCLUDE_DIR)
                target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
                # Try to find and link OpenGL library
                find_library(OPENGL_LIBRARY
                    NAMES GL gl
                    PATHS
                        /usr/lib
                        /usr/lib/x86_64-linux-gnu
                        /usr/local/lib
                        /opt/local/lib
                )
                if(OPENGL_LIBRARY)
                    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARY})
                endif()
            else()
                message(WARNING "OpenGL not found. GPUPixel may not compile correctly. Install libgl1-mesa-dev or mesa-libGL-devel")
            endif()
        endif()
    endif()
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
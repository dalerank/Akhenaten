# This file is used to build SDL2_mixer as a standalone project
# It should be called from the main CMakeLists.txt with: cmake -P BuildSDL2_mixer.cmake
# Required variables: SDL2_MIXER_SOURCE_DIR, SDL2_MIXER_BUILD_DIR, SDL2_MIXER_INSTALL_DIR, SDL2_ROOT, SDL2_MIXER_ADDITIONAL_CMAKE_ARGS

# Create build and install directories
file(MAKE_DIRECTORY ${SDL2_MIXER_BUILD_DIR})
file(MAKE_DIRECTORY ${SDL2_MIXER_INSTALL_DIR})
file(MAKE_DIRECTORY ${SDL2_MIXER_INSTALL_DIR}/include)

set(SDL2_MIXER_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${SDL2_MIXER_INSTALL_DIR}
    -DBUILD_SHARED_LIBS=OFF
    -DSDL2MIXER_SHARED=OFF
    -DSDL2MIXER_STATIC=ON
    -DSDL2MIXER_SAMPLES=OFF
    -DSDL2MIXER_VENDORED=ON
    -DSDL2_SHARED=OFF
    -DSDL2_STATIC=ON
    -DSDL2_DIR=${SDL2_ROOT}/lib/cmake/SDL2
    -DSDL2_ROOT=${SDL2_ROOT}
)

# Pass through macOS deployment target if defined
if(APPLE AND DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
    list(APPEND SDL2_MIXER_CMAKE_ARGS -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET})
endif()

# Pass through macOS architectures if defined
if(APPLE AND DEFINED CMAKE_OSX_ARCHITECTURES)
    list(APPEND SDL2_MIXER_CMAKE_ARGS -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES})
endif()

if(SDL2_MIXER_IS_MSVC)
    # Multi-config generator (Visual Studio)
    message(STATUS "Configuring SDL2_mixer...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -S ${SDL2_MIXER_SOURCE_DIR} -B ${SDL2_MIXER_BUILD_DIR} ${SDL2_MIXER_CMAKE_ARGS} ${SDL2_MIXER_ADDITIONAL_CMAKE_ARGS}
        WORKING_DIRECTORY ${SDL2_MIXER_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
    
    message(STATUS "Building SDL2_mixer for Release/Debug...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${SDL2_MIXER_BUILD_DIR} --config Debug
        RESULT_VARIABLE BUILD_DEBUG_RESULT
    )
      
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${SDL2_MIXER_BUILD_DIR} --config Release
        RESULT_VARIABLE BUILD_RELEASE_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${SDL2_MIXER_BUILD_DIR} --config Debug --prefix ${SDL2_MIXER_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_DEBUG_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${SDL2_MIXER_BUILD_DIR} --config Release --prefix ${SDL2_MIXER_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_RELEASE_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_MIXER_BUILD_DIR}/Release/SDL2_mixer-static.lib ${SDL2_MIXER_INSTALL_DIR}/SDL2_mixer-static.lib
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_MIXER_BUILD_DIR}/Debug/SDL2_mixer-staticd.lib ${SDL2_MIXER_INSTALL_DIR}/SDL2_mixer-staticd.lib
    )
                 
    if(EXISTS "${SDL2_MIXER_INSTALL_DIR}/SDL2_mixer-static.lib" OR EXISTS "${SDL2_MIXER_INSTALL_DIR}/SDL2_mixer-staticd.lib")
        message(STATUS "SDL2_mixer: Installation verified successfully")
    else()
        message(WARNING "SDL2_mixer: Library files not found in ${SDL2_MIXER_INSTALL_DIR}")
    endif()
else()
    message(STATUS "Configuring SDL2_mixer...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} ${SDL2_MIXER_SOURCE_DIR} ${SDL2_MIXER_CMAKE_ARGS} ${SDL2_MIXER_ADDITIONAL_CMAKE_ARGS} -B ${SDL2_MIXER_BUILD_DIR} -S ${SDL2_MIXER_SOURCE_DIR}
        WORKING_DIRECTORY ${SDL2_MIXER_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
    
    if(NOT CONFIGURE_RESULT EQUAL 0)
        message(FATAL_ERROR "SDL2_mixer: Configuration failed with exit code ${CONFIGURE_RESULT}")
    endif()
      
    message(STATUS "Building SDL2_mixer...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${SDL2_MIXER_BUILD_DIR} --parallel
        RESULT_VARIABLE BUILD_RESULT
        OUTPUT_VARIABLE BUILD_OUTPUT
        ERROR_VARIABLE BUILD_ERROR
    )
    
    message(STATUS "Installing SDL2_mixer...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${SDL2_MIXER_BUILD_DIR} --prefix ${SDL2_MIXER_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_RESULT
    )
        
    # After install, the library should be in lib/ subdirectory
    # SDL2_mixer might produce different library names, so check multiple possibilities
    set(SDL2_MIXER_LIB_BUILD_PATHS
        "${SDL2_MIXER_BUILD_DIR}/libSDL2_mixer.a"
        "${SDL2_MIXER_BUILD_DIR}/libSDL2_mixer-static.a"
        "${SDL2_MIXER_BUILD_DIR}/SDL2_mixer/libSDL2_mixer.a"
        "${SDL2_MIXER_BUILD_DIR}/SDL2_mixer/libSDL2_mixer-static.a"
    )

    set(SDL2_MIXER_LIB_INSTALL_PATHS
        "${SDL2_MIXER_INSTALL_DIR}/lib/libSDL2_mixer.a"
        "${SDL2_MIXER_INSTALL_DIR}/lib/libSDL2_mixer-static.a"
        "${SDL2_MIXER_INSTALL_DIR}/lib64/libSDL2_mixer.a"
        "${SDL2_MIXER_INSTALL_DIR}/lib64/libSDL2_mixer-static.a"
    )

    set(SDL2_MIXER_LIB_FINAL_PATH "${SDL2_MIXER_INSTALL_DIR}/libSDL2_mixer-static.a")
    
    # Find and copy library from install directory first
    set(SDL2_MIXER_LIB_FOUND FALSE)
    foreach(LIB_PATH ${SDL2_MIXER_LIB_INSTALL_PATHS})
        if(EXISTS "${LIB_PATH}")
            file(COPY ${LIB_PATH} DESTINATION ${SDL2_MIXER_INSTALL_DIR})
            get_filename_component(LIB_NAME ${LIB_PATH} NAME)
            if(NOT "${LIB_NAME}" STREQUAL "libSDL2_mixer-static.a")
                # Rename to expected name if different
                file(RENAME "${SDL2_MIXER_INSTALL_DIR}/${LIB_NAME}" "${SDL2_MIXER_LIB_FINAL_PATH}")
            endif()
            message(STATUS "SDL2_mixer: Copied library from ${LIB_PATH} to ${SDL2_MIXER_LIB_FINAL_PATH}")
            set(SDL2_MIXER_LIB_FOUND TRUE)
            break()
        endif()
    endforeach()
    
    # If not found in install directory, try build directory
    if(NOT SDL2_MIXER_LIB_FOUND)
        foreach(LIB_PATH ${SDL2_MIXER_LIB_BUILD_PATHS})
            if(EXISTS "${LIB_PATH}")
                file(COPY ${LIB_PATH} DESTINATION ${SDL2_MIXER_INSTALL_DIR})
                get_filename_component(LIB_NAME ${LIB_PATH} NAME)
                if(NOT "${LIB_NAME}" STREQUAL "libSDL2_mixer-static.a")
                    # Rename to expected name if different
                    file(RENAME "${SDL2_MIXER_INSTALL_DIR}/${LIB_NAME}" "${SDL2_MIXER_LIB_FINAL_PATH}")
                endif()
                message(STATUS "SDL2_mixer: Copied library from ${LIB_PATH} to ${SDL2_MIXER_LIB_FINAL_PATH}")
                set(SDL2_MIXER_LIB_FOUND TRUE)
                break()
            endif()
        endforeach()
    endif()
  
    # Verify header installation and copy if needed
    # SDL2_mixer's cmake --install should install headers to include/SDL2/ or include/
    set(SDL2_MIXER_HEADERS_FOUND FALSE)
    if(EXISTS "${SDL2_MIXER_INSTALL_DIR}/include/SDL2/SDL_mixer.h")
        message(STATUS "SDL2_mixer: Headers found in ${SDL2_MIXER_INSTALL_DIR}/include/SDL2")
        set(SDL2_MIXER_HEADERS_FOUND TRUE)
    elseif(EXISTS "${SDL2_MIXER_INSTALL_DIR}/include/SDL_mixer.h")
        message(STATUS "SDL2_mixer: Headers found in ${SDL2_MIXER_INSTALL_DIR}/include")
        set(SDL2_MIXER_HEADERS_FOUND TRUE)
    endif()
    
    # If headers not found, try to copy from source
    if(NOT SDL2_MIXER_HEADERS_FOUND)
        if(EXISTS "${SDL2_MIXER_SOURCE_DIR}/include/SDL2")
            file(COPY ${SDL2_MIXER_SOURCE_DIR}/include DESTINATION ${SDL2_MIXER_INSTALL_DIR})
            message(STATUS "SDL2_mixer: Copied headers from ${SDL2_MIXER_SOURCE_DIR}/include to ${SDL2_MIXER_INSTALL_DIR}/include")
        elseif(EXISTS "${SDL2_MIXER_SOURCE_DIR}/include")
            file(COPY ${SDL2_MIXER_SOURCE_DIR}/include DESTINATION ${SDL2_MIXER_INSTALL_DIR})
            message(STATUS "SDL2_mixer: Copied headers from ${SDL2_MIXER_SOURCE_DIR}/include to ${SDL2_MIXER_INSTALL_DIR}/include")
        else()
            message(WARNING "SDL2_mixer: Headers not found in source directory ${SDL2_MIXER_SOURCE_DIR}/include")
        endif()
    endif()
    
    # Final verification
    if(EXISTS "${SDL2_MIXER_INSTALL_DIR}/include/SDL2/SDL_mixer.h")
        message(STATUS "SDL2_mixer: Headers verified at ${SDL2_MIXER_INSTALL_DIR}/include/SDL2/SDL_mixer.h")
    elseif(EXISTS "${SDL2_MIXER_INSTALL_DIR}/include/SDL_mixer.h")
        message(STATUS "SDL2_mixer: Headers verified at ${SDL2_MIXER_INSTALL_DIR}/include/SDL_mixer.h")
    else()
        message(WARNING "SDL2_mixer: Headers not found after installation. Checked:")
        message(WARNING "  - ${SDL2_MIXER_INSTALL_DIR}/include/SDL2/SDL_mixer.h")
        message(WARNING "  - ${SDL2_MIXER_INSTALL_DIR}/include/SDL_mixer.h")
    endif()
       
    # Verify installation
    message(STATUS "SDL2_mixer: Verifying installation in ${SDL2_MIXER_INSTALL_DIR}")
    if(EXISTS "${SDL2_MIXER_LIB_FINAL_PATH}")
        message(STATUS "SDL2_mixer: Found library: ${SDL2_MIXER_LIB_FINAL_PATH}")
    else()
        # Check all possible paths
        set(SDL2_MIXER_VERIFY_FOUND FALSE)
        foreach(CHECK_PATH ${SDL2_MIXER_LIB_INSTALL_PATHS} ${SDL2_MIXER_LIB_BUILD_PATHS})
            if(EXISTS "${CHECK_PATH}")
                message(STATUS "SDL2_mixer: Found library: ${CHECK_PATH}")
                set(SDL2_MIXER_VERIFY_FOUND TRUE)
                break()
            endif()
        endforeach()
        
        if(NOT SDL2_MIXER_VERIFY_FOUND)
            message(WARNING "SDL2_mixer: Library files not found in ${SDL2_MIXER_INSTALL_DIR}")
            message(WARNING "SDL2_mixer: Checked paths:")
            foreach(CHECK_PATH ${SDL2_MIXER_LIB_INSTALL_PATHS} ${SDL2_MIXER_LIB_BUILD_PATHS})
                message(WARNING "  - ${CHECK_PATH}")
            endforeach()
        endif()
    endif()
endif()

message(STATUS "SDL2_mixer build completed successfully")


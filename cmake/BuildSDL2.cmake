# This file is used to build SDL2 as a standalone project
# It should be called from the main CMakeLists.txt with: cmake -P BuildSDL2.cmake
# Required variables: SDL2_SOURCE_DIR, SDL2_BUILD_DIR, SDL2_INSTALL_DIR

# Create build and install directories
file(MAKE_DIRECTORY ${SDL2_BUILD_DIR})
file(MAKE_DIRECTORY ${SDL2_INSTALL_DIR})
file(MAKE_DIRECTORY ${SDL2_INSTALL_DIR}/include)

set(SDL2_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${SDL2_INSTALL_DIR}
    -DSDL_SHARED=OFF
    -DSDL_STATIC=ON
    -DSDL_STATIC_PIC=ON
    -DSDL_TEST=OFF
)

# Pass through macOS deployment target if defined
if(APPLE AND DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
    list(APPEND SDL2_CMAKE_ARGS -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET})
endif()

# Pass through macOS architectures if defined
if(APPLE AND DEFINED CMAKE_OSX_ARCHITECTURES)
    list(APPEND SDL2_CMAKE_ARGS -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES})
endif()

if(SDL2_IS_MSVC)
    # Multi-config generator (Visual Studio)
    message(STATUS "Configuring SDL2...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -S ${SDL2_SOURCE_DIR} -B ${SDL2_BUILD_DIR} ${SDL2_CMAKE_ARGS}
        WORKING_DIRECTORY ${SDL2_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
    
    message(STATUS "Building SDL2 for Release/Debug...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${SDL2_BUILD_DIR} --config Debug
        RESULT_VARIABLE BUILD_DEBUG_RESULT
    )
      
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${SDL2_BUILD_DIR} --config Release
        RESULT_VARIABLE BUILD_RELEASE_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${SDL2_BUILD_DIR} --config Debug --prefix ${SDL2_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_DEBUG_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${SDL2_BUILD_DIR} --config Release --prefix ${SDL2_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_RELEASE_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_BUILD_DIR}/Release/SDL2-static.lib ${SDL2_INSTALL_DIR}/SDL2-static.lib
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_BUILD_DIR}/Debug/SDL2-staticd.lib ${SDL2_INSTALL_DIR}/SDL2-staticd.lib
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_BUILD_DIR}/Release/SDL2main.lib ${SDL2_INSTALL_DIR}/SDL2main.lib
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_BUILD_DIR}/Debug/SDL2maind.lib ${SDL2_INSTALL_DIR}/SDL2maind.lib
    )
                 
    if(EXISTS "${SDL2_INSTALL_DIR}/SDL2-static.lib" OR EXISTS "${SDL2_INSTALL_DIR}/SDL2-staticd.lib")
        message(STATUS "SDL2: Installation verified successfully")
    else()
        message(WARNING "SDL2: Library files not found in ${SDL2_INSTALL_DIR}")
    endif()
else()
    message(STATUS "Configuring SDL2...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} ${SDL2_SOURCE_DIR} ${SDL2_CMAKE_ARGS} -B ${SDL2_BUILD_DIR} -S ${SDL2_SOURCE_DIR}
        WORKING_DIRECTORY ${SDL2_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
    
    if(NOT CONFIGURE_RESULT EQUAL 0)
        message(FATAL_ERROR "SDL2: Configuration failed with exit code ${CONFIGURE_RESULT}")
    endif()
      
    message(STATUS "Building SDL2...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${SDL2_BUILD_DIR} --parallel
        RESULT_VARIABLE BUILD_RESULT
        OUTPUT_VARIABLE BUILD_OUTPUT
        ERROR_VARIABLE BUILD_ERROR
    )
    
    message(STATUS "Installing SDL2...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${SDL2_BUILD_DIR} --prefix ${SDL2_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_RESULT
    )
        
    # After install, the library should be in lib/ subdirectory
    # SDL2 might produce different library names, so check multiple possibilities
    set(SDL2_LIB_BUILD_PATHS
        "${SDL2_BUILD_DIR}/libSDL2.a"
        "${SDL2_BUILD_DIR}/libSDL2-static.a"
        "${SDL2_BUILD_DIR}/SDL2/libSDL2.a"
        "${SDL2_BUILD_DIR}/SDL2/libSDL2-static.a"
    )

    set(SDL2_LIB_INSTALL_PATHS
        "${SDL2_INSTALL_DIR}/lib/libSDL2.a"
        "${SDL2_INSTALL_DIR}/lib/libSDL2-static.a"
        "${SDL2_INSTALL_DIR}/lib64/libSDL2.a"
        "${SDL2_INSTALL_DIR}/lib64/libSDL2-static.a"
    )

    set(SDL2_LIB_FINAL_PATH "${SDL2_INSTALL_DIR}/libSDL2-static.a")
    
    # Find and copy library from install directory first
    set(SDL2_LIB_FOUND FALSE)
    foreach(LIB_PATH ${SDL2_LIB_INSTALL_PATHS})
        if(EXISTS "${LIB_PATH}")
            file(COPY ${LIB_PATH} DESTINATION ${SDL2_INSTALL_DIR})
            get_filename_component(LIB_NAME ${LIB_PATH} NAME)
            if(NOT "${LIB_NAME}" STREQUAL "libSDL2-static.a")
                # Rename to expected name if different
                file(RENAME "${SDL2_INSTALL_DIR}/${LIB_NAME}" "${SDL2_LIB_FINAL_PATH}")
            endif()
            message(STATUS "SDL2: Copied library from ${LIB_PATH} to ${SDL2_LIB_FINAL_PATH}")
            set(SDL2_LIB_FOUND TRUE)
            break()
        endif()
    endforeach()
    
    # If not found in install directory, try build directory
    if(NOT SDL2_LIB_FOUND)
        foreach(LIB_PATH ${SDL2_LIB_BUILD_PATHS})
            if(EXISTS "${LIB_PATH}")
                file(COPY ${LIB_PATH} DESTINATION ${SDL2_INSTALL_DIR})
                get_filename_component(LIB_NAME ${LIB_PATH} NAME)
                if(NOT "${LIB_NAME}" STREQUAL "libSDL2-static.a")
                    # Rename to expected name if different
                    file(RENAME "${SDL2_INSTALL_DIR}/${LIB_NAME}" "${SDL2_LIB_FINAL_PATH}")
                endif()
                message(STATUS "SDL2: Copied library from ${LIB_PATH} to ${SDL2_LIB_FINAL_PATH}")
                set(SDL2_LIB_FOUND TRUE)
                break()
            endif()
        endforeach()
    endif()
    
  
    # Verify header installation and copy if needed
    # SDL2's cmake --install should install headers to include/SDL2/
    set(SDL2_HEADERS_FOUND FALSE)
    if(EXISTS "${SDL2_INSTALL_DIR}/include/SDL2/SDL.h")
        message(STATUS "SDL2: Headers found in ${SDL2_INSTALL_DIR}/include/SDL2")
        set(SDL2_HEADERS_FOUND TRUE)
    elseif(EXISTS "${SDL2_INSTALL_DIR}/include/SDL.h")
        message(STATUS "SDL2: Headers found in ${SDL2_INSTALL_DIR}/include")
        set(SDL2_HEADERS_FOUND TRUE)
    endif()
    
    # If headers not found, try to copy from source
    if(NOT SDL2_HEADERS_FOUND)
        if(EXISTS "${SDL2_SOURCE_DIR}/include/SDL2")
            file(COPY ${SDL2_SOURCE_DIR}/include DESTINATION ${SDL2_INSTALL_DIR})
            message(STATUS "SDL2: Copied headers from ${SDL2_SOURCE_DIR}/include to ${SDL2_INSTALL_DIR}/include")
        elseif(EXISTS "${SDL2_SOURCE_DIR}/include")
            file(COPY ${SDL2_SOURCE_DIR}/include DESTINATION ${SDL2_INSTALL_DIR})
            message(STATUS "SDL2: Copied headers from ${SDL2_SOURCE_DIR}/include to ${SDL2_INSTALL_DIR}/include")
        else()
            message(WARNING "SDL2: Headers not found in source directory ${SDL2_SOURCE_DIR}/include")
        endif()
    endif()
    
    # Final verification
    if(EXISTS "${SDL2_INSTALL_DIR}/include/SDL2/SDL.h")
        message(STATUS "SDL2: Headers verified at ${SDL2_INSTALL_DIR}/include/SDL2/SDL.h")
    elseif(EXISTS "${SDL2_INSTALL_DIR}/include/SDL.h")
        message(STATUS "SDL2: Headers verified at ${SDL2_INSTALL_DIR}/include/SDL.h")
    else()
        message(WARNING "SDL2: Headers not found after installation. Checked:")
        message(WARNING "  - ${SDL2_INSTALL_DIR}/include/SDL2/SDL.h")
        message(WARNING "  - ${SDL2_INSTALL_DIR}/include/SDL.h")
    endif()
       
    # Verify installation
    message(STATUS "SDL2: Verifying installation in ${SDL2_INSTALL_DIR}")
    if(EXISTS "${SDL2_LIB_FINAL_PATH}")
        message(STATUS "SDL2: Found library: ${SDL2_LIB_FINAL_PATH}")
    else()
        # Check all possible paths
        set(SDL2_VERIFY_FOUND FALSE)
        foreach(CHECK_PATH ${SDL2_LIB_INSTALL_PATHS} ${SDL2_LIB_BUILD_PATHS})
            if(EXISTS "${CHECK_PATH}")
                message(STATUS "SDL2: Found library: ${CHECK_PATH}")
                set(SDL2_VERIFY_FOUND TRUE)
                break()
            endif()
        endforeach()
        
        if(NOT SDL2_VERIFY_FOUND)
            message(WARNING "SDL2: Library files not found in ${SDL2_INSTALL_DIR}")
            message(WARNING "SDL2: Checked paths:")
            foreach(CHECK_PATH ${SDL2_LIB_INSTALL_PATHS} ${SDL2_LIB_BUILD_PATHS})
                message(WARNING "  - ${CHECK_PATH}")
            endforeach()
        endif()
    endif()
endif()

message(STATUS "SDL2 build completed successfully")


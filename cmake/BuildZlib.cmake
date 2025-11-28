# This file is used to build zlib as a standalone project
# It should be called from the main CMakeLists.txt with: cmake -P BuildZlib.cmake
# Required variables: ZLIB_SOURCE_DIR, ZLIB_BUILD_DIR, ZLIB_INSTALL_DIR, ZLIP_ADDITIONAL_CMAKE_ARGS

# Create build and install directories
file(MAKE_DIRECTORY ${ZLIB_BUILD_DIR})
file(MAKE_DIRECTORY ${ZLIB_INSTALL_DIR})
file(MAKE_DIRECTORY ${ZLIB_INSTALL_DIR}/include)

set(ZLIB_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${ZLIB_INSTALL_DIR}
    -DBUILD_SHARED_LIBS=OFF
    -DSKIP_INSTALL_ALL=ON
)

if(ZLIB_IS_MSVC)
    # Multi-config generator (Visual Studio)
    message(STATUS "Configuring zlib...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} ${ZLIB_CMAKE_ARGS} ${ZLIP_ADDITIONAL_CMAKE_ARGS} -B ${ZLIB_BUILD_DIR} -S ${ZLIB_SOURCE_DIR}
        WORKING_DIRECTORY ${ZLIB_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
       
    message(STATUS "Building zlib for Release/Debug...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${ZLIB_BUILD_DIR} --config Debug
        COMMAND ${CMAKE_COMMAND} --install ${ZLIB_BUILD_DIR} --config Debug --prefix ${ZLIB_INSTALL_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${ZLIB_BUILD_DIR} --config Release
        COMMAND ${CMAKE_COMMAND} --install ${ZLIB_BUILD_DIR} --config Release --prefix ${ZLIB_INSTALL_DIR}
        RESULT_VARIABLE BUILD_DEBUG_RESULT
    )

    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_BUILD_DIR}/Release/zlibstatic.lib ${ZLIB_INSTALL_DIR}/zlibstatic.lib
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_BUILD_DIR}/Debug/zlibstaticd.lib ${ZLIB_INSTALL_DIR}/zlibstaticd.lib
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_BUILD_DIR}/zconf.h ${ZLIB_INSTALL_DIR}/include/zconf.h
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_SOURCE_DIR}/zlib.h ${ZLIB_INSTALL_DIR}/include/zlib.h
        RESULT_VARIABLE BUILD_DEBUG_RESULT
    )
               
    # Verify installation
    message(STATUS "zlib: Verifying installation in ${ZLIB_INSTALL_DIR}")
    if(EXISTS "${ZLIB_INSTALL_DIR}/zlibstatic.lib")
        message(STATUS "zlib: Found Release library: ${ZLIB_INSTALL_DIR}/zlibstatic.lib")
    endif()
    
    if(EXISTS "${ZLIB_INSTALL_DIR}/zlibstaticd.lib")
        message(STATUS "zlib: Found Debug library: ${ZLIB_INSTALL_DIR}/zlibstaticd.lib")
    endif()

    if(EXISTS "${ZLIB_INSTALL_DIR}/zlibstatic.lib" OR EXISTS "${ZLIB_INSTALL_DIR}/zlibstaticd.lib")
        message(STATUS "zlib: Installation verified successfully")
    else()
        message(WARNING "zlib: Library files not found in ${ZLIB_INSTALL_DIR}")
    endif()
else()
    message(STATUS "Configuring zlib...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} ${ZLIB_CMAKE_ARGS} ${ZLIP_ADDITIONAL_CMAKE_ARGS} -B ${ZLIB_BUILD_DIR} -S ${ZLIB_SOURCE_DIR}
        WORKING_DIRECTORY ${ZLIB_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
    
    if(NOT CONFIGURE_RESULT EQUAL 0)
        message(FATAL_ERROR "zlib: Configuration failed with exit code ${CONFIGURE_RESULT}")
    endif()
      
    message(STATUS "Building zlib...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${ZLIB_BUILD_DIR} --parallel 1
        RESULT_VARIABLE BUILD_RESULT
        OUTPUT_VARIABLE BUILD_OUTPUT
        ERROR_VARIABLE BUILD_ERROR
    )
    
    if(NOT BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "zlib: Build failed with exit code ${BUILD_RESULT}\nBuild output: ${BUILD_OUTPUT}\nBuild error: ${BUILD_ERROR}")
    endif()
    
    message(STATUS "Installing zlib...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${ZLIB_BUILD_DIR} --prefix ${ZLIB_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_RESULT
    )
    
    if(NOT INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "zlib: Install failed with exit code ${INSTALL_RESULT}")
    endif()
    
    # After install, the library should be in lib/ subdirectory
    # But we also check the build directory as fallback
    # zlib might produce different library names, so check multiple possibilities
    set(ZLIB_LIB_BUILD_PATHS
        "${ZLIB_BUILD_DIR}/libzlibstatic.a"
        "${ZLIB_BUILD_DIR}/libz.a"
    )
    set(ZLIB_LIB_INSTALL_PATHS
        "${ZLIB_INSTALL_DIR}/lib/libzlibstatic.a"
        "${ZLIB_INSTALL_DIR}/lib/libz.a"
    )
    set(ZLIB_LIB_FINAL_PATH "${ZLIB_INSTALL_DIR}/libzlibstatic.a")
    
    # Find and copy library from install directory first
    set(ZLIB_LIB_FOUND FALSE)
    foreach(LIB_PATH ${ZLIB_LIB_INSTALL_PATHS})
        if(EXISTS "${LIB_PATH}")
            file(COPY ${LIB_PATH} DESTINATION ${ZLIB_INSTALL_DIR})
            get_filename_component(LIB_NAME ${LIB_PATH} NAME)
            if(NOT "${LIB_NAME}" STREQUAL "libzlibstatic.a")
                # Rename to expected name if different
                file(RENAME "${ZLIB_INSTALL_DIR}/${LIB_NAME}" "${ZLIB_LIB_FINAL_PATH}")
            endif()
            message(STATUS "zlib: Copied library from ${LIB_PATH} to ${ZLIB_LIB_FINAL_PATH}")
            set(ZLIB_LIB_FOUND TRUE)
            break()
        endif()
    endforeach()
    
    # If not found in install directory, try build directory
    if(NOT ZLIB_LIB_FOUND)
        foreach(LIB_PATH ${ZLIB_LIB_BUILD_PATHS})
            if(EXISTS "${LIB_PATH}")
                file(COPY ${LIB_PATH} DESTINATION ${ZLIB_INSTALL_DIR})
                get_filename_component(LIB_NAME ${LIB_PATH} NAME)
                if(NOT "${LIB_NAME}" STREQUAL "libzlibstatic.a")
                    # Rename to expected name if different
                    file(RENAME "${ZLIB_INSTALL_DIR}/${LIB_NAME}" "${ZLIB_LIB_FINAL_PATH}")
                endif()
                message(STATUS "zlib: Copied library from ${LIB_PATH} to ${ZLIB_LIB_FINAL_PATH}")
                set(ZLIB_LIB_FOUND TRUE)
                break()
            endif()
        endforeach()
    endif()
    
    if(NOT ZLIB_LIB_FOUND)
        message(WARNING "zlib: Library not found in expected locations")
        message(WARNING "zlib: Checked install paths: ${ZLIB_LIB_INSTALL_PATHS}")
        message(WARNING "zlib: Checked build paths: ${ZLIB_LIB_BUILD_PATHS}")
    endif()
    
    # Copy header files if needed
    if(EXISTS "${ZLIB_BUILD_DIR}/zconf.h")
        file(COPY ${ZLIB_BUILD_DIR}/zconf.h DESTINATION ${ZLIB_INSTALL_DIR}/include)
    endif()
    
    if(EXISTS "${ZLIB_SOURCE_DIR}/zlib.h")
        file(COPY ${ZLIB_SOURCE_DIR}/zlib.h DESTINATION ${ZLIB_INSTALL_DIR}/include)
    endif()
       
    # Verify installation
    message(STATUS "zlib: Verifying installation in ${ZLIB_INSTALL_DIR}")
    if(EXISTS "${ZLIB_LIB_FINAL_PATH}")
        message(STATUS "zlib: Found library: ${ZLIB_LIB_FINAL_PATH}")
    else()
        # Check all possible paths
        set(ZLIB_VERIFY_FOUND FALSE)
        foreach(CHECK_PATH ${ZLIB_LIB_INSTALL_PATHS} ${ZLIB_LIB_BUILD_PATHS})
            if(EXISTS "${CHECK_PATH}")
                message(STATUS "zlib: Found library: ${CHECK_PATH}")
                set(ZLIB_VERIFY_FOUND TRUE)
                break()
            endif()
        endforeach()
        
        if(NOT ZLIB_VERIFY_FOUND)
            message(WARNING "zlib: Library files not found in ${ZLIB_INSTALL_DIR}")
            message(WARNING "zlib: Checked paths:")
            foreach(CHECK_PATH ${ZLIB_LIB_INSTALL_PATHS} ${ZLIB_LIB_BUILD_PATHS})
                message(WARNING "  - ${CHECK_PATH}")
            endforeach()
        endif()
    endif()
endif()

message(STATUS "zlib build completed successfully")
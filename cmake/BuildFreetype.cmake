# This file is used to build freetype as a standalone project
# It should be called from the main CMakeLists.txt with: cmake -P BuildFreetype.cmake
# Required variables: FREETYPE_SOURCE_DIR, FREETYPE_BUILD_DIR, FREETYPE_INSTALL_DIR, ZLIB_ROOT

# Create build and install directories
file(MAKE_DIRECTORY ${FREETYPE_BUILD_DIR})
file(MAKE_DIRECTORY ${FREETYPE_INSTALL_DIR})
file(MAKE_DIRECTORY ${FREETYPE_INSTALL_DIR}/include)

set(FREETYPE_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${FREETYPE_INSTALL_DIR}
    -DBUILD_SHARED_LIBS=OFF
    -DFT_DISABLE_ZLIB=OFF
    -DFT_REQUIRE_ZLIB=ON
    -DFT_REQUIRE_HARFBUZZ=OFF
    -DFT_DISABLE_HARFBUZZ=ON
    -DFT_DISABLE_BZIP2=ON
    -DFT_DISABLE_PNG=ON
    -DFT_DISABLE_BROTLI=ON
)

# Set zlib path for freetype to find
if(DEFINED ZLIB_ROOT)
    set(FREETYPE_CMAKE_ARGS ${FREETYPE_CMAKE_ARGS}
        -DZLIB_ROOT=${ZLIB_ROOT}
        -DZLIB_INCLUDE_DIR=${ZLIB_ROOT}/include
        -DZLIB_LIBRARY=${ZLIB_LIBRARY}
    )
endif()

if(FREETYPE_IS_MSVC)
    # Multi-config generator (Visual Studio)
    message(STATUS "Configuring freetype...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -S ${FREETYPE_SOURCE_DIR} -B ${FREETYPE_BUILD_DIR} ${FREETYPE_CMAKE_ARGS}
        WORKING_DIRECTORY ${FREETYPE_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
    
    if(NOT CONFIGURE_RESULT EQUAL 0)
        message(FATAL_ERROR "freetype: Configuration failed with exit code ${CONFIGURE_RESULT}")
    endif()
    
    message(STATUS "Building freetype for Release/Debug...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${FREETYPE_BUILD_DIR} --config Debug
        RESULT_VARIABLE BUILD_DEBUG_RESULT
    )
      
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${FREETYPE_BUILD_DIR} --config Release
        RESULT_VARIABLE BUILD_RELEASE_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${FREETYPE_BUILD_DIR} --config Debug --prefix ${FREETYPE_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_DEBUG_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${FREETYPE_BUILD_DIR} --config Release --prefix ${FREETYPE_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_RELEASE_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FREETYPE_BUILD_DIR}/Release/freetype.lib ${FREETYPE_INSTALL_DIR}/freetype.lib
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FREETYPE_BUILD_DIR}/Debug/freetyped.lib ${FREETYPE_INSTALL_DIR}/freetyped.lib
    )
    
    # Verify installation
    if(EXISTS "${FREETYPE_INSTALL_DIR}/freetype.lib" OR EXISTS "${FREETYPE_INSTALL_DIR}/freetyped.lib")
        message(STATUS "freetype: Installation verified successfully")
    else()
        message(WARNING "freetype: Library files not found in ${FREETYPE_INSTALL_DIR}")
    endif()
else()
    message(STATUS "Configuring freetype...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} ${FREETYPE_SOURCE_DIR} ${FREETYPE_CMAKE_ARGS} -B ${FREETYPE_BUILD_DIR} -S ${FREETYPE_SOURCE_DIR}
        WORKING_DIRECTORY ${FREETYPE_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
    
    if(NOT CONFIGURE_RESULT EQUAL 0)
        message(FATAL_ERROR "freetype: Configuration failed with exit code ${CONFIGURE_RESULT}")
    endif()
      
    message(STATUS "Building freetype...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${FREETYPE_BUILD_DIR} --parallel
        RESULT_VARIABLE BUILD_RESULT
        OUTPUT_VARIABLE BUILD_OUTPUT
        ERROR_VARIABLE BUILD_ERROR
    )
    
    if(NOT BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "freetype: Build failed with exit code ${BUILD_RESULT}\nBuild output: ${BUILD_OUTPUT}\nBuild error: ${BUILD_ERROR}")
    endif()
    
    message(STATUS "Installing freetype...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${FREETYPE_BUILD_DIR} --prefix ${FREETYPE_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_RESULT
    )
    
    if(NOT INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "freetype: Install failed with exit code ${INSTALL_RESULT}")
    endif()
    
    # After install, the library should be in lib/ subdirectory
    # freetype might produce different library names, so check multiple possibilities
    set(FREETYPE_LIB_BUILD_PATHS
        "${FREETYPE_BUILD_DIR}/libfreetype.a"
        "${FREETYPE_BUILD_DIR}/freetype/libfreetype.a"
    )

    set(FREETYPE_LIB_INSTALL_PATHS
        "${FREETYPE_INSTALL_DIR}/lib/libfreetype.a"
        "${FREETYPE_INSTALL_DIR}/lib64/libfreetype.a"
    )

    set(FREETYPE_LIB_FINAL_PATH "${FREETYPE_INSTALL_DIR}/libfreetype.a")
    
    # Find and copy library from install directory first
    set(FREETYPE_LIB_FOUND FALSE)
    foreach(LIB_PATH ${FREETYPE_LIB_INSTALL_PATHS})
        if(EXISTS "${LIB_PATH}")
            file(COPY ${LIB_PATH} DESTINATION ${FREETYPE_INSTALL_DIR})
            get_filename_component(LIB_NAME ${LIB_PATH} NAME)
            if(NOT "${LIB_NAME}" STREQUAL "libfreetype.a")
                # Rename to expected name if different
                file(RENAME "${FREETYPE_INSTALL_DIR}/${LIB_NAME}" "${FREETYPE_LIB_FINAL_PATH}")
            endif()
            message(STATUS "freetype: Copied library from ${LIB_PATH} to ${FREETYPE_LIB_FINAL_PATH}")
            set(FREETYPE_LIB_FOUND TRUE)
            break()
        endif()
    endforeach()
    
    # If not found in install directory, try build directory
    if(NOT FREETYPE_LIB_FOUND)
        foreach(LIB_PATH ${FREETYPE_LIB_BUILD_PATHS})
            if(EXISTS "${LIB_PATH}")
                file(COPY ${LIB_PATH} DESTINATION ${FREETYPE_INSTALL_DIR})
                get_filename_component(LIB_NAME ${LIB_PATH} NAME)
                if(NOT "${LIB_NAME}" STREQUAL "libfreetype.a")
                    # Rename to expected name if different
                    file(RENAME "${FREETYPE_INSTALL_DIR}/${LIB_NAME}" "${FREETYPE_LIB_FINAL_PATH}")
                endif()
                message(STATUS "freetype: Copied library from ${LIB_PATH} to ${FREETYPE_LIB_FINAL_PATH}")
                set(FREETYPE_LIB_FOUND TRUE)
                break()
            endif()
        endforeach()
    endif()
  
    # Verify header installation and copy if needed
    # freetype's cmake --install should install headers to include/freetype2/
    set(FREETYPE_HEADERS_FOUND FALSE)
    if(EXISTS "${FREETYPE_INSTALL_DIR}/include/freetype2/freetype/freetype.h")
        message(STATUS "freetype: Headers found in ${FREETYPE_INSTALL_DIR}/include/freetype2")
        set(FREETYPE_HEADERS_FOUND TRUE)
    elseif(EXISTS "${FREETYPE_INSTALL_DIR}/include/freetype/freetype.h")
        message(STATUS "freetype: Headers found in ${FREETYPE_INSTALL_DIR}/include/freetype")
        set(FREETYPE_HEADERS_FOUND TRUE)
    endif()
    
    # If headers not found, try to copy from source
    if(NOT FREETYPE_HEADERS_FOUND)
        if(EXISTS "${FREETYPE_SOURCE_DIR}/include")
            file(COPY ${FREETYPE_SOURCE_DIR}/include DESTINATION ${FREETYPE_INSTALL_DIR})
            message(STATUS "freetype: Copied headers from ${FREETYPE_SOURCE_DIR}/include to ${FREETYPE_INSTALL_DIR}/include")
        else()
            message(WARNING "freetype: Headers not found in source directory ${FREETYPE_SOURCE_DIR}/include")
        endif()
    endif()
    
    # Final verification
    if(EXISTS "${FREETYPE_INSTALL_DIR}/include/freetype2/freetype/freetype.h")
        message(STATUS "freetype: Headers verified at ${FREETYPE_INSTALL_DIR}/include/freetype2/freetype/freetype.h")
    elseif(EXISTS "${FREETYPE_INSTALL_DIR}/include/freetype/freetype.h")
        message(STATUS "freetype: Headers verified at ${FREETYPE_INSTALL_DIR}/include/freetype/freetype.h")
    else()
        message(WARNING "freetype: Headers not found after installation. Checked:")
        message(WARNING "  - ${FREETYPE_INSTALL_DIR}/include/freetype2/freetype/freetype.h")
        message(WARNING "  - ${FREETYPE_INSTALL_DIR}/include/freetype/freetype.h")
    endif()
       
    # Verify installation
    message(STATUS "freetype: Verifying installation in ${FREETYPE_INSTALL_DIR}")
    if(EXISTS "${FREETYPE_LIB_FINAL_PATH}")
        message(STATUS "freetype: Found library: ${FREETYPE_LIB_FINAL_PATH}")
    else()
        # Check all possible paths
        set(FREETYPE_VERIFY_FOUND FALSE)
        foreach(CHECK_PATH ${FREETYPE_LIB_INSTALL_PATHS} ${FREETYPE_LIB_BUILD_PATHS})
            if(EXISTS "${CHECK_PATH}")
                message(STATUS "freetype: Found library: ${CHECK_PATH}")
                set(FREETYPE_VERIFY_FOUND TRUE)
                break()
            endif()
        endforeach()
        
        if(NOT FREETYPE_VERIFY_FOUND)
            message(WARNING "freetype: Library files not found in ${FREETYPE_INSTALL_DIR}")
            message(WARNING "freetype: Checked paths:")
            foreach(CHECK_PATH ${FREETYPE_LIB_INSTALL_PATHS} ${FREETYPE_LIB_BUILD_PATHS})
                message(WARNING "  - ${CHECK_PATH}")
            endforeach()
        endif()
    endif()
endif()

message(STATUS "freetype build completed successfully")


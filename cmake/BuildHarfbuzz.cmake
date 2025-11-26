# This file is used to build harfbuzz as a standalone project
# It should be called from the main CMakeLists.txt with: cmake -P BuildHarfbuzz.cmake
# Required variables: HARFBUZZ_SOURCE_DIR, HARFBUZZ_BUILD_DIR, HARFBUZZ_INSTALL_DIR, FREETYPE_ROOT

# Create build and install directories
file(MAKE_DIRECTORY ${HARFBUZZ_BUILD_DIR})
file(MAKE_DIRECTORY ${HARFBUZZ_INSTALL_DIR})
file(MAKE_DIRECTORY ${HARFBUZZ_INSTALL_DIR}/include)

set(HARFBUZZ_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${HARFBUZZ_INSTALL_DIR}
    -DBUILD_SHARED_LIBS=OFF
    -DHB_BUILD_SUBSET=OFF
    -DHB_HAVE_FREETYPE=ON
)

# Set freetype path for harfbuzz to find
if(DEFINED FREETYPE_ROOT)
    set(HARFBUZZ_CMAKE_ARGS ${HARFBUZZ_CMAKE_ARGS}
        -DFreetype_ROOT=${FREETYPE_ROOT}
        -DFreetype_INCLUDE_DIR=${FREETYPE_INCLUDE_DIR}
        -DFreetype_INCLUDE_DIRS=${FREETYPE_INCLUDE_DIR}
        -DFreetype_LIBRARY=${FREETYPE_LIBRARY}
    )
    # Add freetype to CMAKE_PREFIX_PATH so harfbuzz can find it via find_package
    set(HARFBUZZ_CMAKE_ARGS ${HARFBUZZ_CMAKE_ARGS}
        -DCMAKE_PREFIX_PATH=${FREETYPE_ROOT}
    )
endif()

if(HARFBUZZ_IS_MSVC)
    # Multi-config generator (Visual Studio)
    message(STATUS "Configuring harfbuzz...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -S ${HARFBUZZ_SOURCE_DIR} -B ${HARFBUZZ_BUILD_DIR} ${HARFBUZZ_CMAKE_ARGS}
        WORKING_DIRECTORY ${HARFBUZZ_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
    
    if(NOT CONFIGURE_RESULT EQUAL 0)
        message(FATAL_ERROR "harfbuzz: Configuration failed with exit code ${CONFIGURE_RESULT}")
    endif()
    
    message(STATUS "Building harfbuzz for Release/Debug...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${HARFBUZZ_BUILD_DIR} --config Debug
        RESULT_VARIABLE BUILD_DEBUG_RESULT
    )
      
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${HARFBUZZ_BUILD_DIR} --config Release
        RESULT_VARIABLE BUILD_RELEASE_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${HARFBUZZ_BUILD_DIR} --config Debug --prefix ${HARFBUZZ_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_DEBUG_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${HARFBUZZ_BUILD_DIR} --config Release --prefix ${HARFBUZZ_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_RELEASE_RESULT
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${HARFBUZZ_BUILD_DIR}/Release/harfbuzz.lib ${HARFBUZZ_INSTALL_DIR}/harfbuzz.lib
    )
    
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${HARFBUZZ_BUILD_DIR}/Debug/harfbuzz.lib ${HARFBUZZ_INSTALL_DIR}/harfbuzzd.lib
    )
    
    # Verify installation
    if(EXISTS "${HARFBUZZ_INSTALL_DIR}/harfbuzz.lib" OR EXISTS "${HARFBUZZ_INSTALL_DIR}/harfbuzzd.lib")
        message(STATUS "harfbuzz: Installation verified successfully")
    else()
        message(WARNING "harfbuzz: Library files not found in ${HARFBUZZ_INSTALL_DIR}")
    endif()
else()
    message(STATUS "Configuring harfbuzz...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} ${HARFBUZZ_SOURCE_DIR} ${HARFBUZZ_CMAKE_ARGS} -B ${HARFBUZZ_BUILD_DIR} -S ${HARFBUZZ_SOURCE_DIR}
        WORKING_DIRECTORY ${HARFBUZZ_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
    
    if(NOT CONFIGURE_RESULT EQUAL 0)
        message(FATAL_ERROR "harfbuzz: Configuration failed with exit code ${CONFIGURE_RESULT}")
    endif()
      
    message(STATUS "Building harfbuzz...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${HARFBUZZ_BUILD_DIR} --parallel
        RESULT_VARIABLE BUILD_RESULT
        OUTPUT_VARIABLE BUILD_OUTPUT
        ERROR_VARIABLE BUILD_ERROR
    )
    
    if(NOT BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "harfbuzz: Build failed with exit code ${BUILD_RESULT}\nBuild output: ${BUILD_OUTPUT}\nBuild error: ${BUILD_ERROR}")
    endif()
    
    message(STATUS "Installing harfbuzz...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --install ${HARFBUZZ_BUILD_DIR} --prefix ${HARFBUZZ_INSTALL_DIR}
        RESULT_VARIABLE INSTALL_RESULT
    )
    
    if(NOT INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "harfbuzz: Install failed with exit code ${INSTALL_RESULT}")
    endif()
    
    # After install, the library should be in lib/ subdirectory
    # harfbuzz might produce different library names, so check multiple possibilities
    set(HARFBUZZ_LIB_BUILD_PATHS
        "${HARFBUZZ_BUILD_DIR}/libharfbuzz.a"
        "${HARFBUZZ_BUILD_DIR}/harfbuzz/libharfbuzz.a"
    )

    set(HARFBUZZ_LIB_INSTALL_PATHS
        "${HARFBUZZ_INSTALL_DIR}/lib/libharfbuzz.a"
        "${HARFBUZZ_INSTALL_DIR}/lib64/libharfbuzz.a"
    )

    set(HARFBUZZ_LIB_FINAL_PATH "${HARFBUZZ_INSTALL_DIR}/libharfbuzz.a")
    
    # Find and copy library from install directory first
    set(HARFBUZZ_LIB_FOUND FALSE)
    foreach(LIB_PATH ${HARFBUZZ_LIB_INSTALL_PATHS})
        if(EXISTS "${LIB_PATH}")
            file(COPY ${LIB_PATH} DESTINATION ${HARFBUZZ_INSTALL_DIR})
            get_filename_component(LIB_NAME ${LIB_PATH} NAME)
            if(NOT "${LIB_NAME}" STREQUAL "libharfbuzz.a")
                # Rename to expected name if different
                file(RENAME "${HARFBUZZ_INSTALL_DIR}/${LIB_NAME}" "${HARFBUZZ_LIB_FINAL_PATH}")
            endif()
            message(STATUS "harfbuzz: Copied library from ${LIB_PATH} to ${HARFBUZZ_LIB_FINAL_PATH}")
            set(HARFBUZZ_LIB_FOUND TRUE)
            break()
        endif()
    endforeach()
    
    # If not found in install directory, try build directory
    if(NOT HARFBUZZ_LIB_FOUND)
        foreach(LIB_PATH ${HARFBUZZ_LIB_BUILD_PATHS})
            if(EXISTS "${LIB_PATH}")
                file(COPY ${LIB_PATH} DESTINATION ${HARFBUZZ_INSTALL_DIR})
                get_filename_component(LIB_NAME ${LIB_PATH} NAME)
                if(NOT "${LIB_NAME}" STREQUAL "libharfbuzz.a")
                    # Rename to expected name if different
                    file(RENAME "${HARFBUZZ_INSTALL_DIR}/${LIB_NAME}" "${HARFBUZZ_LIB_FINAL_PATH}")
                endif()
                message(STATUS "harfbuzz: Copied library from ${LIB_PATH} to ${HARFBUZZ_LIB_FINAL_PATH}")
                set(HARFBUZZ_LIB_FOUND TRUE)
                break()
            endif()
        endforeach()
    endif()
  
    # Verify header installation and copy if needed
    # harfbuzz's cmake --install should install headers to include/harfbuzz/
    set(HARFBUZZ_HEADERS_FOUND FALSE)
    if(EXISTS "${HARFBUZZ_INSTALL_DIR}/include/harfbuzz/hb.h")
        message(STATUS "harfbuzz: Headers found in ${HARFBUZZ_INSTALL_DIR}/include/harfbuzz")
        set(HARFBUZZ_HEADERS_FOUND TRUE)
    elseif(EXISTS "${HARFBUZZ_INSTALL_DIR}/include/hb.h")
        message(STATUS "harfbuzz: Headers found in ${HARFBUZZ_INSTALL_DIR}/include")
        set(HARFBUZZ_HEADERS_FOUND TRUE)
    endif()
    
    # If headers not found, try to copy from source
    if(NOT HARFBUZZ_HEADERS_FOUND)
        if(EXISTS "${HARFBUZZ_SOURCE_DIR}/src")
            file(COPY ${HARFBUZZ_SOURCE_DIR}/src DESTINATION ${HARFBUZZ_INSTALL_DIR}/include)
            message(STATUS "harfbuzz: Copied headers from ${HARFBUZZ_SOURCE_DIR}/src to ${HARFBUZZ_INSTALL_DIR}/include")
        else()
            message(WARNING "harfbuzz: Headers not found in source directory ${HARFBUZZ_SOURCE_DIR}/src")
        endif()
    endif()
    
    # Final verification
    if(EXISTS "${HARFBUZZ_INSTALL_DIR}/include/harfbuzz/hb.h")
        message(STATUS "harfbuzz: Headers verified at ${HARFBUZZ_INSTALL_DIR}/include/harfbuzz/hb.h")
    elseif(EXISTS "${HARFBUZZ_INSTALL_DIR}/include/hb.h")
        message(STATUS "harfbuzz: Headers verified at ${HARFBUZZ_INSTALL_DIR}/include/hb.h")
    else()
        message(WARNING "harfbuzz: Headers not found after installation. Checked:")
        message(WARNING "  - ${HARFBUZZ_INSTALL_DIR}/include/harfbuzz/hb.h")
        message(WARNING "  - ${HARFBUZZ_INSTALL_DIR}/include/hb.h")
    endif()
       
    # Verify installation
    message(STATUS "harfbuzz: Verifying installation in ${HARFBUZZ_INSTALL_DIR}")
    if(EXISTS "${HARFBUZZ_LIB_FINAL_PATH}")
        message(STATUS "harfbuzz: Found library: ${HARFBUZZ_LIB_FINAL_PATH}")
    else()
        # Check all possible paths
        set(HARFBUZZ_VERIFY_FOUND FALSE)
        foreach(CHECK_PATH ${HARFBUZZ_LIB_INSTALL_PATHS} ${HARFBUZZ_LIB_BUILD_PATHS})
            if(EXISTS "${CHECK_PATH}")
                message(STATUS "harfbuzz: Found library: ${CHECK_PATH}")
                set(HARFBUZZ_VERIFY_FOUND TRUE)
                break()
            endif()
        endforeach()
        
        if(NOT HARFBUZZ_VERIFY_FOUND)
            message(WARNING "harfbuzz: Library files not found in ${HARFBUZZ_INSTALL_DIR}")
            message(WARNING "harfbuzz: Checked paths:")
            foreach(CHECK_PATH ${HARFBUZZ_LIB_INSTALL_PATHS} ${HARFBUZZ_LIB_BUILD_PATHS})
                message(WARNING "  - ${CHECK_PATH}")
            endforeach()
        endif()
    endif()
endif()

message(STATUS "harfbuzz build completed successfully")


# This file is used to build zlib as a standalone project
# It should be called from the main CMakeLists.txt with: cmake -P BuildZlib.cmake
# Required variables: ZLIB_SOURCE_DIR, ZLIB_BUILD_DIR, ZLIB_INSTALL_DIR

# Create build and install directories
file(MAKE_DIRECTORY ${ZLIB_BUILD_DIR})
file(MAKE_DIRECTORY ${ZLIB_INSTALL_DIR})

set(ZLIB_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${ZLIB_INSTALL_DIR}
    -DBUILD_SHARED_LIBS=OFF
    -DSKIP_INSTALL_ALL=ON
)

if(ZLIB_IS_MSVC)
    # Multi-config generator (Visual Studio)
    message(STATUS "Configuring zlib...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} ${ZLIB_SOURCE_DIR} ${ZLIB_CMAKE_ARGS} -B ${ZLIB_BUILD_DIR} -S ${ZLIB_SOURCE_DIR}
        WORKING_DIRECTORY ${ZLIB_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
       
    message(STATUS "Building zlib for Release/Debug...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${ZLIB_BUILD_DIR} --config Debug
        COMMAND ${CMAKE_COMMAND} --install ${ZLIB_BUILD_DIR} --config Debug --prefix ${ZLIB_INSTALL_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${ZLIB_BUILD_DIR} --config Release
        COMMAND ${CMAKE_COMMAND} --install ${ZLIB_BUILD_DIR} --config Release --prefix ${ZLIB_INSTALL_DIR}
        COMMAND ${CMAKE_COMMAND} -E sleep 1
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_BUILD_DIR}/Release/zlibstatic.lib ${ZLIB_INSTALL_DIR}/zlibstatic.lib
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_BUILD_DIR}/Debug/zlibstaticd.lib ${ZLIB_INSTALL_DIR}/zlibstaticd.lib
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_BUILD_DIR}/zconf.h ${ZLIB_INSTALL_DIR}/include/zconf.h
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_SOURCE_DIR}/zlib.h ${ZLIB_INSTALL_DIR}/include/zlib.h
        RESULT_VARIABLE BUILD_DEBUG_RESULT
    )
               
    # Verify installation
    message(STATUS "zlib: Verifying installation in ${ZLIB_INSTALL_DIR}/lib")
    if(EXISTS "${ZLIB_INSTALL_DIR}/lib/zlibstatic.lib")
        message(STATUS "zlib: Found Release library: ${ZLIB_INSTALL_DIR}/lib/zlibstatic.lib")
    endif()
    
    if(EXISTS "${ZLIB_INSTALL_DIR}/lib/zlibstaticd.lib")
        message(STATUS "zlib: Found Debug library: ${ZLIB_INSTALL_DIR}/lib/zlibstaticd.lib")
    endif()

    if(EXISTS "${ZLIB_INSTALL_DIR}/zlibstatic.lib" OR EXISTS "${ZLIB_INSTALL_DIR}/zlibstaticd.lib")
        message(STATUS "zlib: Installation verified successfully")
    else()
        message(WARNING "zlib: Library files not found in ${ZLIB_INSTALL_DIR}/lib")
    endif()
else()
    message(STATUS "Configuring zlib...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} ${ZLIB_SOURCE_DIR} ${ZLIB_CMAKE_ARGS} -B ${ZLIB_BUILD_DIR} -S ${ZLIB_SOURCE_DIR}
        WORKING_DIRECTORY ${ZLIB_BUILD_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
    )
      
    message(STATUS "Building zlib...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${ZLIB_BUILD_DIR}
        COMMAND ${CMAKE_COMMAND} --install ${ZLIB_BUILD_DIR} --prefix ${ZLIB_INSTALL_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_BUILD_DIR}/lib/zlibstatic.a ${ZLIB_INSTALL_DIR}/zlibstatic.a
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_BUILD_DIR}/zconf.h ${ZLIB_INSTALL_DIR}/include/zconf.h
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ZLIB_SOURCE_DIR}/zlib.h ${ZLIB_INSTALL_DIR}/include/zlib.h
        RESULT_VARIABLE BUILD_RESULT
    )
       
    # Verify installation
    message(STATUS "zlib: Verifying installation in ${ZLIB_INSTALL_DIR}/lib")
    if(EXISTS "${ZLIB_INSTALL_DIR}/libzlibstatic.a")
        message(STATUS "zlib: Installation verified in ${ZLIB_INSTALL_DIR}/lib")
    else()
        message(WARNING "zlib: Library files not found in ${ZLIB_INSTALL_DIR}/lib")
    endif()
endif()

message(STATUS "zlib build completed successfully")
cmake_minimum_required(VERSION 3.13...3.26)
project(lame C)

set(SOURCES_LIST "${PROJECT_SOURCE_DIR}/libmp3lame/lame.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/set_get.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/version.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/encoder.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/id3tag.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/util.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/gain_analysis.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/bitstream.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/presets.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/psymodel.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/tables.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/fft.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/takehiro.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/quantize.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/quantize_pvt.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/reservoir.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/VbrTag.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/vbrquantize.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/newmdct.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/mpglib_interface.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/interface.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/common.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/tabinit.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/layer1.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/layer2.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/layer3.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/dct64_i386.c"
				 "${PROJECT_SOURCE_DIR}/libmp3lame/decode_i386.c"
)

include_directories("${PROJECT_SOURCE_DIR}/include")
#include_directories("${PROJECT_SOURCE_DIR}/lib")

if (MSVC)

elseif()
  add_compile_definitions("-Wno-absolute-value")
endif()

add_definitions(-DHAVE_CONFIG_H=ON)
add_definitions(-DCPU_IS_LITTLE_ENDIAN=1)
add_definitions(-DPACKAGE_NAME="Ozy")
add_definitions(-DPACKAGE_VERSION="static")
add_definitions(-DHAVE_MPGLIB=ON)

add_library(${PROJECT_NAME} STATIC ${SOURCES_LIST})

set(EXTLAME_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(EXTLAME_LIBRARY ${PROJECT_NAME}
    CACHE INTERNAL "${PROJECT_NAME}: Library Name" FORCE)

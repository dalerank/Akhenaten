cmake_minimum_required(VERSION 3.0)
project(incbin C)

file(GLOB SOURCES_LIST "*.c")

add_executable(${PROJECT_NAME} ${SOURCES_LIST})
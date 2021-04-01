cmake_minimum_required(VERSION 3.10)

project(emulator6502 LANGUAGES CXX VERSION 0.1)

set (CMAKE_CXX_STANDARD 17)

# Basic paths
set(EMULATOR6502_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCES_DIR ${EMULATOR6502_DIR}/src)
set(INCLUDES_DIR ${EMULATOR6502_DIR}/include)
set(TESTS_DIR ${EMULATOR6502_DIR}/tests)
set(INSTALL_DIR ${EMULATOR6502_DIR}/bin)

add_subdirectory(${SOURCES_DIR})

add_subdirectory(external/Catch2)

add_executable(Emulator6502Tests ${TESTS_DIR}/Emulator6502/tests.cpp)
target_link_libraries(Emulator6502Tests PRIVATE Catch2::Catch2WithMain)
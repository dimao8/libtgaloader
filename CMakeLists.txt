cmake_minimum_required(VERSION 3.10)

project(
  libtgaloader
  VERSION 0.1.0.1
  DESCRIPTION "Lite TGA loader library"
  HOMEPAGE_URL "https://gitverse.ru/DimaO87/libtgaloader"
  LANGUAGES C
)

# Compile options
set(CMAKE_C_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-pedantic)
endif()

set(SOURCES
  src/tgaloader.c)

set(HEADERS
  include/tgaloader.h)

# Library
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(
  tgaloader
  ${SOURCES}
  ${HEADERS}
)
target_include_directories(
  tgaloader PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}
)
target_compile_definitions(
  tgaloader PUBLIC
  "-DHAVE_CONFIG_H"
)
set_target_properties(
  tgaloader PROPERTIES
  PUBLIC_HEADER ${HEADERS}
)

# Tests
add_subdirectory(tests)

# Config file
set(PACKAGE ${PROJECT_NAME})
set(VERSION ${PROJECT_VERSION})
configure_file(
  ${CMAKE_SOURCE_DIR}/config.h.in
  ${CMAKE_BINARY_DIR}/config.h
  @ONLY
)

# Copy compile_commands.json
file(
  CREATE_LINK
  ${CMAKE_BINARY_DIR}/compile_commands.json
  ${CMAKE_SOURCE_DIR}/compile_commands.json
  COPY_ON_ERROR
  SYMBOLIC
)

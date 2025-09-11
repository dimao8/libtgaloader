cmake_minimum_required(VERSION 3.18)

project(
  tgaloader
  VERSION 0.1.0.2
  DESCRIPTION "Lite TGA loader library"
  HOMEPAGE_URL "https://gitverse.ru/DimaO87/libtgaloader"
  LANGUAGES C
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Compile options
set(CMAKE_C_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-pedantic)
endif()

set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tgaloader.c)

set(HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/tgaloader/tgaloader.h)

# Library
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(tgaloader SHARED ${SOURCES})
target_include_directories(
  tgaloader PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:include/tgaloader>
)
target_compile_definitions(
  tgaloader PUBLIC
  "-DHAVE_CONFIG_H"
)
set_target_properties(
  tgaloader PROPERTIES
  PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/tgaloader/tgaloader.h
)

# Documentation
find_program(
  MAKEINFO
  makeinfo
)
if(MAKEINFO)
  add_subdirectory(doc)
else()
  message(WARNING "makeinfo not found. Skip document building.")
endif()

# Tests
add_subdirectory(tests)

# Config file
set(PACKAGE ${PROJECT_NAME})
set(VERSION ${PROJECT_VERSION})
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h
  @ONLY
)

# Configuration
set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Headers install directory")
set(LIB_INSTALL_DIR lib/ CACHE PATH "Libraries install directory")
set(SYSCONFIG_INSTALL_DIR etc/tgaloader/ CACHE PATH "System Configuration install directory")
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tgaloaderConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/tgaloaderConfig.cmake
  INSTALL_DESTINATION ${LIB_INSTALL_DIR}/tgaloader/cmake
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/tgaloaderConfigVersion.cmake
  VERSION 0.1.0
  COMPATIBILITY SameMajorVersion
)

install(
  TARGETS tgaloader
  EXPORT tgaloader-targets
  PUBLIC_HEADER DESTINATION include/tgaloader
)

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/tgaloaderConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/tgaloaderConfigVersion.cmake
  DESTINATION ${LIB_INSTALL_DIR}/cmake/tgaloader
)

if(MAKEINFO)
  install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/doc/tgaloader.pdf
    TYPE DOC
  )
endif()

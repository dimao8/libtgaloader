enable_testing()

set(TESTS_SRC_DIR ${CMAKE_SOURCE_DIR}/tests)
set(TESTS_BIN_DIR ${CMAKE_BINARY_DIR}/tests)

# ttgaloader8
add_executable(
  ttgaloader8
  ${TESTS_SRC_DIR}/ttgaloader8.c
)
target_include_directories(ttgaloader8 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  ttgaloader8 PRIVATE
  $<TARGET_FILE:tgaloader>
)

# ttgaloader16
add_executable(
  ttgaloader16
  ${TESTS_SRC_DIR}/ttgaloader16.c
)
target_include_directories(ttgaloader16 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  ttgaloader16 PRIVATE
  $<TARGET_FILE:tgaloader>
)

# ttgaloader24
add_executable(
  ttgaloader24
  ${TESTS_SRC_DIR}/ttgaloader24.c
)
target_include_directories(ttgaloader24 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  ttgaloader24 PRIVATE
  $<TARGET_FILE:tgaloader>
)

# ttgaloader32
add_executable(
  ttgaloader32
  ${TESTS_SRC_DIR}/ttgaloader32.c
)
target_include_directories(ttgaloader32 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  ttgaloader32 PRIVATE
  $<TARGET_FILE:tgaloader>
)

# ttgaloader_error
add_executable(
  ttgaloader_error
  ${TESTS_SRC_DIR}/ttgaloader_error.c
)
target_include_directories(ttgaloader_error PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  ttgaloader_error PRIVATE
  $<TARGET_FILE:tgaloader>
)

# ttgasave
add_executable(
  ttgasave
  ${TESTS_SRC_DIR}/ttgasave.c
)
target_include_directories(ttgasave PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  ttgasave PRIVATE
  $<TARGET_FILE:tgaloader>
)

# t_version test
add_test(
  NAME t_version
  COMMAND $<TARGET_FILE:ttgaloader32> --version
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_load8 test
add_test(
  NAME t_load8
  COMMAND $<TARGET_FILE:ttgaloader8> ${TESTS_SRC_DIR}/t_load8.tga
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_load16 test
add_test(
  NAME t_load16
  COMMAND $<TARGET_FILE:ttgaloader16> ${TESTS_SRC_DIR}/t_load16.tga
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_load24 test
add_test(
  NAME t_load24
  COMMAND $<TARGET_FILE:ttgaloader24> ${TESTS_SRC_DIR}/t_load24.tga
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_load32 test
add_test(
  NAME t_load32
  COMMAND $<TARGET_FILE:ttgaloader32> ${TESTS_SRC_DIR}/t_load32.tga
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_empty_error test
add_test(
  NAME t_empty_error
  COMMAND $<TARGET_FILE:ttgaloader_error> --except=4 ${TESTS_SRC_DIR}/t_empty_error.tga
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_empty_error
  PROPERTY WILL_FAIL True
)

# t_save test
add_test(
  NAME t_save
  COMMAND $<TARGET_FILE:ttgasave>
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS ttgaloader32 ttgaloader24 ttgaloader16 ttgaloader8 ttgaloader_error ttgasave
)

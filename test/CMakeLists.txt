cmake_minimum_required(VERSION 3.14)
project(libembroidery-test)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(libembroidery_test SHARED
    "tests.h"
    "tests.c"
)

add_executable(
  format_test
  formats.cc
)

target_link_libraries(libembroidery_test PRIVATE embroidery_static)
target_link_libraries(format_test PRIVATE gtest_main libembroidery_test embroidery_static)

include(GoogleTest)
gtest_discover_tests(format_test)
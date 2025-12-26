cmake_minimum_required(VERSION 3.15)

project(animation_tests LANGUAGES CXX)

if(DEFINED CONAN_GTEST_ROOT)
  set(GTest_DIR "${CONAN_GTEST_ROOT}/lib/cmake/GTest")
endif()

# Find GTest (either from Conan env or system)
find_package(GTest REQUIRED)

add_executable(test_animation
  test_dummy.cpp
)

target_include_directories(test_animation PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_animation PRIVATE GTest::gtest GTest::gtest_main animation)

include(GoogleTest)
gtest_discover_tests(test_animation)
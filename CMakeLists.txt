cmake_minimum_required(VERSION 3.10)

project(DungeonEditor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIB_SOURCES
    NPC.cpp
    NPCFactory.cpp
    Observer.cpp
    Battle.cpp
    DungeonEditor.cpp
)

add_library(DungeonEditorLib ${LIB_SOURCES})

add_executable(DungeonEditor main.cpp)

target_link_libraries(DungeonEditor DungeonEditorLib)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_l6 tests.cpp)

target_link_libraries(test_l6 DungeonEditorLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_l6)
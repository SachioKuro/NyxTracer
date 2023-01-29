# CMakeList.txt : CMake project for NyxTracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("NyxTracer")

# Add source to this project's executable.
add_executable (NyxTracer "NyxTracer.cpp" "NyxTracer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NyxTracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
add_subdirectory(lib/Catch2)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false tests/*.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
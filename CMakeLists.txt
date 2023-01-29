# CMakeList.txt : CMake project for NyxTracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("NyxTracer")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(CTest)
enable_testing()

# Add source to this project's executable.
add_library(nyxtracer "src/math/Point.cpp" "src/math/Vector.cpp")
target_include_directories(nyxtracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable (NyxTracerExe "NyxTracer.cpp" "NyxTracer.hpp")

# TODO: Add tests and install targets if needed.
add_subdirectory(lib/Catch2)
add_executable(NyxTracerTest "tests/utils/Util.cpp" "tests/math/test_Point.cpp" "tests/math/test_Vector.cpp")
target_link_libraries(NyxTracerTest PRIVATE Catch2::Catch2WithMain PUBLIC nyxtracer)
target_include_directories(NyxTracerTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(NyxTracerTest)

install(
	TARGETS NyxTracerTest
	RUNTIME DESTINATION bin
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NyxTracerExe PROPERTY CXX_STANDARD 20)
  set_property(TARGET NyxTracerTest PROPERTY CXX_STANDARD 20)
endif()
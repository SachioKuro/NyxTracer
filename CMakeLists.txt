# CMakeList.txt : CMake project for NyxTracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("NyxTracer")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(CTest)
enable_testing()

# Add source to this project's executable.
add_library(nyxtracer  "src/graphics/Utils.cpp" "src/graphics/Matrix.cpp" "src/graphics/Vector.cpp")
target_include_directories(nyxtracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable (NyxTracerExe  "src/Playground.cpp" "src/graphics/Matrix.cpp" "src/graphics/Vector.cpp")

# TODO: Add tests and install targets if needed.
add_subdirectory(lib/Catch2)
add_executable(NyxTracerTest "tests/utils/Util.cpp" "tests/graphics/test_Point.cpp" "tests/graphics/test_Vector.cpp" "tests/graphics/test_Color.cpp" "tests/graphics/test_Canvas.cpp" "tests/graphics/test_Matrix.cpp" "tests/graphics/test_Transformation.cpp")
target_link_libraries(NyxTracerTest PRIVATE Catch2::Catch2WithMain PUBLIC nyxtracer)
target_include_directories(NyxTracerTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(NyxTracerTest)

install(
	TARGETS NyxTracerTest
	RUNTIME DESTINATION bin
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NyxTracerExe PROPERTY CXX_STANDARD 23)
  set_property(TARGET NyxTracerTest PROPERTY CXX_STANDARD 23)
endif()
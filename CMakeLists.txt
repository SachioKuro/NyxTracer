cmake_minimum_required(VERSION 3.28)

project(NyxTracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Google Test
include(GoogleTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

FILE(GLOB_RECURSE SOURCES "src/*.cpp")
LIST(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_executable(NyxTracer ${SOURCES} src/main.cpp)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN} ${SOURCES})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    
    gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(
  tuple_test
  tests/test_point.cpp  
  tests/test_vector.cpp
  tests/test_color.cpp
  tests/test_canvas.cpp
  tests/test_matrix.cpp
  tests/test_transformation.cpp
  tests/test_ray.cpp
  tests/test_uid.cpp
  tests/test_object.cpp
  tests/test_sphere.cpp
  tests/test_plane.cpp
  tests/test_intersection.cpp
  tests/test_point_light.cpp
  tests/test_material.cpp
  tests/test_world.cpp
  tests/test_camera.cpp
)
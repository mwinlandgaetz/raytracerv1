cmake_minimum_required(VERSION 3.0.0)
project(RayTracerV1 VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(LIBPNG CONFIG REQUIRED)
find_package(GLM REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RayTracerV1 main.cpp camera.cpp ray.cpp sphere.cpp)

target_link_libraries(${PROJECT_NAME} glm png)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

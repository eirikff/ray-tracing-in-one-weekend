cmake_minimum_required(VERSION 3.22)
project(raytracer VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/image.cpp
	src/vector3d.cpp
	src/camera.cpp
	src/sphere.cpp
	src/hittable_list.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	-Wpedantic
)


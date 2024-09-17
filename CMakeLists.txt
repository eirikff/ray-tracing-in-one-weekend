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
	src/interval.cpp
	src/color.cpp
	src/stb_image_write.cpp
    src/material/lambertian.cpp
    src/material/metal.cpp
    src/material/dielectric.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Disable specific warning for stb image write header library
set_source_files_properties(
	src/stb_image_write.cpp
	PROPERTIES APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-missing-field-initializers"
)

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall
	-Wextra
	-Wpedantic
)


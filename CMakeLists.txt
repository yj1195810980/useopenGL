cmake_minimum_required(VERSION 3.27)
project(useOpenGl)

set(CMAKE_CXX_STANDARD 17)
set(VCPKG_ROOT "D:/src/vcpkg-master/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}) #设置vcpak的路径才能找到编译的库

find_package(OpenGL REQUIRED)

find_package(glfw3 CONFIG REQUIRED)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/glad)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR)

add_executable(useOpenGl main.cpp glad.c)

target_link_libraries(useOpenGl PRIVATE OpenGL::GL  glfw)
target_include_directories(useOpenGl INTERFACE ${INCLUDE_DIR})


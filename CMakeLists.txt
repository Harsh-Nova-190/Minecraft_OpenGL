cmake_minimum_required(VERSION 3.30)

project(Minecraft_clone)

set(CMAKE_CXX_STANDARD 17)

add_executable(Minecraft_clone
	src/main.cpp
	libs/glad/src/glad.c
)

target_include_directories(Minecraft_clone PRIVATE
	libs/glad/include
	libs/glfw/include
)

target_link_directories(Minecraft_clone PRIVATE
	libs/glfw/lib-vc2022
)

target_link_libraries(Minecraft_clone
	glfw3
	opengl32
)
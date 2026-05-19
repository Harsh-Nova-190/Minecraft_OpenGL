cmake_minimum_required(VERSION 3.30)

project(Minecraft_clone)

set(CMAKE_CXX_STANDARD 17)

add_executable(Minecraft_clone
	src/main.cpp
	libs/glad/src/glad.c
	src/graphics/Shader.cpp
	src/graphics/Shader.h
	src/camera/Camera.cpp 
	src/camera/Camera.h
	src/world/Block.h
	src/world/Block.cpp
)

target_include_directories(Minecraft_clone PRIVATE
	libs/glad/include
	libs/glfw/include
	libs/glm
	libs/stb
)

target_link_directories(Minecraft_clone PRIVATE
	libs/glfw/lib-vc2022
)

target_link_libraries(Minecraft_clone
	glfw3
	opengl32
)
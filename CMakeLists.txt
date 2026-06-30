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
	src/world/helper/Block.h
	src/engine/Core.h
	src/engine/Window.h
	src/engine/Window.cpp
	src/world/World.h
	src/world/World.cpp
	src/renderer/WorldRenderer.h
	src/renderer/WorldRenderer.cpp
	src/world/Chunk.h
	src/world/Chunk.cpp
	src/world/ChunkManager.h
	src/world/ChunkManager.cpp
	src/ui/Crosshair.cpp
	src/ui/Crosshair.h
	src/renderer/ChunkMesh.h
	src/renderer/ChunkMesh.cpp
	src/world/CubeData.h
	src/world/helper/FaceFlags.h
	src/graphics/TextureAtlas.h
	src/world/helper/TextureAtlas.h
	
	"src/renderer/ChunkMeshBuilder.cpp"
 "src/renderer/ChunkMeshBuilder.h"  )

target_include_directories(Minecraft_clone PRIVATE
	libs/glad/include
	libs/glfw/include
	libs/glm
	libs/stb
)

target_link_directories(Minecraft_clone PRIVATE
	libs/glfw/lib-vc2022
	libs/curl/lib
)

target_link_libraries(Minecraft_clone
	glfw3
	opengl32
)
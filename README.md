# C++ OpenGL Voxel Engine

A high-performance, custom-built 3D voxel rendering engine written in C++ and modern OpenGL. Designed from scratch to explore low-level graphics pipeline architecture, custom memory layouts, procedural terrain, and chunk-based rendering optimizations.

---

## Technical Highlights & Performance

* **Framerate:** Sustained **300+ FPS** (up from 43 FPS in early iterations).
* **Architecture:** Modular pipeline passing through `World` -> `ChunkManager` -> `Chunk` -> `ChunkMesh`.
* **Geometry Optimization:** Custom **Face Culling** algorithm to skip hidden block faces, significantly reducing vertex data sent to the GPU.
* **Texture Management:** 64x64 **Texture Atlas** integration to eliminate per-block texture switching and batch draw calls.
* **Procedural Generation:** Dynamic heightmap and terrain rendering powered by noise functions.

---

## Engine Architecture Evolution

### 1. Initial Naive Approach
* **Pipeline:** `main` -> `worldRenderer` -> `blockRenderer`
* **Draw Calls:** Individual rendering calls per block (e.g., 9,072 function calls for 9,072 blocks).
* **Performance:** ~43–46 FPS (flat terrain).

### 2. Optimized Chunked Pipeline
* **Pipeline:** `main` -> `World` -> `ChunkManager` -> `Chunk` -> `ChunkMesh`
* **Optimization:** Unified 16-chunk batching (4,096 blocks) into single-mesh draw calls with hidden face removal.
* **Performance:** **100–300+ FPS** (3D procedural terrain).

---

## Features

- [x] Modern OpenGL (VAOs, VBOs, GLSL Shader Pipeline)
- [x] Custom Chunk Meshing (`ChunkMesh`)
- [x] Hidden Face Culling (Adjacent Block Detection)
- [x] Texture Atlas Mapping (64x64 Tile Resolution)
- [x] Procedural Terrain Noise Generation

---

## Building & Running

### Prerequisites
* C++17 Compiler (GCC, Clang, or MSVC)
* CMake 3.15+
* OpenGL 3.3+ Drivers
* Dependencies: GLFW / GLEW (or GLAD) / GLM

### Build Instructions
```bash
# Clone repository
git clone [https://github.com/your-username/voxel-engine.git](https://github.com/your-username/voxel-engine.git)
cd voxel-engine

# Build project
mkdir build && cd build
cmake ..
cmake --build .

# Run engine
./VoxelEngine
```

---

## Screenshots

<img width="480" height="402" alt="Screenshot 2026-09-25 151502" src="https://github.com/user-attachments/assets/8af04a6c-034f-4192-a5fc-c2b628448075" />

<img width="1282" height="758" alt="Screenshot 2026-09-25 151446" src="https://github.com/user-attachments/assets/e4db24d1-32b3-45e9-b763-5f5f011fe4a2" />

<img width="1283" height="762" alt="Screenshot 2026-09-25 151423" src="https://github.com/user-attachments/assets/9ee67f6a-f578-4c82-88e8-dab6603e1213" />

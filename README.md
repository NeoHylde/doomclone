# DoomClone (Experimental OpenGL Game)

Welcome to **DoomClone** — a simple experimental game and my first project using **OpenGL with C++**.  
This is primarily a learning project to explore how real-time 3D rendering works from scratch, including shaders, camera movement, mesh creation, and object transformation.

---

## 🎮 Features

- Custom `Tile`, `Wall`, and `Map` classes for rendering modular environments
- Support for diffuse and specular textures
- Basic lighting using custom shaders
- Interactive camera using keyboard/mouse input
- Structured and reusable rendering pipeline with `Mesh` and `Shader` abstractions

---

## 🛠️ Built With

- **C++17**
- **OpenGL 3.3 Core**
- **GLFW** (window/context/input)
- **GLAD** (OpenGL function loader)
- **GLM** (math library)
- **STB Image** (texture loading)

---

## 🚀 Getting Started

### Prerequisites

Make sure you have the following libraries installed and properly linked:

- GLFW
- GLAD
- GLM
- STB Image

### Build Instructions (example for CMake)

```bash
git clone https://github.com/neohylde/doomclone.git
cd doomclone-opengl
mkdir build && cd build
cmake ..
make
./DoomClone

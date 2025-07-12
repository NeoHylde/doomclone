# DoomClone

**DoomClone** is an experimental 3D game built with **OpenGL** and **C++**. This project serves as a hands-on exploration of real-time rendering, shader programming, and basic game engine architecture.

---

## Features

- Real-time 3D rendering with custom shaders
- First-person camera and movement
- Custom model loading via glTF parser
- Modular rendering pipeline (Mesh, Model, Shader abstraction)

---

## Implemented Systems

- Custom glTF Loader using nlohmann::json
- Hierarchical Scene Graph with Transform Matrices
- Vertex Buffer & Array Abstraction
- Depth Testing and Backface Culling
- Custom Material and Texture System (with PBR parameters)

---

## Controls (For Player Class)

- `W` / `A` / `S` / `D` – Move
- Mouse – Look around
- `ESC` – Unlock/Lock cursor

---

## Next Steps

- Implement dynamic 3D model transformations (rotation, scaling, animation)
- Add `Weapon` classes and firing logic (still fixing model orientation issues)
- Create `Enemy` classes with pathfinding (likely A* or navmesh)
- Integrate a basic audio system (positional sounds, effects)

---

## Tech Stack

- **C++17**
- **OpenGL 3.3 Core Profile**
- **GLFW** (windowing & input)
- **GLAD** (OpenGL loader)
- **GLM** (math)
- **STB Image** (texture loading)

---

### Prerequisites

Ensure the following libraries are installed and linked:

- GLFW
- GLAD
- GLM
- STB Image
- KHR
- NHLOMANN JSON 

---

## Build Instructions (VSCode)

> Make sure you've installed the **C++ extension** and configured your compiler. On Windows, you can use either:
>
> - **MinGW-w64** – Easy to set up with VSCode
> - **MSVC** – Works with the "MSVC" version of the C++ extension and Visual Studio Build Tools
>
> Ensure that your `.vscode/tasks.json` points to the right compiler executable (`g++.exe` for MinGW, or `cl.exe` for MSVC).


If you're using **Visual Studio Code**, building is easy:

1. Open the project folder in VSCode.
2. Press **Ctrl + Shift + B** to trigger the default build task.
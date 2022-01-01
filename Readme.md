# Flax Engine

It is a custom made game engine structured in C++. The main goal is to test how to create a modular 
game engine with a focus on performance and flexibility. The engine is designed to be easy to use and 
easy to extend. In my previous engine projects, I tried creating lots of features and systems from 
scratch. That was a great learning experience, but I mostly ended up with a lot of code that has no
visual result. This time, I want to use the right tools for the job and focus on creating something decent.

## Wanted Features
- [x] Hybrid Entity Component System (OOP + Data Oriented).
- [ ] Runtime reflection that has been inspired by EnTT.
- [ ] Extendable resource types and extensions.
- [ ] Customizable serialization system.
- [ ] Customizable Render Graph.
- [ ] Single Graphics Abstraction Layer that can handle multiple graphics APIs.
- [ ] Enhanced Input System that has been inspired by Unreal Engine.
- [ ] GPU Skinning System (Where all the data lives in GPU memory. Only inputs will be sent to CPU_TO_GPU)
- [ ] GPU Based Physics System.
- [ ] GPU Driven Rendering with Mesh Shaders without Compute Based Rasterization (Way too heavy)
- [ ] Clustered Deferred Shading. (Because why not?)
- [ ] Shader(Material) Graph System that has been inspired by Unity.

## How is it going?
Slow but steady. I'm working in a team of one. I have a full time job and I am working on this engine in my 
free time. So to see something worth showing with editor and stuff, it will take a while but I think I can get
some result till the end of 2025. But of course, I will try to make some basic showcases as soon as 
possible. The first thing I want to show is the hardcoded gltf viewer with a not so complex but decently
visualized rendering techniques. The eventual goal is to create one of the games below with a single level.

- Wolverine's Revenge (With tweaked mechanics and remade meshes)
- Taz Wanted (No tweak but I won't say no to remade meshes)
- Bugs Bunny: Lost in Time (No tweak but I won't say no to remade meshes)
- Earthworm Jim 3D (No tweak but I won't say no to remade meshes)
- Zax: The Alien Hunter (Little tweak but I won't say no to remade meshes)

# Rendering Pipeline Diagram
![Pipeline](https://github.com/user-attachments/assets/50508e0a-ae71-4d2d-bbe7-e0232ea881ce)

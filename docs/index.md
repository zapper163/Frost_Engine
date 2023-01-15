# Frost Engine
A 3D Game Engine made by Alejandro Giralt at UPC's CITM

Github: [zapper163](https://github.com/zapper163)

## Features:

### v0.1
- FBX & Texture loader
- Drag & Drop of FBX and PNG
- Unity-like Camera
- GameObject structure & Hierarchy
- Each GameObject has three components: Transform, Mesh & Texture

![v0.1](https://github.com/zapper163/Frost_Engine/blob/main/docs/media/v0.1.jpeg?raw=true)

### v0.2
All the features from v0.1 +
- Camera as a component
- Frustum Culling
- Mouse Picking

![v0.2](https://github.com/zapper163/Frost_Engine/blob/main/docs/media/v0.2.jpeg?raw=true)

### v0.3
All the features from v0.1 and v0.2 +
- Audio with Wwise library
- Components SoundSource and SoundListener
- SoundBank loading and event management
- Play, Pause, Resume and Stop the audio

<iframe width="560" height="315" src="https://www.youtube.com/embed/G27xBVIa7fs" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe> <br>


## Controls:
- While Right clicking, “WASD” for fps-like movement and free look around.
- Mouse wheel for zoom in and out.
- Alt + Left click orbits the object.
- F to focus the camera around the geometry.
- Holding SHIFT duplicates movement speed.

## Third party Libraries Used:
* [SDL](https://github.com/libsdl-org/SDLS) 2.24.0.0
* [Glew](https://github.com/nigels-com/glew) 2.1.0.0
* [ImGui](https://github.com/ocornut/imgui) 1.88
* [JSON Parser](https://github.com/json-parser/json-parser) 1.1.0
* [MathGeoLib](https://github.com/juj/MathGeoLib) 1.15
* [Assimp](https://assimp-docs.readthedocs.io/en/v5.1.0) 5.1.0
* [DevIL](https://openil.sourceforge.net) 1.8.0
* [Wwise](https://www.audiokinetic.com/en/download/) 2021.1.11

## MIT License

Copyright (c) 2022 zapper163

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


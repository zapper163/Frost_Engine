
# Frost Engine
A 3D Game Engine made by Alejandro Giralt at UPC's CITM

Github: [zapper163](https://github.com/zapper163)

## Demo info
In this demo there are one cube and one sphere on scene. 
- The cube has the AudioSource component, wich manages the audio track and the play, pause, resume and stop events (and also the audio volume, but it doesn't work).
- The sphere has the AudioListener component, witch can be disabled by a checkbox. 

The cube will start playing the background music as soon as the program is executed.
The background music features two songs of 32 seconds eatch, that blend eatch other an loop infinitely

*The second song seems to have a couple seconds of silence at the end. Because of this, there is a moment of silence between eatch loop.

## Features:

- FBX & Texture loader
- Drag & Drop of FBX and PNG
- Unity-like Camera with frustum culling
- GameObject structure & Hierarchy
- Component Texture, Mesh, Transform & Camera.
- Mouse Picking

## WWise audio Sub-System
- Components SoundSource and SoundListener
- SoundBank loading and event management
- Play, Pause, Resume and Stop the audio

## Controls:
- While Right clicking, “WASD” for fps-like movement and free look around.
- Mouse wheel for zoom in and out.
- Alt + Left click orbits the object.
- F to focus the camera to the center of the world.
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

# GMD3D11

> D3D11 functions extension for GameMaker

[![License](https://img.shields.io/github/license/blueburncz/GMD3D11)](LICENSE)
[![Discord](https://img.shields.io/discord/298884075585011713?label=Discord)](https://discord.gg/ep2BGPm)

## Status: Community Project 💙

This is a community-developed project, released under **CC0 1.0 Universal (Public Domain)**. It is **no longer actively maintained** by the original author. Feel free to fork, modify, or experiment.

## Features

* [x] Shaders
  * [x] Compile from file (optimization level 3)
  * [x] Save and load compiled shaders
  * [x] Hook into `ID3D11DeviceContext::Draw` calls to swap out used vertex and pixel shaders with custom ones
  * [x] Vertex
  * [x] Pixel
  * [x] Geometry
  * [x] Tessellation
  * [x] Compute
* [x] Vertex formats
* [x] Buffers
  * [x] Vertex
  * [x] Index
  * [x] Constant
  * [x] Structured (read-only)
  * [x] Compute (read/write structured)
  * [x] Append/consume
  * [x] Indirect args
  * [x] Raw
  * [x] Upload (CPU -> GPU)
  * [x] Readback (GPU -> CPU)
* [x] Textures
  * [x] `texture_set_stage_vs()` - vertex texture fetching of native GM textures (`sprite_get_texture()`, `surface_get_texture()`)
  * [x] Samplers
  * [x] 2D
  * [x] 3D
  * [x] Arrays
* [x] DSV
* [x] RTV
* [x] SRV
* [x] UAV
* [x] Occlusion queries
* [x] Timestamps
* [x] `vertex_submit_instanced()` - instanced rendering of native GM vertex buffers
* [x] Viewports
* [x] Scissor rects

## Building the DLL

> Requires [CMake](https://cmake.org/) 3.23 at least and [Python 3](https://www.python.org/downloads/)!

Simply run `./build.ps1` from the root directory to build the DLL, copy it into `datafiles` and generate
`__d3d11_generated.gml`.

## Links

* [Documentation](https://blueburn.cz/gmd3d11/docs) - for the latest release, not the `main` branch!!!

## Credits

* <https://github.com/ParinovYT/cVmtHook-x64> - x64 VMT hook
* <https://polyhaven.com/a/rubber_duck_toy> - model used in instanced rendering example


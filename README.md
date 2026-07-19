# ID3D11

GameMaker ↔ Direct3D 11 bindings generated from GMIDL with YoYo Games' Extension Generator.

This fork is being rebuilt around a complete, typed `id3d11_*` API. The original `d3d11_*` implementation and `GMD3D11.dll` remain in the project as a compatibility baseline while interfaces migrate to the new core.

## Current status

The new `ID3D11.dll` path is functional end to end:

- GameMaker obtains the runner's `ID3D11Device`, immediate context, and DXGI swap chain through `os_get_info()`.
- Native COM ownership uses `Microsoft::WRL::ComPtr`.
- GML sees generation-checked 64-bit handles instead of raw COM pointers.
- `QueryInterface` supports core and versioned D3D11 interface kinds through D3D11.4.
- `ID3D11Buffer` and Texture1D/2D/3D creation support no-data and buffer-backed initialization, including multi-subresource offset/pitch tables.
- Resource type, eviction priority, parent-device lookup, and texture/buffer descriptor round trips are exposed.
- SRV, RTV, DSV, and UAV creation support both default and explicit flattened descriptors, with view descriptor/resource lookup.
- Runtime HLSL compilation feeds exact bytecode lengths into all six shader stages, InputLayout, and Stream Output GeometryShader creation. ClassLinkage creation, class-instance lookup/creation, descriptors, names, and parent-linkage queries are exposed as typed APIs.
- Sampler, rasterizer, blend, and depth-stencil states support typed creation and complete descriptor round trips, including nested stencil operations and all eight render-target blend slots.
- Query, predicate, and device-dependent counter objects expose typed creation, capability checks, `GetDataSize`, and descriptor round trips; the immediate context supports `Begin`, `End`, `GetData`, and `Flush` with checked GameMaker output buffers.
- Immediate-context execution covers direct and indirect Draw/Dispatch, whole-resource and boxed subresource copies, structured-UAV counter copies, RTV/UAV/DSV clears, mip generation, resource minimum LOD, and multisample resolve. Indirect argument buffers, boxes, clear flags, device identity, and resource shapes are validated before dispatch.
- Base pipeline state binding covers IA InputLayout/topology/vertex/index buffers, RS state/viewports/scissors, OM blend/depth-stencil states, predication, and shader/constant-buffer/SRV/sampler bindings for all six shader stages. Shader bindings carry up to 256 class-instance handles. Array getters return typed structs or handle arrays, and the VM smoke test restores every captured Runner binding.
- A startup smoke test exercises typed structs, enums, `uint64`, `GMBuffer`, COM interface upgrades, all current resource/view/shader/state/asynchronous paths, bounds rejection, stale-handle rejection, and resource lifetime inside the real GameMaker VM runner. It prints one result line and calls `game_end()` so `gm-cli run` terminates deterministically.

See [Architecture](docs/ARCHITECTURE.md) and [API coverage](docs/API_COVERAGE.md).

## Build

Requirements:

- `extgen` on `PATH`
- CMake 3.25 or newer
- Visual Studio 2026 with the v145 toolset and Windows SDK
- `gm-cli` on `PATH` for GameMaker compile verification

Run the complete generation, native build, GameMaker compile, and VM smoke-test pipeline:

```powershell
.\build.ps1
```

Useful options:

```powershell
.\build.ps1 -Configuration Debug
.\build.ps1 -SkipGenerate
.\build.ps1 -SkipGameMaker
.\build.ps1 -SkipSmoke
.\scripts\smoke.ps1 -TimeoutSeconds 300 -LogPath .\smoke.log
.\build.ps1 -Legacy
```

The new DLL is copied to `extensions/ID3D11/ID3D11.dll`. The legacy switch builds `GMD3D11.dll` into `datafiles/` and regenerates the old wrappers.

Run the deterministic VM smoke test directly with `.\scripts\smoke.ps1`. It compiles first unless `-SkipCompile` is supplied, then runs the project with explicit Windows VM settings. The script requires exactly one result line with every smoke category set to `1`, a clean `game_end`, and a zero `gm-cli` exit code. Use `-LogPath` to retain the combined Runner log; the default temporary log is removed after a successful run and retained after a failure.

## Development workflow

1. Define the public API in `binding/id3d11.gmidl`.
2. Run `binding/generate.ps1` (or the root build script).
3. Implement native behavior under `binding/src/native/`.
4. Build with the checked-in `win-v145` CMake preset.
5. Compile or run `ID3D11.yyp` with `gm-cli`.

Generated files under `binding/code_gen/`, the GML API script, runtime script, and extension function metadata are build-managed. The generation wrapper reapplies the hidden runner bootstrap metadata and zero-initializes numeric input descriptors after every extgen run. Native implementation files under `binding/src/` are developer-owned.

An optional native dynamic-linkage probe lives under `binding/probes/`. It reproduces the exact `ID3D11ClassLinkage`/`PSSetShader` sequence independently of GameMaker and supports `--warp` for a software-driver control run. It is not part of the normal extension build.

## Legacy feature baseline

The pre-refactor project already demonstrates shaders, vertex/index/constant/structured/compute/raw/upload/readback buffers, 2D/3D/array textures, DSV/RTV/SRV/UAV views, queries, timestamps, instanced rendering, viewports, and scissor rectangles. These remain available through the old `d3d11_*` surface until equivalent typed `id3d11_*` APIs replace them.

## License

See [LICENSE](LICENSE).

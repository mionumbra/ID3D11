# ID3D11 API coverage

Coverage is measured against the runtime COM interfaces declared by Windows SDK 10.0.26100.0 in `d3d11.h` and `d3d11_1.h` through `d3d11_4.h`.

Status meanings:

- **Implemented**: public GMIDL API, native implementation, and GameMaker-side verification exist.
- **Transport only**: the interface can be represented/query-upgraded as a typed handle, but its methods are not mapped yet.
- **Planned**: handle kind and implementation work remain.

## Foundation

| Area | Status | Notes |
|---|---|---|
| Runner device/context/swap-chain bootstrap | Implemented | Validates shared COM device identity |
| COM ownership | Implemented | `ComPtr` throughout |
| 64-bit generation handles | Implemented | Stale-handle rejection tested in VM runner |
| Handle kind inspection/release | Implemented | `id3d11_handle_*` |
| `QueryInterface` upgrades | Implemented | Core and versioned D3D11 interface kinds |
| HRESULT state | Implemented | Direct/structured result plus last HRESULT |
| GMIDL typed structs/enums/`uint64` | Implemented | extgen-generated codecs |
| GameMaker `buffer` ↔ `GMBuffer` | Implemented | Tested through buffer and texture initial data |
| Multi-subresource transport | Implemented | Buffer plus checked offset/pitch/size table |
| Numeric descriptor defaults | Implemented | Post-generation constructors initialize all input fields to zero |
| HLSL bytecode transport | Implemented | Source compilation, exact output sizes, diagnostics, and checked creation spans |

## Interface families

| Interfaces | Status | Current method coverage |
|---|---|---|
| `ID3D11Device` | Partial | Buffers/textures/views/base states/query/predicate/counter creation; six shader creators, SO geometry shader, InputLayout, ClassLinkage; format/MSAA/counter checks and device queries |
| `ID3D11Device1` … `ID3D11Device5` | Transport only | Typed `QueryInterface` handles |
| `ID3D11DeviceContext` | Partial | `Begin`/`End`/checked `GetData`/`Flush`; direct/indirect Draw and Dispatch; resource/subresource/structure-count copies; checked `UpdateSubresource`; synchronous bounded Map read/write wrappers; RTV/UAV/DSV clear; GenerateMips, resource MinLOD, ResolveSubresource; IA InputLayout/topology/vertex/index buffers; RS state/viewports/scissors; OM blend/depth-stencil states, render targets, and RT+UAV combo; SO targets; CS UAV slots; ClearState; deferred context + command list Finish/Execute; predication; VS/HS/DS/GS/PS/CS shader plus class instances, constant-buffer, SRV, and sampler slots |
| `ID3D11DeviceContext1` … `ID3D11DeviceContext4` | Transport only | Typed `QueryInterface` handles |
| `ID3D11Buffer` | Partial | `GetDesc`; creation, parent-device lookup, resource methods, synchronous staging Map transfer, and lifetime complete |
| `ID3D11Resource`, `Texture1D`, `Texture2D`, `Texture3D` | Partial | Type/eviction methods, `GetDesc`, no-data and checked multi-subresource creation |
| `ID3D11Texture2D1`, `ID3D11Texture3D1` | Transport only | Typed `QueryInterface` handles |
| Base SRV, RTV, DSV, UAV interfaces | Partial | Default/explicit creation, complete base `GetDesc`, `GetResource`, parent-device lookup, lifetime |
| Versioned SRV1, RTV1, UAV1 interfaces | Transport only | Typed `QueryInterface` handles |
| Vertex, hull, domain, geometry, pixel, compute shaders | Partial | Bytecode creation with optional ClassLinkage, six-stage context Set/Get, parent-device lookup, typed lifetime; private-data methods remain |
| `ID3D11InputLayout` | Partial | Typed element-array creation, parent-device lookup, lifetime; private-data methods remain |
| Base sampler, rasterizer, blend, and depth-stencil states | Partial | Typed creation, complete `GetDesc`, parent-device lookup, lifetime; private-data methods remain |
| Versioned rasterizer/blend states | Transport only | Typed `QueryInterface` handles |
| Base query, predicate, counter, asynchronous | Partial | Typed creation, `CheckCounter`, `GetDataSize`, base `GetDesc`, context execution, parent-device lookup, lifetime |
| `ID3D11Query1` | Transport only | Typed `QueryInterface` handle |
| `ID3D11ClassLinkage` | Partial | Device creation, named class-instance lookup, and class-instance creation |
| `ID3D11ClassInstance` | Partial | Parent ClassLinkage, complete base descriptor, instance name, type name, and typed lifetime |
| Command list, fence | Transport only | Typed handles / upgrades |
| Video device/context/processor/decoder/view/crypto interfaces | Transport only | Typed handles / upgrades |
| `ID3D11DeviceChild`, `ID3D11View` | Partial | `GetDevice` and `GetResource`; debug name + private data set/get |
| `ID3D11Multithread` | Transport only | Typed `QueryInterface` handle |

The core/versioned target contains 67 COM interfaces. Method-by-method completion will proceed in dependency order:

1. Resource descriptors and all `ID3D11Device::Create*` methods.
2. Resource/view/state getters and private-data methods.
3. Full device-context pipeline state, draw/dispatch, copy/update/map/query methods.
4. D3D11.1–11.4 additions, deferred contexts, command lists, and fences.
5. Video interfaces.

After the 67 runtime interfaces, separate coverage passes will address SDK-layer/debug interfaces, shader reflection/tooling interfaces, and optional D3D11On12/DXGI integration. These are tracked separately because they have different deployment and GameMaker-runner constraints.

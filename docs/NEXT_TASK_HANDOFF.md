# ID3D11 next-task handoff

Date: 2026-07-17

## Mission and naming

This fork is being rebuilt as a GameMaker extension that exposes the D3D11 API to
GML.

- Extension/project name: `ID3D11`
- GML prefix: `id3d11`
- GMIDL-generated names are the public GML extension names; keep naming consistent
  in GMIDL instead of adding a second manual renaming layer.
- `extgen` is already on `PATH`.
- Visual Studio 2026 with toolset v145 is on drive D. Do not switch the build to
  v142: that installation exists but cannot be driven correctly by CMake here.
- `gm-cli` is on drive D and can build, run, and modify the GameMaker project.

The worktree contains intentional legacy deletions and modifications from the
refactor. Do not reset, restore, clean, or otherwise undo unrelated dirty files.

## Verified baseline

At this handoff the project has:

- 171 GMIDL functions and 173 extension functions.
- Generation-checked 64-bit native handles and Runner bootstrap integration.
- Device/resource/buffer/texture/view/shader/state/query support.
- Six shader stages, class linkage/class instances, pipeline bindings, queries,
  predication, and synchronous/asynchronous context tests.
- Twenty immediate context execution/resource operations: direct and indirect
  Draw/Dispatch, CopyResource, CopySubresourceRegion, CopyStructureCount, view
  clears, GenerateMips, resource MinLOD, and ResolveSubresource.
- Native-side validation for handle type, device identity, buffer offsets and
  spans, subresources, boxes, view types, resource flags, formats, and sample
  counts for those operations.

The last fully verified Runner result was:

```text
[ID3D11] bootstrap=1 smoke=1 shader=1 state=1 async=1 context=1 pipeline=1 feature_level=45312
###game_end###0
Runner.exe DONE (0)
Game exited
```

The Release native DLL, packaged extension DLL, and Runner output DLL had the same
SHA-256:

```text
889307853075D7A673D1B973E9337BA94FDD74DAD49D6C51F238BC460170115F
```

Treat that hash as a historical baseline, not as an expected hash after new code
is built.

The bootstrap script deliberately ends with `game_end()`. Keep that termination
so automated runs do not hang.

## Known external issue

Dynamic shader class binding crashes inside NVIDIA driver
`nvgpucomp64.dll` version `32.0.15.8228` on the current machine. CDB and a
standalone native probe showed the same hardware-driver crash, while WARP passed.
The ordinary smoke path therefore tests class linkage/class instance management
without binding a dynamic class instance. Do not mistake this for an extension
handle-lifetime bug, and do not re-enable that hardware smoke case without a
driver change or an explicit isolated experiment.

## Recommended next batch

Implement safe CPU data transfer around `ID3D11DeviceContext::UpdateSubresource`,
`Map`, and `Unmap`.

Do not begin by exposing `D3D11_MAPPED_SUBRESOURCE::pData` as a numeric GML value.
It is a temporary native pointer whose lifetime ends at `Unmap`; exposing it would
make use-after-unmap, cross-context misuse, and unchecked reads/writes easy.

The recommended order is:

1. Inventory the current GMIDL buffer parameter/return capabilities and the
   existing native handle registry. Confirm how a GameMaker buffer address and
   size reach native code.
2. Add a reusable DXGI format-layout module. It must describe bytes per texel or
   block, block dimensions, packed/planar properties, and formats that cannot yet
   be copied safely.
3. Add resource/subresource layout helpers for mip dimensions, array slices,
   buffer byte ranges, row byte counts, row counts, and depth slices. Keep logical
   row size separate from D3D's mapped `RowPitch` and `DepthPitch`.
4. Implement `UpdateSubresource` only after validating source-buffer offset and
   length, optional destination box, `SrcRowPitch`, and `SrcDepthPitch`. Handle
   block-compressed alignment and multisample restrictions explicitly; reject an
   unsupported format rather than estimating its footprint.
5. Represent `Map` safely. Prefer a generation-checked native map-session handle
   tied to the exact context, resource, and subresource. Provide bounded copy
   operations between that session and GML buffers, then require exactly one
   `Unmap`. An immediate `map_read_to_buffer` / `map_write_from_buffer` wrapper is
   a simpler acceptable alternative if GMIDL cannot express a robust session API.
6. Ensure every failure path after a successful native `Map` performs `Unmap`.
   Session destruction and extension shutdown must also clean up live mappings
   deterministically.
7. Cover `D3D11_MAP_READ`, `WRITE`, `READ_WRITE`, `WRITE_DISCARD`, and
   `WRITE_NO_OVERWRITE` according to resource usage and CPU-access flags. Handle
   `D3D11_MAP_FLAG_DO_NOT_WAIT` and `DXGI_ERROR_WAS_STILL_DRAWING` as a normal
   recoverable result rather than corrupting the global error state.
8. Add narrow GML tests for buffers, Texture1D/2D/3D mip subresources, padded row
   pitch, boxes, invalid buffer spans, double-unmap, stale handles, wrong context,
   and unsupported formats. Keep allocations tiny and release every handle.
9. Regenerate, build Release, package, run the Runner, compare all deployed DLL
   hashes, check for leaked Runner/Igor/debugger processes, and run
   `git diff --check`.

## Safety invariants for mapped sessions

If the session-handle design is used, preserve these invariants:

- One successful D3D `Map` creates one live session; one session permits one
  successful `Unmap`.
- A session owns strong references needed to keep the context/resource alive.
- The session records map type, subresource, mapped pointer, row pitch, depth
  pitch, and the validated logical layout.
- Copy functions never trust a caller-provided size by itself. They compute both
  source and destination bounds and copy row-by-row/slice-by-slice when pitches
  differ.
- Releasing a resource handle does not invalidate a live session's native
  references, but the public resource handle generation rules still apply.
- A mapped pointer is never returned to GML, stored as a `double`, logged, or
  reused after unmap.
- Unsupported planar, video, typeless, or depth/stencil transfer cases fail with
  a clear documented error until their layout rules are implemented.

## Files to read first

- `binding/id3d11.gmidl`
- `binding/src/native/ContextExecution.cpp`
- The native handle-registry and error-state implementation under
  `binding/src/native/`
- `scripts/__id3d11_bootstrap/__id3d11_bootstrap.gml`
- `docs/ARCHITECTURE.md`
- `docs/API_COVERAGE.md`
- `README.md`

Read the locally cloned extgen wiki before inventing GMIDL syntax:

```text
D:\Users\Mionumbra\Documents\GitHub\GM-ExtensionGenerator.wiki
```

## Definition of done for the next batch

The batch is complete only when the GMIDL surface, native implementation, generated
extension metadata/GML, smoke tests, and documentation agree; Release compilation
has no new warnings; the GameMaker Runner reaches `game_end()` with all status
flags equal to 1; deployed DLL hashes match each other; and unsupported layout
cases fail safely without native crashes or out-of-bounds memory access.

## Suggested new-task opening prompt

```text
Continue the ID3D11 refactor using docs/NEXT_TASK_HANDOFF.md as the authoritative
handoff. Inspect the current dirty worktree and local extgen wiki first; preserve
all existing changes and do not reset anything. Implement the recommended next
batch for safe UpdateSubresource and Map/Unmap data transfer, including DXGI
subresource-layout validation, GMIDL/native/GML tests, Release build, packaging,
Runner verification ending in game_end(), DLL hash comparison, and documentation.
If the safest recommended design is blocked by a missing tool or SDK component,
stop and tell me exactly what to install instead of silently choosing a weaker
design.
```

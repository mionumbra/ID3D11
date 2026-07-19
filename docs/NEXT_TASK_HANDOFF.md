# Next Task Handoff

Date: 2026-07-19

## Current status

Completed priority batch 1–3:

1. **OMSet/GetRenderTargetsAndUnorderedAccessViews**
   - Explicit `keepRenderTargets` / `keepUnorderedAccessViews` flags (no raw 0xFFFFFFFF magic in GML)
   - Overlap validation: UAV start slot must be >= RT count when both are updated
   - Smoke: set RT+UAV, keep-RT clear-UAV, overlap reject, restore, release

2. **ClearState**
   - `id3d11_device_context_clear_state`
   - Smoke captures OM/topology/viewports, clears, verifies empty, restores Runner state

3. **Private data / debug names**
   - `id3d11_device_child_set/get_debug_name` (WKPDID_D3DDebugObjectName)
   - `id3d11_device_child_set/get_private_data` (GUID string + GML buffer)
   - Smoke: name round-trip, 8-byte private payload round-trip, bad GUID reject

## Verified

```text
[ID3D11] bootstrap=1 smoke=1 shader=1 state=1 async=1 context=1 pipeline=1 feature_level=45312
Smoke test passed.
```

## Remaining lower priority

4. **PS UAV (OM UAV slots as dedicated helpers)** — optional convenience over combo API
5. **Deferred context / command list** — CreateDeferredContext, Finish/ExecuteCommandList; complex ownership

## Do not regress

- Never expose raw mapped pointers or `pData` to GML
- Keep generation-checked handles and device-identity checks
- Smoke must restore Runner bindings after ClearState / OM changes
- Keep dynamic-linkage `PSSetShader` off the hardware smoke path
- After native changes: generate → CMake Release → gm-cli → `scripts/smoke.ps1`

# Next Task Handoff

Date: 2026-07-19

## Current status

Priority batch 1–5 from earlier handoff is complete, including deferred context / command list.

### This session

**Deferred context / command list**
- `id3d11_device_create_deferred_context(device, contextFlags)` — flags must be 0
- `id3d11_device_context_finish_command_list(context, restoreDeferredContextState)` — deferred only
- `id3d11_device_context_execute_command_list(context, commandList, restoreContextState)` — immediate only
- `id3d11_device_context_get_type` / `get_context_flags`
- `id3d11_command_list_get_context_flags`
- Enum `ID3D11DeviceContextType` (Immediate / Deferred)
- Ownership: same handle registry + device-identity checks as other context children
- Smoke: create deferred → record topology → finish → reject wrong context types → execute on immediate with restore → restore Runner OM/topology/viewports → release

## Verified

```text
[ID3D11] bootstrap=1 smoke=1 shader=1 state=1 async=1 context=1 pipeline=1 feature_level=45312
[ID3D11] shutdown complete
Smoke test passed.
```

## Remaining / next ideas

1. **PS UAV convenience wrappers** (optional; OM combo already covers the path)
2. **Device1–5 / Context1–4 real methods** beyond QI transport handles
3. **Demo integration** — use deferred recording in a sample object
4. **Multithread interface** (`ID3D11Multithread`) if multi-threaded GML workers are planned

## Do not regress

- FinishCommandList only on deferred; ExecuteCommandList only on immediate
- Smoke must restore Runner state after Execute (even with restoreContextState=true, be defensive)
- Never expose raw mapped pointers to GML
- After native changes: generate → CMake Release → gm-cli → `scripts/smoke.ps1`

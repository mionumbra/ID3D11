# Next Task Handoff

Date: 2026-07-24

## Policy

- No Runner VMT shader override / draw hooks.
- Do not migrate PCR `obj_chart_sfx` until a full explicit-path rewrite is ready.
- Device/context rebuild (e.g. VSync swapchain recreate) is **user-owned**: re-bootstrap + recreate resources.
- Dynamic-linkage shader smoke is opt-in through `ID3D11_DYNAMIC_LINKAGE_SMOKE=1`.
  NVIDIA 582.66 crashes asynchronously in `nvgpucomp64.dll` during
  `CreatePixelShader`, even if the shader is never bound. Use the native probe
  with `--warp` as the stable control path.
- Backbuffer present is opt-in through `ID3D11_PRESENT=1`. The initial
  implementation acquired the Runner backbuffer and created an RTV, but
  continuous per-frame drawing caused a Runner stack overflow (`0xC00000FD`).
  It is not enabled by default and needs a reduced reproduction.

## This session

### Explicit-path demo: `OId3d11Triangle` / `RmId3d11Triangle`

Pure `id3d11` pipeline (no hooks):
1. Compile VS/PS, create input layout + immutable VB
2. Offscreen RT + RTV + staging texture
3. Immediate: bind OM/IA/VS/PS/RS → clear → draw triangle → copy → map_read → check center pixel `(255,64,0)`
4. Deferred: same draws on deferred context → FinishCommandList → Execute on immediate
5. Always restore Runner OM/VS/PS/IA/RS and PS constant-buffer state after touching the context
6. Do **not** release interned handles from Get* calls

### Bootstrap smoke auto-exit fix

Smoke used to always `id3d11_shutdown` + `game_end` after bootstrap, which prevented any demo room from running.

Now auto-exit only when:
- env `ID3D11_SMOKE_AUTO_EXIT=1`, or
- marker file `ID3D11_SMOKE_AUTO_EXIT` (created by `scripts/smoke.ps1`)

### Verified

```text
[ID3D11] bootstrap=1 smoke=1 ... pipeline=1
Smoke test passed.

[ID3D11] triangle demo status=immediate ok ok=1 deferred_ok=1 rgba=(255,64,0)
```

### Animated PS constant buffer

`OId3d11Triangle` now:

1. Creates a 16-byte default-usage constant buffer bound at PS slot 0.
2. Updates its `float4` color each Draw event through checked `UpdateSubresource`.
3. Draws and reads back the offscreen target every frame, comparing RGB against the current constant-buffer values.
4. Restores the Runner's previous PS constant-buffer slot together with OM/VS/PS/IA/RS state.
5. Uses the same constant buffer in the deferred-context command list proof.

Runtime verification produced:

```text
[ID3D11] triangle demo status=animated cbuffer ok ok=1 deferred_ok=1 rgba=(255,64,0) expected=(255,64,0)
[ID3D11] animated_triangle=1 deferred=1 rgba=(188,212,1) expected=(188,212,1)
```

The second line came from a temporary three-frame auto-exit harness and is not retained in the project.

1. Reduce opt-in backbuffer present to one controlled draw and establish whether the Runner Draw event permits direct backbuffer mutation.
2. Device1–5 / Context1–4 real methods as demos need them

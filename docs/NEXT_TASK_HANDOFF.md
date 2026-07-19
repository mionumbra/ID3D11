# Next Task Handoff

Date: 2026-07-19

## Policy

- No Runner VMT shader override / draw hooks.
- Do not migrate PCR `obj_chart_sfx` until a full explicit-path rewrite is ready.
- Device/context rebuild (e.g. VSync swapchain recreate) is **user-owned**: re-bootstrap + recreate resources.

## This session

### Explicit-path demo: `OId3d11Triangle` / `RmId3d11Triangle`

Pure `id3d11` pipeline (no hooks):
1. Compile VS/PS, create input layout + immutable VB
2. Offscreen RT + RTV + staging texture
3. Immediate: bind OM/IA/VS/PS/RS → clear → draw triangle → copy → map_read → check center pixel `(255,64,0)`
4. Deferred: same draws on deferred context → FinishCommandList → Execute on immediate
5. Always restore Runner OM/VS/PS/IA/RS after touching the context
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

## Next ideas

1. Expand triangle demo: PS cbuffer + animated color (closer to chart_sfx data path, still explicit)
2. Optional present path (draw RT to screen without hooks)
3. Device1–5 / Context1–4 real methods as demos need them

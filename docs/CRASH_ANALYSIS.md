# Crash Analysis

## NVIDIA dynamic-linkage shader crash

Observed on 2026-07-24 with:

- GameMaker Runner 2026.0.0.23
- NVIDIA driver 582.66 (`32.0.15.8266`)
- `nvgpucomp64.dll` version `32.0.15.8266`

Windows Error Reporting and CDB agree on one repeated signature:

```text
Exception: 0xc0000005 (invalid pointer read)
Module: nvgpucomp64.dll
Offset: 0xF948EA
Read address: 0x30
Failure bucket: INVALID_POINTER_READ_c0000005_nvgpucomp64.dll!Unknown
```

The crash occurs on an NVIDIA compiler worker thread one to two seconds after
`ID3D11Device::CreatePixelShader` returns for a valid Shader Model 5 dynamic
class-linkage pixel shader. Binding the shader is not required to reproduce it.

The standalone probe reproduces the crash without GameMaker, the extension,
wire buffers, or the handle registry:

```powershell
cmake -S binding/probes -B binding/probes/out/build/win-v145 `
  -G "Visual Studio 18 2026" -A x64 -T v145
cmake --build binding/probes/out/build/win-v145 --config Debug

# Reproduces on NVIDIA 582.66, including with --no-bind.
binding/probes/out/build/win-v145/Debug/ID3D11DynamicLinkageProbe.exe
binding/probes/out/build/win-v145/Debug/ID3D11DynamicLinkageProbe.exe --no-bind

# Stable control path.
binding/probes/out/build/win-v145/Debug/ID3D11DynamicLinkageProbe.exe --warp
```

The normal GameMaker bootstrap therefore skips this one driver-sensitive smoke
case. Set `ID3D11_DYNAMIC_LINKAGE_SMOKE=1` only for controlled compatibility
testing. The public class-linkage API remains available.

After the change, ten consecutive hardware Runner smoke tests passed and the
number of `Runner.exe` crash dumps remained unchanged.

## Dump analysis

Local WER dumps are under `%LOCALAPPDATA%\CrashDumps`. Analyze one with:

```powershell
& "D:\Windows Kits\10\Debuggers\x64\cdb.exe" `
  -z "$env:LOCALAPPDATA\CrashDumps\Runner.exe.<pid>.dmp" `
  -c ".symfix; .reload; !analyze -v; .ecxr; kv; ~* k; q"
```

Use a Debug extension build and matching PDB when the exception stack enters
`ID3D11.dll`. This NVIDIA failure is asynchronous and its exception thread does
not contain extension frames, which is why the standalone WARP/hardware probe is
the decisive isolation test.

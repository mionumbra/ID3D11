# Present Path Status

`id3d11_swapchain_get_buffer` obtains a Runner-owned swapchain backbuffer as a
typed `Texture2D` handle. Existing RTV creation can then create a compatible
render-target view without exposing raw DXGI pointers.

The triangle demo enables direct backbuffer drawing only when:

```powershell
$env:ID3D11_PRESENT = "1"
gm-cli run "ID3D11.yyp" --target=windows --runtime=vm
```

The first frame reaches:

```text
[ID3D11] triangle demo status=animated cbuffer ok ok=1 deferred_ok=1 present_ok=1 ...
```

However, continuous per-frame direct drawing caused a Runner stack overflow
(`0xC00000FD`) after several seconds. CDB shows the repeating failing stack
entirely in Runner draw/dispatch code, not in `ID3D11.dll`. This feature is not
stable and remains opt-in.

Next work should reduce the path to one backbuffer draw, one state restore, and
no per-frame readback. Compare it with a no-op room and confirm whether the
Runner Draw event permits direct mutation of its current OM target. Do not add
Present/VMT hooks as a workaround.

/// Explicit id3d11 path demo: no hooks, no Runner shader override.
/// Draws a clip-space triangle into an offscreen RT, readbacks, optionally via deferred.
/// Device/context rebuild is the caller's job (re-run bootstrap + recreate resources).

status = "init";
ok = false;
deferred_ok = false;
detail = "";

vs = 0;
ps = 0;
input_layout = 0;
vertex_buffer = 0;
rt_texture = 0;
rtv = 0;
staging_texture = 0;
bytecode_vs = undefined;
bytecode_ps = undefined;
errors = undefined;

if (!global.__id3d11_bootstrap_ok)
{
	status = "bootstrap failed";
	detail = "global.__id3d11_bootstrap_ok is false";
	exit;
}

var _device = global.__id3d11_device;
var _context = global.__id3d11_context;
var _compile_flags = 0;

bytecode_vs = buffer_create(65536, buffer_fixed, 1);
bytecode_ps = buffer_create(65536, buffer_fixed, 1);
errors = buffer_create(4096, buffer_fixed, 1);

var _vs_source =
	"float4 main(float4 position : POSITION) : SV_Position { return position; }";
var _vs_compile = id3d11_compile_shader(
	_vs_source,
	"id3d11_triangle_vs",
	"main",
	"vs_5_0",
	_compile_flags,
	0,
	bytecode_vs,
	errors);
if (_vs_compile.hresult != 0)
{
	status = "vs compile failed";
	detail = string(id3d11_get_last_hresult());
	exit;
}

var _vs_result = id3d11_device_create_vertex_shader(
	_device,
	bytecode_vs,
	_vs_compile.bytecodeSize,
	0);
if (_vs_result.hresult != 0)
{
	status = "vs create failed";
	detail = string(_vs_result.hresult);
	exit;
}
vs = _vs_result.handle;
id3d11_device_child_set_debug_name(vs, "id3d11.demo.triangle.vs");

var _ps_source =
	"float4 main() : SV_Target { return float4(1.0, 0.25, 0.0, 1.0); }";
var _ps_compile = id3d11_compile_shader(
	_ps_source,
	"id3d11_triangle_ps",
	"main",
	"ps_5_0",
	_compile_flags,
	0,
	bytecode_ps,
	errors);
if (_ps_compile.hresult != 0)
{
	status = "ps compile failed";
	detail = string(_ps_compile.hresult);
	exit;
}

var _ps_result = id3d11_device_create_pixel_shader(
	_device,
	bytecode_ps,
	_ps_compile.bytecodeSize,
	0);
if (_ps_result.hresult != 0)
{
	status = "ps create failed";
	detail = string(_ps_result.hresult);
	exit;
}
ps = _ps_result.handle;
id3d11_device_child_set_debug_name(ps, "id3d11.demo.triangle.ps");

var _element = new ID3D11InputElementDesc();
_element.semanticName = "POSITION";
_element.semanticIndex = 0;
_element.format = DXGI_FORMAT_R32G32B32A32_FLOAT;
_element.inputSlot = 0;
_element.alignedByteOffset = 0;
_element.inputSlotClass = ID3D11InputClassification.PerVertexData;
_element.instanceDataStepRate = 0;
var _layout_result = id3d11_device_create_input_layout(
	_device,
	[_element],
	bytecode_vs,
	_vs_compile.bytecodeSize);
if (_layout_result.hresult != 0)
{
	status = "input layout failed";
	detail = string(_layout_result.hresult);
	exit;
}
input_layout = _layout_result.handle;

// Clip-space triangle (float4 * 3)
var _vb_data = buffer_create(48, buffer_fixed, 1);
// CW winding (D3D default front face when FrontCounterClockwise=false)
buffer_write(_vb_data, buffer_f32, 0.0);
buffer_write(_vb_data, buffer_f32, 0.75);
buffer_write(_vb_data, buffer_f32, 0.0);
buffer_write(_vb_data, buffer_f32, 1.0);
buffer_write(_vb_data, buffer_f32, 0.75);
buffer_write(_vb_data, buffer_f32, -0.75);
buffer_write(_vb_data, buffer_f32, 0.0);
buffer_write(_vb_data, buffer_f32, 1.0);
buffer_write(_vb_data, buffer_f32, -0.75);
buffer_write(_vb_data, buffer_f32, -0.75);
buffer_write(_vb_data, buffer_f32, 0.0);
buffer_write(_vb_data, buffer_f32, 1.0);

var _vb_desc = new ID3D11BufferDesc();
_vb_desc.byteWidth = 48;
_vb_desc.usage = ID3D11Usage.Immutable;
_vb_desc.bindFlags = ID3D11BindFlag.VertexBuffer;
_vb_desc.cpuAccessFlags = 0;
_vb_desc.miscFlags = 0;
_vb_desc.structureByteStride = 0;
var _vb_result = id3d11_device_create_buffer_with_data(_device, _vb_desc, _vb_data);
buffer_delete(_vb_data);
if (_vb_result.hresult != 0)
{
	status = "vertex buffer failed";
	detail = string(_vb_result.hresult);
	exit;
}
vertex_buffer = _vb_result.handle;

var _rt_desc = new ID3D11Texture2DDesc();
_rt_desc.width = 64;
_rt_desc.height = 64;
_rt_desc.mipLevels = 1;
_rt_desc.arraySize = 1;
_rt_desc.format = DXGI_FORMAT_R8G8B8A8_UNORM;
_rt_desc.sampleCount = 1;
_rt_desc.sampleQuality = 0;
_rt_desc.usage = ID3D11Usage.Default;
_rt_desc.bindFlags = ID3D11BindFlag.RenderTarget;
_rt_desc.cpuAccessFlags = 0;
_rt_desc.miscFlags = 0;
var _rt_result = id3d11_device_create_texture2d(_device, _rt_desc);
if (_rt_result.hresult != 0)
{
	status = "rt texture failed";
	detail = string(_rt_result.hresult);
	exit;
}
rt_texture = _rt_result.handle;

var _rtv_result = id3d11_device_create_render_target_view_default(_device, rt_texture);
if (_rtv_result.hresult != 0)
{
	status = "rtv failed";
	detail = string(_rtv_result.hresult);
	exit;
}
rtv = _rtv_result.handle;

var _staging_desc = new ID3D11Texture2DDesc();
_staging_desc.width = 64;
_staging_desc.height = 64;
_staging_desc.mipLevels = 1;
_staging_desc.arraySize = 1;
_staging_desc.format = DXGI_FORMAT_R8G8B8A8_UNORM;
_staging_desc.sampleCount = 1;
_staging_desc.sampleQuality = 0;
_staging_desc.usage = ID3D11Usage.Staging;
_staging_desc.bindFlags = 0;
_staging_desc.cpuAccessFlags = ID3D11CpuAccessFlag.Read;
_staging_desc.miscFlags = 0;
var _staging_result = id3d11_device_create_texture2d(_device, _staging_desc);
if (_staging_result.hresult != 0)
{
	status = "staging failed";
	detail = string(_staging_result.hresult);
	exit;
}
staging_texture = _staging_result.handle;

var _bind_draw = function(_ctx, _vs, _ps, _layout, _vb, _rtv)
{
	var _viewport = new ID3D11Viewport();
	_viewport.topLeftX = 0;
	_viewport.topLeftY = 0;
	_viewport.width = 64;
	_viewport.height = 64;
	_viewport.minDepth = 0;
	_viewport.maxDepth = 1;

	var _vb_bind = new ID3D11VertexBufferBinding();
	_vb_bind.buffer = _vb;
	_vb_bind.stride = 16;
	_vb_bind.offset = 0;

	if (!id3d11_device_context_om_set_render_targets(_ctx, [_rtv], 0))
	{
		return "om_set_render_targets";
	}
	if (!id3d11_device_context_rs_set_viewports(_ctx, [_viewport]))
	{
		return "rs_set_viewports";
	}
	if (!id3d11_device_context_ia_set_input_layout(_ctx, _layout))
	{
		return "ia_set_input_layout";
	}
	if (!id3d11_device_context_ia_set_primitive_topology(_ctx, 4))
	{
		return "ia_set_primitive_topology";
	}
	if (!id3d11_device_context_ia_set_vertex_buffers(_ctx, 0, [_vb_bind]))
	{
		return "ia_set_vertex_buffers";
	}
	if (!id3d11_device_context_vs_set_shader(_ctx, _vs, []))
	{
		return "vs_set_shader";
	}
	if (!id3d11_device_context_ps_set_shader(_ctx, _ps, []))
	{
		return "ps_set_shader";
	}
	if (!id3d11_device_context_clear_render_target_view(_ctx, _rtv, 0.05, 0.05, 0.1, 1))
	{
		return "clear_rtv";
	}
	if (!id3d11_device_context_draw(_ctx, 3, 0))
	{
		return "draw";
	}
	return "";
};

// ---- immediate path ----
var _prev_om = id3d11_device_context_om_get_render_targets(_context, 1);
var _prev_vs = id3d11_device_context_vs_get_shader(_context);
var _prev_ps = id3d11_device_context_ps_get_shader(_context);
var _prev_layout = id3d11_device_context_ia_get_input_layout(_context);
var _prev_topology = id3d11_device_context_ia_get_primitive_topology(_context);
var _prev_vbs = id3d11_device_context_ia_get_vertex_buffers(_context, 0, 1);
var _prev_viewports = id3d11_device_context_rs_get_viewports(_context);

var _draw_err = _bind_draw(_context, vs, ps, input_layout, vertex_buffer, rtv);
if (_draw_err != "")
{
	status = "immediate draw failed";
	detail = _draw_err;
}
else
{
	id3d11_device_context_copy_resource(_context, staging_texture, rt_texture);
	var _readback = buffer_create(64 * 64 * 4, buffer_fixed, 1);
	var _map_ok = id3d11_device_context_map_read_to_buffer(
		_context,
		staging_texture,
		0,
		ID3D11Map.Read,
		0,
		_readback);
	if (!_map_ok)
	{
		status = "readback failed";
		detail = string(id3d11_get_last_hresult());
	}
	else
	{
		// Center pixel (32,32), row pitch may be 256 for 64*4
		var _center = buffer_peek(_readback, ((32 * 64) + 32) * 4, buffer_u32);
		// R8G8B8A8 little-endian: 0xFF0040FF expected-ish for (1,0.25,0,1) -> R=255 G=64 B=0 A=255
		var _r = _center & 0xff;
		var _g = (_center >> 8) & 0xff;
		var _b = (_center >> 16) & 0xff;
		ok = (_r > 200 && _g > 20 && _g < 120 && _b < 40);
		status = ok ? "immediate ok" : "pixel mismatch";
		detail = $"rgba=({_r},{_g},{_b}) raw={_center}";
	}
	buffer_delete(_readback);
}

// Restore Runner bindings (defensive even if draw failed mid-way).
// Do NOT release handles returned by Get* — they are interned views of Runner-owned objects.
id3d11_device_context_om_set_render_targets(
	_context,
	_prev_om.renderTargetViews,
	_prev_om.depthStencilView);
var _prev_vs_ci = is_array(_prev_vs.classInstances) ? _prev_vs.classInstances : [];
var _prev_ps_ci = is_array(_prev_ps.classInstances) ? _prev_ps.classInstances : [];
id3d11_device_context_vs_set_shader(_context, _prev_vs.shader, _prev_vs_ci);
id3d11_device_context_ps_set_shader(_context, _prev_ps.shader, _prev_ps_ci);
id3d11_device_context_ia_set_input_layout(_context, _prev_layout);
id3d11_device_context_ia_set_primitive_topology(_context, _prev_topology);
id3d11_device_context_ia_set_vertex_buffers(_context, 0, _prev_vbs);
id3d11_device_context_rs_set_viewports(_context, _prev_viewports);

// ---- deferred path (optional second proof) ----
var _deferred = id3d11_device_create_deferred_context(_device, 0);
if (_deferred.hresult == 0)
{
	var _def_err = _bind_draw(
		_deferred.handle,
		vs,
		ps,
		input_layout,
		vertex_buffer,
		rtv);
	if (_def_err == "")
	{
		var _clist = id3d11_device_context_finish_command_list(_deferred.handle, false);
		if (_clist.hresult == 0)
		{
			var _prev_om2 = id3d11_device_context_om_get_render_targets(_context, 1);
			var _exec = id3d11_device_context_execute_command_list(
				_context,
				_clist.handle,
				true);
			id3d11_device_context_om_set_render_targets(
				_context,
				_prev_om2.renderTargetViews,
				_prev_om2.depthStencilView);
			id3d11_handle_release(_clist.handle);
			deferred_ok = _exec;
		}
	}
	id3d11_handle_release(_deferred.handle);
}

show_debug_message(
	$"[ID3D11] triangle demo status={status} ok={ok} deferred_ok={deferred_ok} {detail}");

// Leave device alive for multi-room browsing. CleanUp releases demo resources.
// Device/context rebuild remains user-owned (re-bootstrap + recreate).
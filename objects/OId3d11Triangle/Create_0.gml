/// Explicit id3d11 path demo: no hooks, no Runner shader override.
/// Draws a clip-space triangle into an offscreen RT, readbacks, optionally via deferred.
/// Device/context rebuild is the caller's job (re-run bootstrap + recreate resources).

status = "init";
ok = false;
deferred_ok = false;
ready = false;
detail = "";

vs = 0;
ps = 0;
input_layout = 0;
vertex_buffer = 0;
constant_buffer = 0;
rt_texture = 0;
rtv = 0;
staging_texture = 0;
backbuffer_texture = 0;
backbuffer_rtv = 0;
constant_data = undefined;
bytecode_vs = undefined;
bytecode_ps = undefined;
errors = undefined;
color_r = 1.0;
color_g = 0.25;
color_b = 0.0;
present_ok = false;
present_enabled = environment_get_variable("ID3D11_PRESENT") == "1";
backbuffer_width = 0;
backbuffer_height = 0;

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
	"cbuffer TriangleColor : register(b0) { float4 color; }; " +
	"float4 main() : SV_Target { return color; }";
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

constant_data = buffer_create(16, buffer_fixed, 1);
buffer_write(constant_data, buffer_f32, color_r);
buffer_write(constant_data, buffer_f32, color_g);
buffer_write(constant_data, buffer_f32, color_b);
buffer_write(constant_data, buffer_f32, 1.0);

var _cb_desc = new ID3D11BufferDesc();
_cb_desc.byteWidth = 16;
_cb_desc.usage = ID3D11Usage.Default;
_cb_desc.bindFlags = ID3D11BindFlag.ConstantBuffer;
_cb_desc.cpuAccessFlags = 0;
_cb_desc.miscFlags = 0;
_cb_desc.structureByteStride = 0;
var _cb_result = id3d11_device_create_buffer_with_data(
	_device,
	_cb_desc,
	constant_data);
if (_cb_result.hresult != 0)
{
	status = "constant buffer failed";
	detail = string(_cb_result.hresult);
	exit;
}
constant_buffer = _cb_result.handle;
id3d11_device_child_set_debug_name(
	constant_buffer,
	"id3d11.demo.triangle.color");

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

if (present_enabled)
{
	var _swapchain = id3d11_get_swapchain_handle();
	var _backbuffer_result = id3d11_swapchain_get_buffer(_swapchain, 0);
	id3d11_handle_release(_swapchain);
	if (_backbuffer_result.hresult != 0)
	{
		status = "backbuffer failed";
		detail = string(_backbuffer_result.hresult);
		exit;
	}
	backbuffer_texture = _backbuffer_result.handle;
	var _backbuffer_desc = id3d11_texture2d_get_desc(backbuffer_texture);
	backbuffer_width = _backbuffer_desc.width;
	backbuffer_height = _backbuffer_desc.height;
	var _backbuffer_rtv_result = id3d11_device_create_render_target_view_default(
		_device,
		backbuffer_texture);
	if (_backbuffer_rtv_result.hresult != 0)
	{
		status = "backbuffer rtv failed";
		detail = string(_backbuffer_rtv_result.hresult);
		exit;
	}
	backbuffer_rtv = _backbuffer_rtv_result.handle;
	present_ok = backbuffer_width > 0 && backbuffer_height > 0;
}

bind_draw = function(_ctx, _vs, _ps, _layout, _vb, _cb, _rtv, _width, _height, _clear)
{
	var _viewport = new ID3D11Viewport();
	_viewport.topLeftX = 0;
	_viewport.topLeftY = 0;
	_viewport.width = _width;
	_viewport.height = _height;
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
	if (!id3d11_device_context_ps_set_constant_buffers(_ctx, 0, [_cb]))
	{
		return "ps_set_constant_buffers";
	}
	if (_clear && !id3d11_device_context_clear_render_target_view(_ctx, _rtv, 0.05, 0.05, 0.1, 1))
	{
		return "clear_rtv";
	}
	if (!id3d11_device_context_draw(_ctx, 3, 0))
	{
		return "draw";
	}
	return "";
};

render_immediate = function()
{
	var _ctx = global.__id3d11_context;
	var _prev_om = id3d11_device_context_om_get_render_targets(_ctx, 8);
	var _prev_vs = id3d11_device_context_vs_get_shader(_ctx);
	var _prev_ps = id3d11_device_context_ps_get_shader(_ctx);
	var _prev_ps_cbs = id3d11_device_context_ps_get_constant_buffers(_ctx, 0, 1);
	var _prev_layout = id3d11_device_context_ia_get_input_layout(_ctx);
	var _prev_topology = id3d11_device_context_ia_get_primitive_topology(_ctx);
	var _prev_vbs = id3d11_device_context_ia_get_vertex_buffers(_ctx, 0, 1);
	var _prev_viewports = id3d11_device_context_rs_get_viewports(_ctx);

	var _draw_err = bind_draw(
		_ctx,
		vs,
		ps,
		input_layout,
		vertex_buffer,
		constant_buffer,
		rtv,
		64,
		64,
		true);
	if (_draw_err != "")
	{
		status = "immediate draw failed";
		detail = _draw_err;
	}
	else
	{
		id3d11_device_context_copy_resource(_ctx, staging_texture, rt_texture);
		var _readback = buffer_create(64 * 64 * 4, buffer_fixed, 1);
		var _map_ok = id3d11_device_context_map_read_to_buffer(
			_ctx,
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
			var _center = buffer_peek(
				_readback,
				((32 * 64) + 32) * 4,
				buffer_u32);
			var _r = _center & 0xff;
			var _g = (_center >> 8) & 0xff;
			var _b = (_center >> 16) & 0xff;
			var _expected_r = round(color_r * 255);
			var _expected_g = round(color_g * 255);
			var _expected_b = round(color_b * 255);
			ok =
				abs(_r - _expected_r) <= 2 &&
				abs(_g - _expected_g) <= 2 &&
				abs(_b - _expected_b) <= 2;
			status = ok ? "animated cbuffer ok" : "pixel mismatch";
			detail =
				$"rgba=({_r},{_g},{_b}) expected=({_expected_r},{_expected_g},{_expected_b})";
		}
		buffer_delete(_readback);
	}

	var _restore_ok = id3d11_device_context_om_set_render_targets(
		_ctx,
		_prev_om.renderTargetViews,
		_prev_om.depthStencilView);
	var _prev_vs_ci = is_array(_prev_vs.classInstances) ? _prev_vs.classInstances : [];
	var _prev_ps_ci = is_array(_prev_ps.classInstances) ? _prev_ps.classInstances : [];
	_restore_ok = id3d11_device_context_vs_set_shader(_ctx, _prev_vs.shader, _prev_vs_ci) && _restore_ok;
	_restore_ok = id3d11_device_context_ps_set_shader(_ctx, _prev_ps.shader, _prev_ps_ci) && _restore_ok;
	_restore_ok = id3d11_device_context_ps_set_constant_buffers(_ctx, 0, _prev_ps_cbs) && _restore_ok;
	_restore_ok = id3d11_device_context_ia_set_input_layout(_ctx, _prev_layout) && _restore_ok;
	_restore_ok = id3d11_device_context_ia_set_primitive_topology(_ctx, _prev_topology) && _restore_ok;
	_restore_ok = id3d11_device_context_ia_set_vertex_buffers(_ctx, 0, _prev_vbs) && _restore_ok;
	_restore_ok = id3d11_device_context_rs_set_viewports(_ctx, _prev_viewports) && _restore_ok;
	if (!_restore_ok)
	{
		ok = false;
		status = "Runner state restore failed";
		detail = string(id3d11_get_last_hresult());
	}
	array_foreach(_prev_om.renderTargetViews, function(_handle) { if (_handle != 0) id3d11_handle_release(_handle); });
	if (_prev_om.depthStencilView != 0) id3d11_handle_release(_prev_om.depthStencilView);
	if (_prev_vs.shader != 0) id3d11_handle_release(_prev_vs.shader);
	array_foreach(_prev_vs_ci, function(_handle) { if (_handle != 0) id3d11_handle_release(_handle); });
	if (_prev_ps.shader != 0) id3d11_handle_release(_prev_ps.shader);
	array_foreach(_prev_ps_ci, function(_handle) { if (_handle != 0) id3d11_handle_release(_handle); });
	array_foreach(_prev_ps_cbs, function(_handle) { if (_handle != 0) id3d11_handle_release(_handle); });
	if (_prev_layout != 0) id3d11_handle_release(_prev_layout);
	array_foreach(_prev_vbs, function(_binding) { if (_binding.buffer != 0) id3d11_handle_release(_binding.buffer); });
};

render_present = function()
{
	if (!present_ok)
	{
		return;
	}

	var _ctx = global.__id3d11_context;
	var _prev_om = id3d11_device_context_om_get_render_targets(_ctx, 8);
	var _prev_vs = id3d11_device_context_vs_get_shader(_ctx);
	var _prev_ps = id3d11_device_context_ps_get_shader(_ctx);
	var _prev_ps_cbs = id3d11_device_context_ps_get_constant_buffers(_ctx, 0, 1);
	var _prev_layout = id3d11_device_context_ia_get_input_layout(_ctx);
	var _prev_topology = id3d11_device_context_ia_get_primitive_topology(_ctx);
	var _prev_vbs = id3d11_device_context_ia_get_vertex_buffers(_ctx, 0, 1);
	var _prev_viewports = id3d11_device_context_rs_get_viewports(_ctx);

	var _present_err = bind_draw(
		_ctx,
		vs,
		ps,
		input_layout,
		vertex_buffer,
		constant_buffer,
		backbuffer_rtv,
		backbuffer_width,
		backbuffer_height,
		false);
	if (_present_err != "")
	{
		present_ok = false;
		status = "present draw failed";
		detail = _present_err;
	}

	var _restore_ok = id3d11_device_context_om_set_render_targets(
		_ctx,
		_prev_om.renderTargetViews,
		_prev_om.depthStencilView);
	var _prev_vs_ci = is_array(_prev_vs.classInstances) ? _prev_vs.classInstances : [];
	var _prev_ps_ci = is_array(_prev_ps.classInstances) ? _prev_ps.classInstances : [];
	_restore_ok = id3d11_device_context_vs_set_shader(_ctx, _prev_vs.shader, _prev_vs_ci) && _restore_ok;
	_restore_ok = id3d11_device_context_ps_set_shader(_ctx, _prev_ps.shader, _prev_ps_ci) && _restore_ok;
	_restore_ok = id3d11_device_context_ps_set_constant_buffers(_ctx, 0, _prev_ps_cbs) && _restore_ok;
	_restore_ok = id3d11_device_context_ia_set_input_layout(_ctx, _prev_layout) && _restore_ok;
	_restore_ok = id3d11_device_context_ia_set_primitive_topology(_ctx, _prev_topology) && _restore_ok;
	_restore_ok = id3d11_device_context_ia_set_vertex_buffers(_ctx, 0, _prev_vbs) && _restore_ok;
	_restore_ok = id3d11_device_context_rs_set_viewports(_ctx, _prev_viewports) && _restore_ok;
	if (!_restore_ok)
	{
		present_ok = false;
		ok = false;
		status = "Runner state restore failed";
		detail = string(id3d11_get_last_hresult());
	}
	array_foreach(_prev_om.renderTargetViews, function(_handle) { if (_handle != 0) id3d11_handle_release(_handle); });
	if (_prev_om.depthStencilView != 0) id3d11_handle_release(_prev_om.depthStencilView);
	if (_prev_vs.shader != 0) id3d11_handle_release(_prev_vs.shader);
	array_foreach(_prev_vs_ci, function(_handle) { if (_handle != 0) id3d11_handle_release(_handle); });
	if (_prev_ps.shader != 0) id3d11_handle_release(_prev_ps.shader);
	array_foreach(_prev_ps_ci, function(_handle) { if (_handle != 0) id3d11_handle_release(_handle); });
	array_foreach(_prev_ps_cbs, function(_handle) { if (_handle != 0) id3d11_handle_release(_handle); });
	if (_prev_layout != 0) id3d11_handle_release(_prev_layout);
	array_foreach(_prev_vbs, function(_binding) { if (_binding.buffer != 0) id3d11_handle_release(_binding.buffer); });
};

// ---- immediate path ----
ready = true;
render_immediate();

// ---- deferred path (optional second proof) ----
var _deferred = id3d11_device_create_deferred_context(_device, 0);
if (_deferred.hresult == 0)
{
	var _def_err = bind_draw(
		_deferred.handle,
		vs,
		ps,
		input_layout,
		vertex_buffer,
		constant_buffer,
		rtv,
		64,
		64,
		true);
	if (_def_err == "")
	{
		var _clist = id3d11_device_context_finish_command_list(_deferred.handle, false);
		if (_clist.hresult == 0)
		{
			var _exec = id3d11_device_context_execute_command_list(
				_context,
				_clist.handle,
				true);
			id3d11_handle_release(_clist.handle);
			deferred_ok = _exec;
		}
	}
	id3d11_handle_release(_deferred.handle);
}

show_debug_message(
	$"[ID3D11] triangle demo status={status} ok={ok} deferred_ok={deferred_ok} present_ok={present_ok} {detail}");

// Leave device alive for multi-room browsing. CleanUp releases demo resources.
// Device/context rebuild remains user-owned (re-bootstrap + recreate).

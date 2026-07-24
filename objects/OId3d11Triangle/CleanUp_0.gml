var _release = function(_handle)
{
	if (_handle != 0 && id3d11_is_initialized())
	{
		id3d11_handle_release(_handle);
	}
};

bind_draw = undefined;
render_immediate = undefined;
render_present = undefined;
ready = false;

_release(vs);
_release(ps);
_release(input_layout);
_release(vertex_buffer);
_release(constant_buffer);
_release(rtv);
_release(rt_texture);
_release(staging_texture);
_release(backbuffer_rtv);
_release(backbuffer_texture);

if (is_undefined(constant_data) == false && buffer_exists(constant_data))
{
	buffer_delete(constant_data);
}

if (is_undefined(bytecode_vs) == false && buffer_exists(bytecode_vs))
{
	buffer_delete(bytecode_vs);
}
if (is_undefined(bytecode_ps) == false && buffer_exists(bytecode_ps))
{
	buffer_delete(bytecode_ps);
}
if (is_undefined(errors) == false && buffer_exists(errors))
{
	buffer_delete(errors);
}

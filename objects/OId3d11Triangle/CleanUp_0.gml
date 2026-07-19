var _release = function(_handle)
{
	if (_handle != 0)
	{
		id3d11_handle_release(_handle);
	}
};

_release(vs);
_release(ps);
_release(input_layout);
_release(vertex_buffer);
_release(rtv);
_release(rt_texture);
_release(staging_texture);

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

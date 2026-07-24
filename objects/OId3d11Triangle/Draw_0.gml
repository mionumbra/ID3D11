if (ready && id3d11_is_initialized())
{
color_r = 0.5 + 0.5 * sin(current_time * 0.0017);
color_g = 0.5 + 0.5 * sin(current_time * 0.0011 + 2.094);
color_b = 0.5 + 0.5 * sin(current_time * 0.0013 + 4.189);
buffer_seek(constant_data, buffer_seek_start, 0);
buffer_write(constant_data, buffer_f32, color_r);
buffer_write(constant_data, buffer_f32, color_g);
buffer_write(constant_data, buffer_f32, color_b);
buffer_write(constant_data, buffer_f32, 1.0);

var _unused_box = new ID3D11Box();
var _updated = id3d11_device_context_update_subresource(
	global.__id3d11_context,
	constant_buffer,
	0,
	false,
	_unused_box,
	constant_data,
	0,
	16,
	16,
	16);
if (_updated)
{
	render_immediate();
	if (present_enabled)
	{
		render_present();
	}
}
else
{
	ok = false;
	status = "constant buffer update failed";
	detail = string(id3d11_get_last_hresult());
}
}

var _immediate = ok ? "PASS" : "FAIL";
var _deferred = deferred_ok ? "PASS" : "FAIL";
var _text =
	"id3d11 animated cbuffer triangle\n" +
	"status: " + string(status) + "\n" +
	"immediate: " + _immediate + "\n" +
	"deferred: " + _deferred + "\n" +
	"present: " + string(present_ok ? "PASS" : "FAIL") + "\n" +
	string(detail);

draw_set_color(c_black);
draw_text(9, 9, _text);
draw_set_color(ok && deferred_ok ? c_lime : c_yellow);
draw_text(8, 8, _text);
draw_set_color(c_white);

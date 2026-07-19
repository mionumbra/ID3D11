var _immediate = ok ? "PASS" : "FAIL";
var _deferred = deferred_ok ? "PASS" : "FAIL";
var _text =
	"id3d11 explicit triangle demo\n" +
	"status: " + string(status) + "\n" +
	"immediate: " + _immediate + "\n" +
	"deferred: " + _deferred + "\n" +
	string(detail) + "\n" +
	"SPACE: next room";

draw_set_color(c_black);
draw_text(9, 9, _text);
draw_set_color(ok && deferred_ok ? c_lime : c_yellow);
draw_text(8, 8, _text);
draw_set_color(c_white);

global.__id3d11_bootstrap_ok = false;
global.__id3d11_smoke_ok = false;
global.__id3d11_shader_smoke_ok = false;
global.__id3d11_state_smoke_ok = false;
global.__id3d11_async_smoke_ok = false;
global.__id3d11_context_smoke_ok = false;
global.__id3d11_pipeline_smoke_ok = false;
global.__id3d11_version = undefined;
global.__id3d11_device = 0;
global.__id3d11_context = 0;
global.__id3d11_swapchain = 0;
global.__id3d11_device1 = 0;
global.__id3d11_feature_level = 0;

if (os_type == os_windows && os_browser == browser_not_a_browser)
{
	var _info = os_get_info();
	var _has_device = ds_map_exists(_info, "video_d3d11_device");
	var _has_context = ds_map_exists(_info, "video_d3d11_context");
	var _has_swapchain = ds_map_exists(_info, "video_d3d11_swapchain");

	if (_has_device && _has_context && _has_swapchain)
	{
		global.__id3d11_bootstrap_ok = __id3d11_bootstrap_raw(
			_info[? "video_d3d11_device"],
			_info[? "video_d3d11_context"],
			_info[? "video_d3d11_swapchain"]);
	}

	ds_map_destroy(_info);

	if (global.__id3d11_bootstrap_ok)
	{
		global.__id3d11_version = id3d11_get_version();
		global.__id3d11_device = id3d11_get_device_handle();
		global.__id3d11_context = id3d11_get_context_handle();
		global.__id3d11_swapchain = id3d11_get_swapchain_handle();
		global.__id3d11_feature_level = id3d11_device_get_feature_level(global.__id3d11_device);

		var _immediate_context = id3d11_device_get_immediate_context(global.__id3d11_device);
		var _format_support = id3d11_device_check_format_support(global.__id3d11_device, 28);
		var _multisample = id3d11_device_check_multisample_quality_levels(
			global.__id3d11_device,
			28,
			1);
		var _exception_mode = id3d11_device_get_exception_mode(global.__id3d11_device);
		var _exception_result = id3d11_device_set_exception_mode(
			global.__id3d11_device,
			_exception_mode);
		var _device1_stale = id3d11_handle_query_interface(
			global.__id3d11_device,
			ID3D11HandleKind.Device1);
		var _device1_release_ok = id3d11_handle_release(_device1_stale);
		var _device1_stale_rejected = !id3d11_handle_is_valid(_device1_stale);
		global.__id3d11_device1 = id3d11_handle_query_interface(
			global.__id3d11_device,
			ID3D11HandleKind.Device1);

		var _buffer_desc = new ID3D11BufferDesc();
		_buffer_desc.byteWidth = 16;
		_buffer_desc.usage = ID3D11Usage.Default;
		_buffer_desc.bindFlags = 4;
		_buffer_desc.cpuAccessFlags = 0;
		_buffer_desc.miscFlags = 0;
		_buffer_desc.structureByteStride = 0;
		var _buffer_data = buffer_create(16, buffer_fixed, 1);
		buffer_write(_buffer_data, buffer_u32, 1);
		buffer_write(_buffer_data, buffer_u32, 2);
		buffer_write(_buffer_data, buffer_u32, 3);
		buffer_write(_buffer_data, buffer_u32, 4);
		var _buffer_result = id3d11_device_create_buffer_with_data(
			global.__id3d11_device,
			_buffer_desc,
			_buffer_data);
		var _buffer_roundtrip = id3d11_buffer_get_desc(_buffer_result.handle);
		var _buffer_dimension = id3d11_resource_get_dimension(_buffer_result.handle);
		var _buffer_device = id3d11_device_child_get_device(_buffer_result.handle);
		var _debug_name_set = id3d11_device_child_set_debug_name(
			_buffer_result.handle,
			"id3d11.smoke.buffer");
		var _debug_name = id3d11_device_child_get_debug_name(_buffer_result.handle);
		var _private_guid = "01234567-89ab-cdef-0123-456789abcdef";
		var _private_write = buffer_create(8, buffer_fixed, 1);
		buffer_write(_private_write, buffer_u32, $11223344);
		buffer_write(_private_write, buffer_u32, $55667788);
		var _private_set = id3d11_device_child_set_private_data(
			_buffer_result.handle,
			_private_guid,
			_private_write);
		var _private_read = buffer_create(8, buffer_fixed, 1);
		var _private_size = id3d11_device_child_get_private_data(
			_buffer_result.handle,
			_private_guid,
			_private_read);
		buffer_seek(_private_read, buffer_seek_start, 0);
		var _private_word0 = buffer_read(_private_read, buffer_u32);
		var _private_word1 = buffer_read(_private_read, buffer_u32);
		var _private_bad_guid_rejected = !id3d11_device_child_set_private_data(
			_buffer_result.handle,
			"not-a-guid",
			_private_write);
		var _debug_name_smoke_ok =
			_debug_name_set &&
			_debug_name == "id3d11.smoke.buffer" &&
			_private_set &&
			_private_size == 8 &&
			_private_word0 == $11223344 &&
			_private_word1 == $55667788 &&
			_private_bad_guid_rejected;
		buffer_delete(_private_write);
		buffer_delete(_private_read);
		var _buffer_release_ok = id3d11_handle_release(_buffer_result.handle);
		var _buffer_stale_rejected = !id3d11_handle_is_valid(_buffer_result.handle);
		buffer_delete(_buffer_data);

		var _texture1d_desc = new ID3D11Texture1DDesc();
		_texture1d_desc.width = 4;
		_texture1d_desc.mipLevels = 1;
		_texture1d_desc.arraySize = 1;
		_texture1d_desc.format = 28;
		_texture1d_desc.usage = ID3D11Usage.Default;
		_texture1d_desc.bindFlags = ID3D11BindFlag.ShaderResource;
		_texture1d_desc.cpuAccessFlags = 0;
		_texture1d_desc.miscFlags = 0;
		var _texture1d_result = id3d11_device_create_texture1d(
			global.__id3d11_device,
			_texture1d_desc);
		var _texture1d_roundtrip = id3d11_texture1d_get_desc(_texture1d_result.handle);
		var _texture1d_dimension = id3d11_resource_get_dimension(_texture1d_result.handle);
		var _texture1d_release_ok = id3d11_handle_release(_texture1d_result.handle);
		var _texture1d_stale_rejected = !id3d11_handle_is_valid(_texture1d_result.handle);

		var _texture2d_desc = new ID3D11Texture2DDesc();
		_texture2d_desc.width = 2;
		_texture2d_desc.height = 2;
		_texture2d_desc.mipLevels = 1;
		_texture2d_desc.arraySize = 1;
		_texture2d_desc.format = 28;
		_texture2d_desc.sampleCount = 1;
		_texture2d_desc.sampleQuality = 0;
		_texture2d_desc.usage = ID3D11Usage.Default;
		_texture2d_desc.bindFlags =
			ID3D11BindFlag.ShaderResource |
			ID3D11BindFlag.RenderTarget |
			ID3D11BindFlag.UnorderedAccess;
		_texture2d_desc.cpuAccessFlags = 0;
		_texture2d_desc.miscFlags = 0;
		var _texture2d_data = buffer_create(16, buffer_fixed, 1);
		buffer_write(_texture2d_data, buffer_u32, $ff0000ff);
		buffer_write(_texture2d_data, buffer_u32, $ff00ff00);
		buffer_write(_texture2d_data, buffer_u32, $ffff0000);
		buffer_write(_texture2d_data, buffer_u32, $ffffffff);
		var _texture2d_subresource = new ID3D11SubresourceData();
		_texture2d_subresource.offset = 0;
		_texture2d_subresource.rowPitch = 8;
		_texture2d_subresource.slicePitch = 16;
		_texture2d_subresource.dataSize = 16;
		var _texture2d_result = id3d11_device_create_texture2d_with_data(
			global.__id3d11_device,
			_texture2d_desc,
			[_texture2d_subresource],
			_texture2d_data);
		var _texture2d_roundtrip = id3d11_texture2d_get_desc(_texture2d_result.handle);
		var _texture2d_dimension = id3d11_resource_get_dimension(_texture2d_result.handle);
		var _texture2d_device = id3d11_device_child_get_device(_texture2d_result.handle);
		var _texture2d_priority = id3d11_resource_get_eviction_priority(_texture2d_result.handle);
		var _texture2d_priority_ok = id3d11_resource_set_eviction_priority(
			_texture2d_result.handle,
			_texture2d_priority);

		var _srv_desc = new ID3D11ShaderResourceViewDesc();
		_srv_desc.format = 28;
		_srv_desc.viewDimension = ID3D11ShaderResourceViewDimension.Texture2D;
		_srv_desc.mostDetailedMip = 0;
		_srv_desc.mipLevels = 1;
		var _srv_result = id3d11_device_create_shader_resource_view(
			global.__id3d11_device,
			_texture2d_result.handle,
			_srv_desc);
		var _srv_default_result = id3d11_device_create_shader_resource_view_default(
			global.__id3d11_device,
			_texture2d_result.handle);
		var _srv_roundtrip = id3d11_shader_resource_view_get_desc(_srv_result.handle);
		var _srv_resource = id3d11_view_get_resource(_srv_result.handle);
		var _srv_kind_ok =
			id3d11_handle_get_kind(_srv_result.handle) == ID3D11HandleKind.ShaderResourceView;

		var _rtv_desc = new ID3D11RenderTargetViewDesc();
		_rtv_desc.format = 28;
		_rtv_desc.viewDimension = ID3D11RenderTargetViewDimension.Texture2D;
		_rtv_desc.mipSlice = 0;
		var _rtv_result = id3d11_device_create_render_target_view(
			global.__id3d11_device,
			_texture2d_result.handle,
			_rtv_desc);
		var _rtv_default_result = id3d11_device_create_render_target_view_default(
			global.__id3d11_device,
			_texture2d_result.handle);
		var _rtv_roundtrip = id3d11_render_target_view_get_desc(_rtv_result.handle);
		var _rtv_resource = id3d11_view_get_resource(_rtv_result.handle);
		var _rtv_kind_ok =
			id3d11_handle_get_kind(_rtv_result.handle) == ID3D11HandleKind.RenderTargetView;

		var _uav_desc = new ID3D11UnorderedAccessViewDesc();
		_uav_desc.format = 28;
		_uav_desc.viewDimension = ID3D11UnorderedAccessViewDimension.Texture2D;
		_uav_desc.mipSlice = 0;
		var _uav_result = id3d11_device_create_unordered_access_view(
			global.__id3d11_device,
			_texture2d_result.handle,
			_uav_desc);
		var _uav_default_result = id3d11_device_create_unordered_access_view_default(
			global.__id3d11_device,
			_texture2d_result.handle);
		var _uav_roundtrip = id3d11_unordered_access_view_get_desc(_uav_result.handle);
		var _uav_resource = id3d11_view_get_resource(_uav_result.handle);
		var _uav_kind_ok =
			id3d11_handle_get_kind(_uav_result.handle) == ID3D11HandleKind.UnorderedAccessView;

		var _depth_texture_desc = new ID3D11Texture2DDesc();
		_depth_texture_desc.width = 2;
		_depth_texture_desc.height = 2;
		_depth_texture_desc.mipLevels = 1;
		_depth_texture_desc.arraySize = 1;
		_depth_texture_desc.format = 45;
		_depth_texture_desc.sampleCount = 1;
		_depth_texture_desc.sampleQuality = 0;
		_depth_texture_desc.usage = ID3D11Usage.Default;
		_depth_texture_desc.bindFlags = ID3D11BindFlag.DepthStencil;
		_depth_texture_desc.cpuAccessFlags = 0;
		_depth_texture_desc.miscFlags = 0;
		var _depth_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_depth_texture_desc);
		var _dsv_desc = new ID3D11DepthStencilViewDesc();
		_dsv_desc.format = 45;
		_dsv_desc.viewDimension = ID3D11DepthStencilViewDimension.Texture2D;
		_dsv_desc.flags = 0;
		_dsv_desc.mipSlice = 0;
		var _dsv_result = id3d11_device_create_depth_stencil_view(
			global.__id3d11_device,
			_depth_texture_result.handle,
			_dsv_desc);
		var _dsv_default_result = id3d11_device_create_depth_stencil_view_default(
			global.__id3d11_device,
			_depth_texture_result.handle);
		var _dsv_roundtrip = id3d11_depth_stencil_view_get_desc(_dsv_result.handle);
		var _dsv_resource = id3d11_view_get_resource(_dsv_result.handle);
		var _dsv_kind_ok =
			id3d11_handle_get_kind(_dsv_result.handle) == ID3D11HandleKind.DepthStencilView;

		_texture2d_subresource.dataSize = 17;
		var _texture2d_bounds_result = id3d11_device_create_texture2d_with_data(
			global.__id3d11_device,
			_texture2d_desc,
			[_texture2d_subresource],
			_texture2d_data);

		var _srv_release_ok = id3d11_handle_release(_srv_result.handle);
		var _srv_default_release_ok = _srv_default_result.handle == _srv_result.handle
			? _srv_release_ok
			: id3d11_handle_release(_srv_default_result.handle);
		var _rtv_release_ok = id3d11_handle_release(_rtv_result.handle);
		var _rtv_default_release_ok = _rtv_default_result.handle == _rtv_result.handle
			? _rtv_release_ok
			: id3d11_handle_release(_rtv_default_result.handle);
		var _uav_release_ok = id3d11_handle_release(_uav_result.handle);
		var _uav_default_release_ok = _uav_default_result.handle == _uav_result.handle
			? _uav_release_ok
			: id3d11_handle_release(_uav_default_result.handle);
		var _dsv_release_ok = id3d11_handle_release(_dsv_result.handle);
		var _dsv_default_release_ok = _dsv_default_result.handle == _dsv_result.handle
			? _dsv_release_ok
			: id3d11_handle_release(_dsv_default_result.handle);
		var _depth_texture_release_ok = id3d11_handle_release(_depth_texture_result.handle);
		var _texture2d_release_ok = id3d11_handle_release(_texture2d_result.handle);
		var _texture2d_stale_rejected = !id3d11_handle_is_valid(_texture2d_result.handle);
		buffer_delete(_texture2d_data);

		var _texture3d_desc = new ID3D11Texture3DDesc();
		_texture3d_desc.width = 2;
		_texture3d_desc.height = 2;
		_texture3d_desc.depth = 2;
		_texture3d_desc.mipLevels = 1;
		_texture3d_desc.format = 28;
		_texture3d_desc.usage = ID3D11Usage.Default;
		_texture3d_desc.bindFlags = ID3D11BindFlag.ShaderResource;
		_texture3d_desc.cpuAccessFlags = 0;
		_texture3d_desc.miscFlags = 0;
		var _texture3d_result = id3d11_device_create_texture3d(
			global.__id3d11_device,
			_texture3d_desc);
		var _texture3d_roundtrip = id3d11_texture3d_get_desc(_texture3d_result.handle);
		var _texture3d_dimension = id3d11_resource_get_dimension(_texture3d_result.handle);
		var _texture3d_release_ok = id3d11_handle_release(_texture3d_result.handle);
		var _texture3d_stale_rejected = !id3d11_handle_is_valid(_texture3d_result.handle);

		var _shader_bytecode = buffer_create(65536, buffer_fixed, 1);
		var _shader_errors = buffer_create(8192, buffer_fixed, 1);
		var _compile_flags = 2048;
		var _class_linkage_result = id3d11_device_create_class_linkage(global.__id3d11_device);

		var _vs_source =
			"float4 main(float4 position : POSITION) : SV_Position { return position; }";
		var _vs_compile = id3d11_compile_shader(
			_vs_source,
			"id3d11_smoke_vs",
			"main",
			"vs_5_0",
			_compile_flags,
			0,
			_shader_bytecode,
			_shader_errors);
		var _vs_result = id3d11_device_create_vertex_shader(
			global.__id3d11_device,
			_shader_bytecode,
			_vs_compile.bytecodeSize,
			0);
		var _input_element = new ID3D11InputElementDesc();
		_input_element.semanticName = "POSITION";
		_input_element.semanticIndex = 0;
		_input_element.format = 2;
		_input_element.inputSlot = 0;
		_input_element.alignedByteOffset = 0;
		_input_element.inputSlotClass = ID3D11InputClassification.PerVertexData;
		_input_element.instanceDataStepRate = 0;
		var _input_layout_result = id3d11_device_create_input_layout(
			global.__id3d11_device,
			[_input_element],
			_shader_bytecode,
			_vs_compile.bytecodeSize);
		var _invalid_bytecode_result = id3d11_device_create_vertex_shader(
			global.__id3d11_device,
			_shader_bytecode,
			buffer_get_size(_shader_bytecode) + 1,
			0);

		var _hs_source =
			"struct HSControlPoint { float4 position : POSITION; }; "
			+ "struct HSConstantData { float edges[3] : SV_TessFactor; float inside : SV_InsideTessFactor; }; "
			+ "HSConstantData patchConstants(InputPatch<HSControlPoint, 3> patch, uint patchId : SV_PrimitiveID) "
			+ "{ HSConstantData output; output.edges[0] = 1.0; output.edges[1] = 1.0; "
			+ "output.edges[2] = 1.0; output.inside = 1.0; return output; } "
			+ "[domain(\"tri\")] [partitioning(\"integer\")] [outputtopology(\"triangle_cw\")] "
			+ "[outputcontrolpoints(3)] [patchconstantfunc(\"patchConstants\")] "
			+ "HSControlPoint main(InputPatch<HSControlPoint, 3> patch, "
			+ "uint pointId : SV_OutputControlPointID, uint patchId : SV_PrimitiveID) "
			+ "{ return patch[pointId]; }";
		var _hs_compile = id3d11_compile_shader(
			_hs_source,
			"id3d11_smoke_hs",
			"main",
			"hs_5_0",
			_compile_flags,
			0,
			_shader_bytecode,
			_shader_errors);
		var _hs_result = id3d11_device_create_hull_shader(
			global.__id3d11_device,
			_shader_bytecode,
			_hs_compile.bytecodeSize,
			0);

		var _ds_source =
			"struct HSControlPoint { float4 position : POSITION; }; "
			+ "struct HSConstantData { float edges[3] : SV_TessFactor; float inside : SV_InsideTessFactor; }; "
			+ "[domain(\"tri\")] float4 main(HSConstantData constants, "
			+ "float3 barycentric : SV_DomainLocation, const OutputPatch<HSControlPoint, 3> patch) : SV_Position "
			+ "{ return patch[0].position * barycentric.x + patch[1].position * barycentric.y "
			+ "+ patch[2].position * barycentric.z; }";
		var _ds_compile = id3d11_compile_shader(
			_ds_source,
			"id3d11_smoke_ds",
			"main",
			"ds_5_0",
			_compile_flags,
			0,
			_shader_bytecode,
			_shader_errors);
		var _ds_result = id3d11_device_create_domain_shader(
			global.__id3d11_device,
			_shader_bytecode,
			_ds_compile.bytecodeSize,
			0);

		var _gs_source =
			"struct GSPoint { float4 position : SV_Position; }; "
			+ "[maxvertexcount(1)] void main(point GSPoint input[1], inout PointStream<GSPoint> output) "
			+ "{ output.Append(input[0]); }";
		var _gs_compile = id3d11_compile_shader(
			_gs_source,
			"id3d11_smoke_gs",
			"main",
			"gs_5_0",
			_compile_flags,
			0,
			_shader_bytecode,
			_shader_errors);
		var _gs_result = id3d11_device_create_geometry_shader(
			global.__id3d11_device,
			_shader_bytecode,
			_gs_compile.bytecodeSize,
			0);
		var _so_entry = new ID3D11StreamOutputDeclarationEntry();
		_so_entry.semanticName = "SV_Position";
		_so_entry.stream = 0;
		_so_entry.semanticIndex = 0;
		_so_entry.startComponent = 0;
		_so_entry.componentCount = 4;
		_so_entry.outputSlot = 0;
		var _gs_so_result = id3d11_device_create_geometry_shader_with_stream_output(
			global.__id3d11_device,
			_shader_bytecode,
			_gs_compile.bytecodeSize,
			[_so_entry],
			[16],
			0,
			0);

		var _ps_source =
			"float4 main() : SV_Target { return float4(1.0, 0.0, 1.0, 1.0); }";
		var _ps_compile = id3d11_compile_shader(
			_ps_source,
			"id3d11_smoke_ps",
			"main",
			"ps_5_0",
			_compile_flags,
			0,
			_shader_bytecode,
			_shader_errors);
		var _ps_result = id3d11_device_create_pixel_shader(
			global.__id3d11_device,
			_shader_bytecode,
			_ps_compile.bytecodeSize,
			0);

		var _cs_source =
			"[numthreads(1, 1, 1)] void main(uint3 threadId : SV_DispatchThreadID) {}";
		var _cs_compile = id3d11_compile_shader(
			_cs_source,
			"id3d11_smoke_cs",
			"main",
			"cs_5_0",
			_compile_flags,
			0,
			_shader_bytecode,
			_shader_errors);
		var _cs_result = id3d11_device_create_compute_shader(
			global.__id3d11_device,
			_shader_bytecode,
			_cs_compile.bytecodeSize,
			0);

		var _shader_kinds_ok =
			id3d11_handle_get_kind(_vs_result.handle) == ID3D11HandleKind.VertexShader &&
			id3d11_handle_get_kind(_hs_result.handle) == ID3D11HandleKind.HullShader &&
			id3d11_handle_get_kind(_ds_result.handle) == ID3D11HandleKind.DomainShader &&
			id3d11_handle_get_kind(_gs_result.handle) == ID3D11HandleKind.GeometryShader &&
			id3d11_handle_get_kind(_gs_so_result.handle) == ID3D11HandleKind.GeometryShader &&
			id3d11_handle_get_kind(_ps_result.handle) == ID3D11HandleKind.PixelShader &&
			id3d11_handle_get_kind(_cs_result.handle) == ID3D11HandleKind.ComputeShader &&
			id3d11_handle_get_kind(_input_layout_result.handle) == ID3D11HandleKind.InputLayout &&
			id3d11_handle_get_kind(_class_linkage_result.handle) == ID3D11HandleKind.ClassLinkage;
		var _shader_parent_device = id3d11_device_child_get_device(_vs_result.handle);
		var _test_shader_binding = function(_set_shader, _get_shader, _shader)
		{
			var _previous = _get_shader(global.__id3d11_context);
			if (!is_array(_previous.classInstances))
			{
				return false;
			}

			var _shader_set = _set_shader(global.__id3d11_context, _shader, []);
			var _bound = _get_shader(global.__id3d11_context);
			var _null_set = _set_shader(global.__id3d11_context, 0, []);
			var _null_binding = _get_shader(global.__id3d11_context);
			var _restored = _set_shader(
				global.__id3d11_context,
				_previous.shader,
				_previous.classInstances);

			var _previous_shader_release_ok =
				_previous.shader == 0 ||
				_previous.shader == _shader ||
				id3d11_handle_release(_previous.shader);
			var _previous_instances_release_ok = true;
			var _released_instances = [];
			for (var _instance_index = 0;
				_instance_index < array_length(_previous.classInstances);
				++_instance_index)
			{
				var _instance = _previous.classInstances[_instance_index];
				var _already_released = false;
				for (var _released_index = 0;
					_released_index < array_length(_released_instances);
					++_released_index)
				{
					_already_released = _already_released ||
						_released_instances[_released_index] == _instance;
				}
				if (_instance == 0)
				{
					_previous_instances_release_ok = false;
				}
				else if (!_already_released)
				{
					_previous_instances_release_ok =
						id3d11_handle_release(_instance) &&
						_previous_instances_release_ok;
					array_push(_released_instances, _instance);
				}
			}

			return
				_shader_set &&
				_bound.shader == _shader &&
				array_length(_bound.classInstances) == 0 &&
				_null_set &&
				_null_binding.shader == 0 &&
				array_length(_null_binding.classInstances) == 0 &&
				_restored &&
				_previous_shader_release_ok &&
				_previous_instances_release_ok;
		};
		var _vs_shader_binding_ok = _test_shader_binding(
			id3d11_device_context_vs_set_shader,
			id3d11_device_context_vs_get_shader,
			_vs_result.handle);
		var _hs_shader_binding_ok = _test_shader_binding(
			id3d11_device_context_hs_set_shader,
			id3d11_device_context_hs_get_shader,
			_hs_result.handle);
		var _ds_shader_binding_ok = _test_shader_binding(
			id3d11_device_context_ds_set_shader,
			id3d11_device_context_ds_get_shader,
			_ds_result.handle);
		var _gs_shader_binding_ok = _test_shader_binding(
			id3d11_device_context_gs_set_shader,
			id3d11_device_context_gs_get_shader,
			_gs_result.handle);
		var _ps_shader_binding_ok = _test_shader_binding(
			id3d11_device_context_ps_set_shader,
			id3d11_device_context_ps_get_shader,
			_ps_result.handle);
		var _cs_shader_binding_ok = _test_shader_binding(
			id3d11_device_context_cs_set_shader,
			id3d11_device_context_cs_get_shader,
			_cs_result.handle);
		var _shader_binding_wrong_type_rejected =
			!id3d11_device_context_vs_set_shader(
				global.__id3d11_context,
				_ps_result.handle,
				[]);
		var _shader_binding_null_instance_rejected =
			!id3d11_device_context_vs_set_shader(
				global.__id3d11_context,
				_vs_result.handle,
				[0]);
		var _shader_binding_too_many_instances_rejected =
			!id3d11_device_context_vs_set_shader(
				global.__id3d11_context,
				_vs_result.handle,
				array_create(257, 0));
		var _shader_bindings_ok =
			_vs_shader_binding_ok &&
			_hs_shader_binding_ok &&
			_ds_shader_binding_ok &&
			_gs_shader_binding_ok &&
			_ps_shader_binding_ok &&
			_cs_shader_binding_ok &&
			_shader_binding_wrong_type_rejected &&
			_shader_binding_null_instance_rejected &&
			_shader_binding_too_many_instances_rejected;

		var _dynamic_ps_source =
			"interface IColor { float4 GetColor(); }; "
			+ "class ColorClass : IColor { float4 color; "
			+ "float4 GetColor() { return color; } }; "
			+ "cbuffer DynamicData : register(b0) { ColorClass storedColor; }; "
			+ "IColor activeColor; "
			+ "float4 main() : SV_Target { return activeColor.GetColor(); }";
		var _dynamic_ps_compile = id3d11_compile_shader(
			_dynamic_ps_source,
			"id3d11_smoke_dynamic_ps",
			"main",
			"ps_5_0",
			_compile_flags,
			0,
			_shader_bytecode,
			_shader_errors);
		var _dynamic_ps_result = id3d11_device_create_pixel_shader(
			global.__id3d11_device,
			_shader_bytecode,
			_dynamic_ps_compile.bytecodeSize,
			_class_linkage_result.handle);
		var _got_class_instance_result = id3d11_class_linkage_get_class_instance(
			_class_linkage_result.handle,
			"storedColor",
			0);
		var _created_class_instance_result = id3d11_class_linkage_create_class_instance(
			_class_linkage_result.handle,
			"ColorClass",
			0,
			0,
			0,
			0);
		var _got_class_instance_kind = id3d11_handle_get_kind(
			_got_class_instance_result.handle);
		var _created_class_instance_kind = id3d11_handle_get_kind(
			_created_class_instance_result.handle);
		var _got_class_instance_desc = id3d11_class_instance_get_desc(
			_got_class_instance_result.handle);
		var _created_class_instance_desc = id3d11_class_instance_get_desc(
			_created_class_instance_result.handle);
		var _got_class_instance_name = id3d11_class_instance_get_instance_name(
			_got_class_instance_result.handle);
		var _got_class_type_name = id3d11_class_instance_get_type_name(
			_got_class_instance_result.handle);
		var _created_class_instance_name = id3d11_class_instance_get_instance_name(
			_created_class_instance_result.handle);
		var _created_class_type_name = id3d11_class_instance_get_type_name(
			_created_class_instance_result.handle);
		var _got_class_linkage = id3d11_class_instance_get_class_linkage(
			_got_class_instance_result.handle);
		var _created_class_linkage = id3d11_class_instance_get_class_linkage(
			_created_class_instance_result.handle);
		var _invalid_gotten_class_instance = id3d11_class_linkage_get_class_instance(
			_class_linkage_result.handle,
			"",
			0);
		var _invalid_created_class_instance = id3d11_class_linkage_create_class_instance(
			_class_linkage_result.handle,
			"",
			0,
			0,
			0,
			0);
		var _dynamic_ps_release_ok = id3d11_handle_release(_dynamic_ps_result.handle);
		var _got_class_instance_release_ok = id3d11_handle_release(
			_got_class_instance_result.handle);
		var _created_class_instance_release_ok =
			_created_class_instance_result.handle == _got_class_instance_result.handle
			? _got_class_instance_release_ok
			: id3d11_handle_release(_created_class_instance_result.handle);
		var _class_linkage_methods_ok =
			_dynamic_ps_compile.hresult == 0 &&
			_dynamic_ps_compile.bytecodeSize > 0 &&
			_dynamic_ps_result.hresult == 0 &&
			_got_class_instance_result.hresult == 0 &&
			_created_class_instance_result.hresult == 0 &&
			_got_class_instance_kind == ID3D11HandleKind.ClassInstance &&
			_created_class_instance_kind == ID3D11HandleKind.ClassInstance &&
			!_got_class_instance_desc.created &&
			_created_class_instance_desc.created &&
			_got_class_instance_name == "storedColor" &&
			_got_class_type_name == "" &&
			_created_class_instance_name == "" &&
			_created_class_type_name == "ColorClass" &&
			_got_class_linkage == _class_linkage_result.handle &&
			_created_class_linkage == _class_linkage_result.handle &&
			_invalid_gotten_class_instance.hresult != 0 &&
			_invalid_gotten_class_instance.handle == 0 &&
			_invalid_created_class_instance.hresult != 0 &&
			_invalid_created_class_instance.handle == 0 &&
			_dynamic_ps_release_ok &&
			_got_class_instance_release_ok &&
			_created_class_instance_release_ok;
		var _vs_release_ok = id3d11_handle_release(_vs_result.handle);
		var _hs_release_ok = id3d11_handle_release(_hs_result.handle);
		var _ds_release_ok = id3d11_handle_release(_ds_result.handle);
		var _gs_release_ok = id3d11_handle_release(_gs_result.handle);
		var _gs_so_release_ok = id3d11_handle_release(_gs_so_result.handle);
		var _ps_release_ok = id3d11_handle_release(_ps_result.handle);
		var _cs_release_ok = id3d11_handle_release(_cs_result.handle);
		var _class_linkage_release_ok = id3d11_handle_release(
			_class_linkage_result.handle);
		var _shader_releases_ok =
			_vs_release_ok &&
			_hs_release_ok &&
			_ds_release_ok &&
			_gs_release_ok &&
			_gs_so_release_ok &&
			_ps_release_ok &&
			_cs_release_ok &&
			_class_linkage_release_ok;
		global.__id3d11_shader_smoke_ok =
			_vs_compile.hresult == 0 && _vs_compile.bytecodeSize > 0 && _vs_result.hresult == 0 &&
			_hs_compile.hresult == 0 && _hs_compile.bytecodeSize > 0 && _hs_result.hresult == 0 &&
			_ds_compile.hresult == 0 && _ds_compile.bytecodeSize > 0 && _ds_result.hresult == 0 &&
			_gs_compile.hresult == 0 && _gs_compile.bytecodeSize > 0 && _gs_result.hresult == 0 &&
			_gs_so_result.hresult == 0 &&
			_ps_compile.hresult == 0 && _ps_compile.bytecodeSize > 0 && _ps_result.hresult == 0 &&
			_cs_compile.hresult == 0 && _cs_compile.bytecodeSize > 0 && _cs_result.hresult == 0 &&
			_input_layout_result.hresult == 0 &&
			_class_linkage_result.hresult == 0 &&
			_invalid_bytecode_result.hresult != 0 && _invalid_bytecode_result.handle == 0 &&
			_shader_kinds_ok &&
			_shader_parent_device == global.__id3d11_device &&
			_shader_bindings_ok &&
			_class_linkage_methods_ok &&
			_shader_releases_ok;
		buffer_delete(_shader_errors);
		buffer_delete(_shader_bytecode);

		var _sampler_desc = new ID3D11SamplerDesc();
		_sampler_desc.filter = ID3D11Filter.Anisotropic;
		_sampler_desc.addressU = ID3D11TextureAddressMode.Clamp;
		_sampler_desc.addressV = ID3D11TextureAddressMode.Clamp;
		_sampler_desc.addressW = ID3D11TextureAddressMode.Clamp;
		_sampler_desc.mipLodBias = 0.0;
		_sampler_desc.maxAnisotropy = 4;
		_sampler_desc.comparisonFunc = ID3D11ComparisonFunc.Never;
		_sampler_desc.borderColorR = 0.0;
		_sampler_desc.borderColorG = 0.0;
		_sampler_desc.borderColorB = 0.0;
		_sampler_desc.borderColorA = 0.0;
		_sampler_desc.minLod = 0.0;
		_sampler_desc.maxLod = 1000.0;
		var _sampler_result = id3d11_device_create_sampler_state(
			global.__id3d11_device,
			_sampler_desc);
		var _sampler_roundtrip = id3d11_sampler_state_get_desc(_sampler_result.handle);

		var _rasterizer_desc = new ID3D11RasterizerDesc();
		_rasterizer_desc.fillMode = ID3D11FillMode.Solid;
		_rasterizer_desc.cullMode = ID3D11CullMode.Back;
		_rasterizer_desc.frontCounterClockwise = false;
		_rasterizer_desc.depthBias = 0;
		_rasterizer_desc.depthBiasClamp = 0.0;
		_rasterizer_desc.slopeScaledDepthBias = 0.0;
		_rasterizer_desc.depthClipEnable = true;
		_rasterizer_desc.scissorEnable = false;
		_rasterizer_desc.multisampleEnable = false;
		_rasterizer_desc.antialiasedLineEnable = false;
		var _rasterizer_result = id3d11_device_create_rasterizer_state(
			global.__id3d11_device,
			_rasterizer_desc);
		var _rasterizer_roundtrip = id3d11_rasterizer_state_get_desc(
			_rasterizer_result.handle);

		var _blend_targets = array_create(8);
		for (var _blend_index = 0; _blend_index < 8; ++_blend_index)
		{
			var _blend_target = new ID3D11RenderTargetBlendDesc();
			_blend_target.blendEnable = false;
			_blend_target.srcBlend = ID3D11Blend.One;
			_blend_target.destBlend = ID3D11Blend.Zero;
			_blend_target.blendOp = ID3D11BlendOp.Add;
			_blend_target.srcBlendAlpha = ID3D11Blend.One;
			_blend_target.destBlendAlpha = ID3D11Blend.Zero;
			_blend_target.blendOpAlpha = ID3D11BlendOp.Add;
			_blend_target.renderTargetWriteMask = ID3D11ColorWriteEnable.All;
			_blend_targets[_blend_index] = _blend_target;
		}
		var _blend_desc = new ID3D11BlendDesc();
		_blend_desc.alphaToCoverageEnable = false;
		_blend_desc.independentBlendEnable = false;
		_blend_desc.renderTargets = _blend_targets;
		var _blend_result = id3d11_device_create_blend_state(
			global.__id3d11_device,
			_blend_desc);
		var _blend_roundtrip = id3d11_blend_state_get_desc(_blend_result.handle);
		var _invalid_blend_desc = new ID3D11BlendDesc();
		var _invalid_blend_result = id3d11_device_create_blend_state(
			global.__id3d11_device,
			_invalid_blend_desc);

		var _depth_stencil_desc = new ID3D11DepthStencilDesc();
		_depth_stencil_desc.depthEnable = true;
		_depth_stencil_desc.depthWriteMask = ID3D11DepthWriteMask.All;
		_depth_stencil_desc.depthFunc = ID3D11ComparisonFunc.Less;
		_depth_stencil_desc.stencilEnable = false;
		_depth_stencil_desc.stencilReadMask = 255;
		_depth_stencil_desc.stencilWriteMask = 255;
		_depth_stencil_desc.frontFace.stencilFailOp = ID3D11StencilOp.Keep;
		_depth_stencil_desc.frontFace.stencilDepthFailOp = ID3D11StencilOp.Keep;
		_depth_stencil_desc.frontFace.stencilPassOp = ID3D11StencilOp.Keep;
		_depth_stencil_desc.frontFace.stencilFunc = ID3D11ComparisonFunc.Always;
		_depth_stencil_desc.backFace.stencilFailOp = ID3D11StencilOp.Keep;
		_depth_stencil_desc.backFace.stencilDepthFailOp = ID3D11StencilOp.Keep;
		_depth_stencil_desc.backFace.stencilPassOp = ID3D11StencilOp.Keep;
		_depth_stencil_desc.backFace.stencilFunc = ID3D11ComparisonFunc.Always;
		var _depth_stencil_result = id3d11_device_create_depth_stencil_state(
			global.__id3d11_device,
			_depth_stencil_desc);
		var _depth_stencil_roundtrip = id3d11_depth_stencil_state_get_desc(
			_depth_stencil_result.handle);

		var _previous_input_layout = id3d11_device_context_ia_get_input_layout(
			global.__id3d11_context);
		var _previous_topology = id3d11_device_context_ia_get_primitive_topology(
			global.__id3d11_context);
		var _previous_rasterizer = id3d11_device_context_rs_get_state(
			global.__id3d11_context);
		var _previous_blend = id3d11_device_context_om_get_blend_state(
			global.__id3d11_context);
		var _previous_depth_stencil = id3d11_device_context_om_get_depth_stencil_state(
			global.__id3d11_context);

		var _pipeline_input_layout_set = id3d11_device_context_ia_set_input_layout(
			global.__id3d11_context,
			_input_layout_result.handle);
		var _pipeline_topology_set = id3d11_device_context_ia_set_primitive_topology(
			global.__id3d11_context,
			ID3D11PrimitiveTopology.TriangleList);
		var _pipeline_rasterizer_set = id3d11_device_context_rs_set_state(
			global.__id3d11_context,
			_rasterizer_result.handle);
		var _pipeline_blend_factor = [0.25, 0.5, 0.75, 1.0];
		var _pipeline_blend_set = id3d11_device_context_om_set_blend_state(
			global.__id3d11_context,
			_blend_result.handle,
			_pipeline_blend_factor,
			252645135);
		var _pipeline_depth_stencil_set = id3d11_device_context_om_set_depth_stencil_state(
			global.__id3d11_context,
			_depth_stencil_result.handle,
			7);

		var _bound_input_layout = id3d11_device_context_ia_get_input_layout(
			global.__id3d11_context);
		var _bound_topology = id3d11_device_context_ia_get_primitive_topology(
			global.__id3d11_context);
		var _bound_rasterizer = id3d11_device_context_rs_get_state(
			global.__id3d11_context);
		var _bound_blend = id3d11_device_context_om_get_blend_state(
			global.__id3d11_context);
		var _bound_depth_stencil = id3d11_device_context_om_get_depth_stencil_state(
			global.__id3d11_context);
		var _pipeline_invalid_topology_rejected = !id3d11_device_context_ia_set_primitive_topology(
			global.__id3d11_context,
			6);
		var _pipeline_invalid_blend_rejected = !id3d11_device_context_om_set_blend_state(
			global.__id3d11_context,
			_blend_result.handle,
			[1.0, 1.0, 1.0],
			4294967295);
		var _pipeline_invalid_stencil_rejected = !id3d11_device_context_om_set_depth_stencil_state(
			global.__id3d11_context,
			_depth_stencil_result.handle,
			256);

		var _pipeline_input_layout_restored = id3d11_device_context_ia_set_input_layout(
			global.__id3d11_context,
			_previous_input_layout);
		var _pipeline_topology_restored = id3d11_device_context_ia_set_primitive_topology(
			global.__id3d11_context,
			_previous_topology);
		var _pipeline_rasterizer_restored = id3d11_device_context_rs_set_state(
			global.__id3d11_context,
			_previous_rasterizer);
		var _pipeline_blend_restored = id3d11_device_context_om_set_blend_state(
			global.__id3d11_context,
			_previous_blend.state,
			_previous_blend.blendFactor,
			_previous_blend.sampleMask);
		var _pipeline_depth_stencil_restored = id3d11_device_context_om_set_depth_stencil_state(
			global.__id3d11_context,
			_previous_depth_stencil.state,
			_previous_depth_stencil.stencilRef);
		var _previous_input_layout_release_ok =
			_previous_input_layout == 0 ||
			_previous_input_layout == _input_layout_result.handle ||
			id3d11_handle_release(_previous_input_layout);
		var _previous_rasterizer_release_ok =
			_previous_rasterizer == 0 ||
			_previous_rasterizer == _rasterizer_result.handle ||
			id3d11_handle_release(_previous_rasterizer);
		var _previous_blend_release_ok =
			_previous_blend.state == 0 ||
			_previous_blend.state == _blend_result.handle ||
			id3d11_handle_release(_previous_blend.state);
		var _previous_depth_stencil_release_ok =
			_previous_depth_stencil.state == 0 ||
			_previous_depth_stencil.state == _depth_stencil_result.handle ||
			id3d11_handle_release(_previous_depth_stencil.state);
		var _fixed_pipeline_smoke_ok =
			_pipeline_input_layout_set &&
			_pipeline_topology_set &&
			_pipeline_rasterizer_set &&
			_pipeline_blend_set &&
			_pipeline_depth_stencil_set &&
			_bound_input_layout == _input_layout_result.handle &&
			_bound_topology == ID3D11PrimitiveTopology.TriangleList &&
			_bound_rasterizer == _rasterizer_result.handle &&
			_bound_blend.state == _blend_result.handle &&
			array_length(_bound_blend.blendFactor) == 4 &&
			_bound_blend.blendFactor[0] == 0.25 &&
			_bound_blend.blendFactor[3] == 1.0 &&
			_bound_blend.sampleMask == 252645135 &&
			_bound_depth_stencil.state == _depth_stencil_result.handle &&
			_bound_depth_stencil.stencilRef == 7 &&
			_pipeline_invalid_topology_rejected &&
			_pipeline_invalid_blend_rejected &&
			_pipeline_invalid_stencil_rejected &&
			_pipeline_input_layout_restored &&
			_pipeline_topology_restored &&
			_pipeline_rasterizer_restored &&
			_pipeline_blend_restored &&
			_pipeline_depth_stencil_restored &&
			_previous_input_layout_release_ok &&
			_previous_rasterizer_release_ok &&
			_previous_blend_release_ok &&
			_previous_depth_stencil_release_ok;

		var _pipeline_vertex_buffer_desc = new ID3D11BufferDesc();
		_pipeline_vertex_buffer_desc.byteWidth = 16;
		_pipeline_vertex_buffer_desc.usage = ID3D11Usage.Default;
		_pipeline_vertex_buffer_desc.bindFlags = ID3D11BindFlag.VertexBuffer;
		var _pipeline_vertex_buffer_result = id3d11_device_create_buffer(
			global.__id3d11_device,
			_pipeline_vertex_buffer_desc);
		var _pipeline_index_buffer_desc = new ID3D11BufferDesc();
		_pipeline_index_buffer_desc.byteWidth = 16;
		_pipeline_index_buffer_desc.usage = ID3D11Usage.Default;
		_pipeline_index_buffer_desc.bindFlags = ID3D11BindFlag.IndexBuffer;
		var _pipeline_index_buffer_result = id3d11_device_create_buffer(
			global.__id3d11_device,
			_pipeline_index_buffer_desc);

		var _previous_vertex_buffers = id3d11_device_context_ia_get_vertex_buffers(
			global.__id3d11_context,
			0,
			1);
		var _previous_index_buffer = id3d11_device_context_ia_get_index_buffer(
			global.__id3d11_context);
		var _previous_viewports = id3d11_device_context_rs_get_viewports(
			global.__id3d11_context);
		var _previous_scissor_rects = id3d11_device_context_rs_get_scissor_rects(
			global.__id3d11_context);

		var _vertex_binding = new ID3D11VertexBufferBinding();
		_vertex_binding.buffer = _pipeline_vertex_buffer_result.handle;
		_vertex_binding.stride = 4;
		_vertex_binding.offset = 0;
		var _pipeline_vertex_buffers_set = id3d11_device_context_ia_set_vertex_buffers(
			global.__id3d11_context,
			0,
			[_vertex_binding]);
		var _pipeline_index_buffer_set = id3d11_device_context_ia_set_index_buffer(
			global.__id3d11_context,
			_pipeline_index_buffer_result.handle,
			42,
			0);
		var _viewport = new ID3D11Viewport();
		_viewport.topLeftX = 0.0;
		_viewport.topLeftY = 0.0;
		_viewport.width = 64.0;
		_viewport.height = 64.0;
		_viewport.minDepth = 0.0;
		_viewport.maxDepth = 1.0;
		var _pipeline_viewports_set = id3d11_device_context_rs_set_viewports(
			global.__id3d11_context,
			[_viewport]);
		var _scissor_rect = new ID3D11Rect();
		_scissor_rect.left = 0;
		_scissor_rect.top = 0;
		_scissor_rect.right = 64;
		_scissor_rect.bottom = 64;
		var _pipeline_scissor_rects_set = id3d11_device_context_rs_set_scissor_rects(
			global.__id3d11_context,
			[_scissor_rect]);

		var _bound_vertex_buffers = id3d11_device_context_ia_get_vertex_buffers(
			global.__id3d11_context,
			0,
			1);
		var _bound_index_buffer = id3d11_device_context_ia_get_index_buffer(
			global.__id3d11_context);
		var _bound_viewports = id3d11_device_context_rs_get_viewports(
			global.__id3d11_context);
		var _bound_scissor_rects = id3d11_device_context_rs_get_scissor_rects(
			global.__id3d11_context);
		var _pipeline_invalid_vertex_slot_rejected = !id3d11_device_context_ia_set_vertex_buffers(
			global.__id3d11_context,
			32,
			[_vertex_binding]);
		var _pipeline_invalid_index_format_rejected = !id3d11_device_context_ia_set_index_buffer(
			global.__id3d11_context,
			_pipeline_index_buffer_result.handle,
			28,
			0);
		var _invalid_viewport = new ID3D11Viewport();
		_invalid_viewport.width = 64.0;
		_invalid_viewport.height = 64.0;
		_invalid_viewport.minDepth = 1.0;
		_invalid_viewport.maxDepth = 0.0;
		var _pipeline_invalid_viewport_rejected = !id3d11_device_context_rs_set_viewports(
			global.__id3d11_context,
			[_invalid_viewport]);
		var _invalid_rect = new ID3D11Rect();
		_invalid_rect.left = 64;
		_invalid_rect.right = 0;
		var _pipeline_invalid_rect_rejected = !id3d11_device_context_rs_set_scissor_rects(
			global.__id3d11_context,
			[_invalid_rect]);

		var _pipeline_vertex_buffers_restored = id3d11_device_context_ia_set_vertex_buffers(
			global.__id3d11_context,
			0,
			_previous_vertex_buffers);
		var _pipeline_index_buffer_restored = id3d11_device_context_ia_set_index_buffer(
			global.__id3d11_context,
			_previous_index_buffer.buffer,
			_previous_index_buffer.format,
			_previous_index_buffer.offset);
		var _pipeline_viewports_restored = id3d11_device_context_rs_set_viewports(
			global.__id3d11_context,
			_previous_viewports);
		var _pipeline_scissor_rects_restored = id3d11_device_context_rs_set_scissor_rects(
			global.__id3d11_context,
			_previous_scissor_rects);
		var _previous_vertex_buffer_handle = _previous_vertex_buffers[0].buffer;
		var _previous_vertex_buffer_release_ok =
			_previous_vertex_buffer_handle == 0 ||
			_previous_vertex_buffer_handle == _pipeline_vertex_buffer_result.handle ||
			_previous_vertex_buffer_handle == _pipeline_index_buffer_result.handle ||
			id3d11_handle_release(_previous_vertex_buffer_handle);
		var _previous_index_buffer_release_ok =
			_previous_index_buffer.buffer == 0 ||
			_previous_index_buffer.buffer == _previous_vertex_buffer_handle ||
			_previous_index_buffer.buffer == _pipeline_vertex_buffer_result.handle ||
			_previous_index_buffer.buffer == _pipeline_index_buffer_result.handle ||
			id3d11_handle_release(_previous_index_buffer.buffer);
		var _pipeline_vertex_buffer_release_ok = id3d11_handle_release(
			_pipeline_vertex_buffer_result.handle);
		var _pipeline_index_buffer_release_ok = id3d11_handle_release(
			_pipeline_index_buffer_result.handle);
		var _pipeline_binding_smoke_ok =
			_pipeline_vertex_buffer_result.hresult == 0 &&
			_pipeline_index_buffer_result.hresult == 0 &&
			_pipeline_vertex_buffers_set &&
			_pipeline_index_buffer_set &&
			_pipeline_viewports_set &&
			_pipeline_scissor_rects_set &&
			array_length(_bound_vertex_buffers) == 1 &&
			_bound_vertex_buffers[0].buffer == _pipeline_vertex_buffer_result.handle &&
			_bound_vertex_buffers[0].stride == 4 &&
			_bound_vertex_buffers[0].offset == 0 &&
			_bound_index_buffer.buffer == _pipeline_index_buffer_result.handle &&
			_bound_index_buffer.format == 42 &&
			_bound_index_buffer.offset == 0 &&
			array_length(_bound_viewports) == 1 &&
			_bound_viewports[0].width == 64.0 &&
			_bound_viewports[0].maxDepth == 1.0 &&
			array_length(_bound_scissor_rects) == 1 &&
			_bound_scissor_rects[0].right == 64 &&
			_bound_scissor_rects[0].bottom == 64 &&
			_pipeline_invalid_vertex_slot_rejected &&
			_pipeline_invalid_index_format_rejected &&
			_pipeline_invalid_viewport_rejected &&
			_pipeline_invalid_rect_rejected &&
			_pipeline_vertex_buffers_restored &&
			_pipeline_index_buffer_restored &&
			_pipeline_viewports_restored &&
			_pipeline_scissor_rects_restored &&
			_previous_vertex_buffer_release_ok &&
			_previous_index_buffer_release_ok &&
			_pipeline_vertex_buffer_release_ok &&
			_pipeline_index_buffer_release_ok;

		var _om_texture_desc = new ID3D11Texture2DDesc();
		_om_texture_desc.width = 1;
		_om_texture_desc.height = 1;
		_om_texture_desc.mipLevels = 1;
		_om_texture_desc.arraySize = 1;
		_om_texture_desc.format = 28;
		_om_texture_desc.sampleCount = 1;
		_om_texture_desc.sampleQuality = 0;
		_om_texture_desc.usage = ID3D11Usage.Default;
		_om_texture_desc.bindFlags = ID3D11BindFlag.RenderTarget;
		var _om_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_om_texture_desc);
		var _om_rtv_result = id3d11_device_create_render_target_view_default(
			global.__id3d11_device,
			_om_texture_result.handle);
		var _om_depth_desc = new ID3D11Texture2DDesc();
		_om_depth_desc.width = 1;
		_om_depth_desc.height = 1;
		_om_depth_desc.mipLevels = 1;
		_om_depth_desc.arraySize = 1;
		_om_depth_desc.format = 45;
		_om_depth_desc.sampleCount = 1;
		_om_depth_desc.sampleQuality = 0;
		_om_depth_desc.usage = ID3D11Usage.Default;
		_om_depth_desc.bindFlags = ID3D11BindFlag.DepthStencil;
		var _om_depth_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_om_depth_desc);
		var _om_dsv_result = id3d11_device_create_depth_stencil_view_default(
			global.__id3d11_device,
			_om_depth_result.handle);
		var _previous_om_targets = id3d11_device_context_om_get_render_targets(
			global.__id3d11_context,
			1);
		var _om_targets_set = id3d11_device_context_om_set_render_targets(
			global.__id3d11_context,
			[_om_rtv_result.handle],
			_om_dsv_result.handle);
		var _bound_om_targets = id3d11_device_context_om_get_render_targets(
			global.__id3d11_context,
			1);
		var _om_count_rejected = array_length(
			id3d11_device_context_om_get_render_targets(
				global.__id3d11_context,
				9).renderTargetViews) == 0;
		var _om_targets_restored = id3d11_device_context_om_set_render_targets(
			global.__id3d11_context,
			_previous_om_targets.renderTargetViews,
			_previous_om_targets.depthStencilView);
		var _previous_om_rtv = array_length(_previous_om_targets.renderTargetViews) > 0
			? _previous_om_targets.renderTargetViews[0]
			: 0;
		var _previous_om_rtv_release_ok =
			_previous_om_rtv == 0 ||
			_previous_om_rtv == _om_rtv_result.handle ||
			id3d11_handle_release(_previous_om_rtv);
		var _previous_om_dsv_release_ok =
			_previous_om_targets.depthStencilView == 0 ||
			_previous_om_targets.depthStencilView == _om_dsv_result.handle ||
			id3d11_handle_release(_previous_om_targets.depthStencilView);
		var _om_rtv_release_ok = id3d11_handle_release(_om_rtv_result.handle);
		var _om_dsv_release_ok = id3d11_handle_release(_om_dsv_result.handle);
		var _om_texture_release_ok = id3d11_handle_release(_om_texture_result.handle);
		var _om_depth_release_ok = id3d11_handle_release(_om_depth_result.handle);

		var _so_buffer_desc = new ID3D11BufferDesc();
		_so_buffer_desc.byteWidth = 16;
		_so_buffer_desc.usage = ID3D11Usage.Default;
		_so_buffer_desc.bindFlags = ID3D11BindFlag.StreamOutput;
		var _so_buffer_result = id3d11_device_create_buffer(
			global.__id3d11_device,
			_so_buffer_desc);
		var _previous_so_targets = id3d11_device_context_so_get_targets(
			global.__id3d11_context,
			1);
		var _so_target = new ID3D11StreamOutputTarget();
		_so_target.buffer = _so_buffer_result.handle;
		_so_target.offset = 0;
		var _so_targets_set = id3d11_device_context_so_set_targets(
			global.__id3d11_context,
			[_so_target]);
		var _bound_so_targets = id3d11_device_context_so_get_targets(
			global.__id3d11_context,
			1);
		var _so_count_rejected = array_length(
			id3d11_device_context_so_get_targets(
				global.__id3d11_context,
				5)) == 0;
		var _so_restore_targets = [];
		if (array_length(_previous_so_targets) > 0 && _previous_so_targets[0] != 0)
		{
			var _restore_so = new ID3D11StreamOutputTarget();
			_restore_so.buffer = _previous_so_targets[0];
			_restore_so.offset = 0;
			array_push(_so_restore_targets, _restore_so);
		}
		var _so_targets_restored = id3d11_device_context_so_set_targets(
			global.__id3d11_context,
			_so_restore_targets);
		var _previous_so_release_ok =
			array_length(_previous_so_targets) == 0 ||
			_previous_so_targets[0] == 0 ||
			_previous_so_targets[0] == _so_buffer_result.handle ||
			id3d11_handle_release(_previous_so_targets[0]);
		var _so_buffer_release_ok = id3d11_handle_release(_so_buffer_result.handle);

		var _cs_uav_texture_desc = new ID3D11Texture2DDesc();
		_cs_uav_texture_desc.width = 1;
		_cs_uav_texture_desc.height = 1;
		_cs_uav_texture_desc.mipLevels = 1;
		_cs_uav_texture_desc.arraySize = 1;
		_cs_uav_texture_desc.format = 28;
		_cs_uav_texture_desc.sampleCount = 1;
		_cs_uav_texture_desc.sampleQuality = 0;
		_cs_uav_texture_desc.usage = ID3D11Usage.Default;
		_cs_uav_texture_desc.bindFlags = ID3D11BindFlag.UnorderedAccess;
		var _cs_uav_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_cs_uav_texture_desc);
		var _cs_uav_result = id3d11_device_create_unordered_access_view_default(
			global.__id3d11_device,
			_cs_uav_texture_result.handle);
		var _previous_cs_uavs = id3d11_device_context_cs_get_unordered_access_views(
			global.__id3d11_context,
			0,
			1);
		var _cs_uav_binding = new ID3D11UnorderedAccessViewBinding();
		_cs_uav_binding.view = _cs_uav_result.handle;
		_cs_uav_binding.initialCount = 4294967295;
		var _cs_uavs_set = id3d11_device_context_cs_set_unordered_access_views(
			global.__id3d11_context,
			0,
			[_cs_uav_binding]);
		var _bound_cs_uavs = id3d11_device_context_cs_get_unordered_access_views(
			global.__id3d11_context,
			0,
			1);
		var _cs_uav_slot_rejected = !id3d11_device_context_cs_set_unordered_access_views(
			global.__id3d11_context,
			64,
			[_cs_uav_binding]);
		var _cs_uav_restore_bindings = [];
		if (array_length(_previous_cs_uavs) > 0)
		{
			var _restore_cs_uav = new ID3D11UnorderedAccessViewBinding();
			_restore_cs_uav.view = _previous_cs_uavs[0];
			_restore_cs_uav.initialCount = 4294967295;
			array_push(_cs_uav_restore_bindings, _restore_cs_uav);
		}
		var _cs_uavs_restored = id3d11_device_context_cs_set_unordered_access_views(
			global.__id3d11_context,
			0,
			_cs_uav_restore_bindings);
		var _previous_cs_uav_release_ok =
			array_length(_previous_cs_uavs) == 0 ||
			_previous_cs_uavs[0] == 0 ||
			_previous_cs_uavs[0] == _cs_uav_result.handle ||
			id3d11_handle_release(_previous_cs_uavs[0]);
		var _cs_uav_release_ok = id3d11_handle_release(_cs_uav_result.handle);
		var _cs_uav_texture_release_ok = id3d11_handle_release(
			_cs_uav_texture_result.handle);

		var _om_combo_texture_desc = new ID3D11Texture2DDesc();
		_om_combo_texture_desc.width = 1;
		_om_combo_texture_desc.height = 1;
		_om_combo_texture_desc.mipLevels = 1;
		_om_combo_texture_desc.arraySize = 1;
		_om_combo_texture_desc.format = 28;
		_om_combo_texture_desc.sampleCount = 1;
		_om_combo_texture_desc.sampleQuality = 0;
		_om_combo_texture_desc.usage = ID3D11Usage.Default;
		_om_combo_texture_desc.bindFlags = ID3D11BindFlag.RenderTarget;
		var _om_combo_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_om_combo_texture_desc);
		var _om_combo_rtv_result = id3d11_device_create_render_target_view_default(
			global.__id3d11_device,
			_om_combo_texture_result.handle);
		var _om_combo_depth_desc = new ID3D11Texture2DDesc();
		_om_combo_depth_desc.width = 1;
		_om_combo_depth_desc.height = 1;
		_om_combo_depth_desc.mipLevels = 1;
		_om_combo_depth_desc.arraySize = 1;
		_om_combo_depth_desc.format = 45;
		_om_combo_depth_desc.sampleCount = 1;
		_om_combo_depth_desc.sampleQuality = 0;
		_om_combo_depth_desc.usage = ID3D11Usage.Default;
		_om_combo_depth_desc.bindFlags = ID3D11BindFlag.DepthStencil;
		var _om_combo_depth_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_om_combo_depth_desc);
		var _om_combo_dsv_result = id3d11_device_create_depth_stencil_view_default(
			global.__id3d11_device,
			_om_combo_depth_result.handle);
		var _om_combo_uav_texture_desc = new ID3D11Texture2DDesc();
		_om_combo_uav_texture_desc.width = 1;
		_om_combo_uav_texture_desc.height = 1;
		_om_combo_uav_texture_desc.mipLevels = 1;
		_om_combo_uav_texture_desc.arraySize = 1;
		_om_combo_uav_texture_desc.format = 28;
		_om_combo_uav_texture_desc.sampleCount = 1;
		_om_combo_uav_texture_desc.sampleQuality = 0;
		_om_combo_uav_texture_desc.usage = ID3D11Usage.Default;
		_om_combo_uav_texture_desc.bindFlags = ID3D11BindFlag.UnorderedAccess;
		var _om_combo_uav_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_om_combo_uav_texture_desc);
		var _om_combo_uav_result = id3d11_device_create_unordered_access_view_default(
			global.__id3d11_device,
			_om_combo_uav_texture_result.handle);
		var _previous_om_combo = id3d11_device_context_om_get_render_targets_and_unordered_access_views(
			global.__id3d11_context,
			1,
			1,
			1);
		var _om_combo_uav_binding = new ID3D11UnorderedAccessViewBinding();
		_om_combo_uav_binding.view = _om_combo_uav_result.handle;
		_om_combo_uav_binding.initialCount = 4294967295;
		var _om_combo_set = id3d11_device_context_om_set_render_targets_and_unordered_access_views(
			global.__id3d11_context,
			false,
			[_om_combo_rtv_result.handle],
			_om_combo_dsv_result.handle,
			1,
			false,
			[_om_combo_uav_binding]);
		var _bound_om_combo = id3d11_device_context_om_get_render_targets_and_unordered_access_views(
			global.__id3d11_context,
			1,
			1,
			1);
		var _om_combo_keep_rt = id3d11_device_context_om_set_render_targets_and_unordered_access_views(
			global.__id3d11_context,
			true,
			[],
			0,
			1,
			false,
			[]);
		var _om_combo_after_keep_rt = id3d11_device_context_om_get_render_targets_and_unordered_access_views(
			global.__id3d11_context,
			1,
			1,
			1);
		var _om_combo_overlap_rejected = !id3d11_device_context_om_set_render_targets_and_unordered_access_views(
			global.__id3d11_context,
			false,
			[_om_combo_rtv_result.handle],
			_om_combo_dsv_result.handle,
			0,
			false,
			[_om_combo_uav_binding]);
		var _om_combo_restore_uavs = [];
		if (array_length(_previous_om_combo.unorderedAccessViews) > 0)
		{
			var _restore_om_uav = new ID3D11UnorderedAccessViewBinding();
			_restore_om_uav.view = _previous_om_combo.unorderedAccessViews[0];
			_restore_om_uav.initialCount = 4294967295;
			array_push(_om_combo_restore_uavs, _restore_om_uav);
		}
		var _om_combo_restored = id3d11_device_context_om_set_render_targets_and_unordered_access_views(
			global.__id3d11_context,
			false,
			_previous_om_combo.renderTargetViews,
			_previous_om_combo.depthStencilView,
			1,
			false,
			_om_combo_restore_uavs);
		var _previous_om_combo_rtv = array_length(_previous_om_combo.renderTargetViews) > 0
			? _previous_om_combo.renderTargetViews[0]
			: 0;
		var _previous_om_combo_uav = array_length(_previous_om_combo.unorderedAccessViews) > 0
			? _previous_om_combo.unorderedAccessViews[0]
			: 0;
		var _previous_om_combo_rtv_release_ok =
			_previous_om_combo_rtv == 0 ||
			_previous_om_combo_rtv == _om_combo_rtv_result.handle ||
			id3d11_handle_release(_previous_om_combo_rtv);
		var _previous_om_combo_dsv_release_ok =
			_previous_om_combo.depthStencilView == 0 ||
			_previous_om_combo.depthStencilView == _om_combo_dsv_result.handle ||
			id3d11_handle_release(_previous_om_combo.depthStencilView);
		var _previous_om_combo_uav_release_ok =
			_previous_om_combo_uav == 0 ||
			_previous_om_combo_uav == _om_combo_uav_result.handle ||
			id3d11_handle_release(_previous_om_combo_uav);
		var _om_combo_rtv_release_ok = id3d11_handle_release(_om_combo_rtv_result.handle);
		var _om_combo_dsv_release_ok = id3d11_handle_release(_om_combo_dsv_result.handle);
		var _om_combo_uav_release_ok = id3d11_handle_release(_om_combo_uav_result.handle);
		var _om_combo_texture_release_ok = id3d11_handle_release(
			_om_combo_texture_result.handle);
		var _om_combo_depth_release_ok = id3d11_handle_release(
			_om_combo_depth_result.handle);
		var _om_combo_uav_texture_release_ok = id3d11_handle_release(
			_om_combo_uav_texture_result.handle);
		var _om_combo_smoke_ok =
			_om_combo_texture_result.hresult == 0 &&
			_om_combo_rtv_result.hresult == 0 &&
			_om_combo_depth_result.hresult == 0 &&
			_om_combo_dsv_result.hresult == 0 &&
			_om_combo_uav_texture_result.hresult == 0 &&
			_om_combo_uav_result.hresult == 0 &&
			_om_combo_set &&
			array_length(_bound_om_combo.renderTargetViews) == 1 &&
			_bound_om_combo.renderTargetViews[0] == _om_combo_rtv_result.handle &&
			_bound_om_combo.depthStencilView == _om_combo_dsv_result.handle &&
			array_length(_bound_om_combo.unorderedAccessViews) == 1 &&
			_bound_om_combo.unorderedAccessViews[0] == _om_combo_uav_result.handle &&
			_om_combo_keep_rt &&
			array_length(_om_combo_after_keep_rt.renderTargetViews) == 1 &&
			_om_combo_after_keep_rt.renderTargetViews[0] == _om_combo_rtv_result.handle &&
			array_length(_om_combo_after_keep_rt.unorderedAccessViews) == 1 &&
			_om_combo_after_keep_rt.unorderedAccessViews[0] == 0 &&
			_om_combo_overlap_rejected &&
			_om_combo_restored &&
			_previous_om_combo_rtv_release_ok &&
			_previous_om_combo_dsv_release_ok &&
			_previous_om_combo_uav_release_ok &&
			_om_combo_rtv_release_ok &&
			_om_combo_dsv_release_ok &&
			_om_combo_uav_release_ok &&
			_om_combo_texture_release_ok &&
			_om_combo_depth_release_ok &&
			_om_combo_uav_texture_release_ok;

		_pipeline_binding_smoke_ok =
			_pipeline_binding_smoke_ok &&
			_om_texture_result.hresult == 0 &&
			_om_rtv_result.hresult == 0 &&
			_om_depth_result.hresult == 0 &&
			_om_dsv_result.hresult == 0 &&
			_om_targets_set &&
			array_length(_bound_om_targets.renderTargetViews) == 1 &&
			_bound_om_targets.renderTargetViews[0] == _om_rtv_result.handle &&
			_bound_om_targets.depthStencilView == _om_dsv_result.handle &&
			_om_count_rejected &&
			_om_targets_restored &&
			_previous_om_rtv_release_ok &&
			_previous_om_dsv_release_ok &&
			_om_rtv_release_ok &&
			_om_dsv_release_ok &&
			_om_texture_release_ok &&
			_om_depth_release_ok &&
			_so_buffer_result.hresult == 0 &&
			_so_targets_set &&
			array_length(_bound_so_targets) == 1 &&
			_bound_so_targets[0] == _so_buffer_result.handle &&
			_so_count_rejected &&
			_so_targets_restored &&
			_previous_so_release_ok &&
			_so_buffer_release_ok &&
			_cs_uav_texture_result.hresult == 0 &&
			_cs_uav_result.hresult == 0 &&
			_cs_uavs_set &&
			array_length(_bound_cs_uavs) == 1 &&
			_bound_cs_uavs[0] == _cs_uav_result.handle &&
			_cs_uav_slot_rejected &&
			_cs_uavs_restored &&
			_previous_cs_uav_release_ok &&
			_cs_uav_release_ok &&
			_cs_uav_texture_release_ok &&
			_om_combo_smoke_ok;

		var _stage_constant_buffer_desc = new ID3D11BufferDesc();
		_stage_constant_buffer_desc.byteWidth = 16;
		_stage_constant_buffer_desc.usage = ID3D11Usage.Default;
		_stage_constant_buffer_desc.bindFlags = ID3D11BindFlag.ConstantBuffer;
		_stage_constant_buffer_desc.cpuAccessFlags = 0;
		_stage_constant_buffer_desc.miscFlags = 0;
		_stage_constant_buffer_desc.structureByteStride = 0;
		var _stage_constant_buffer_result = id3d11_device_create_buffer(
			global.__id3d11_device,
			_stage_constant_buffer_desc);

		var _stage_texture_desc = new ID3D11Texture2DDesc();
		_stage_texture_desc.width = 1;
		_stage_texture_desc.height = 1;
		_stage_texture_desc.mipLevels = 1;
		_stage_texture_desc.arraySize = 1;
		_stage_texture_desc.format = 28;
		_stage_texture_desc.sampleCount = 1;
		_stage_texture_desc.sampleQuality = 0;
		_stage_texture_desc.usage = ID3D11Usage.Default;
		_stage_texture_desc.bindFlags = ID3D11BindFlag.ShaderResource;
		_stage_texture_desc.cpuAccessFlags = 0;
		_stage_texture_desc.miscFlags = 0;
		var _stage_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_stage_texture_desc);
		var _stage_srv_result = id3d11_device_create_shader_resource_view_default(
			global.__id3d11_device,
			_stage_texture_result.handle);

		var _test_stage_bindings = function(
			_set_constant_buffers,
			_get_constant_buffers,
			_set_shader_resources,
			_get_shader_resources,
			_set_samplers,
			_get_samplers,
			_constant_buffer,
			_shader_resource,
			_sampler)
		{
			var _previous_constant_buffers = _get_constant_buffers(
				global.__id3d11_context, 0, 1);
			var _previous_shader_resources = _get_shader_resources(
				global.__id3d11_context, 0, 1);
			var _previous_samplers = _get_samplers(global.__id3d11_context, 0, 1);
			if (array_length(_previous_constant_buffers) != 1 ||
				array_length(_previous_shader_resources) != 1 ||
				array_length(_previous_samplers) != 1)
			{
				return false;
			}

			var _constant_buffers_set = _set_constant_buffers(
				global.__id3d11_context, 0, [_constant_buffer]);
			var _shader_resources_set = _set_shader_resources(
				global.__id3d11_context, 0, [_shader_resource]);
			var _samplers_set = _set_samplers(
				global.__id3d11_context, 0, [_sampler]);
			var _bound_constant_buffers = _get_constant_buffers(
				global.__id3d11_context, 0, 1);
			var _bound_shader_resources = _get_shader_resources(
				global.__id3d11_context, 0, 1);
			var _bound_samplers = _get_samplers(global.__id3d11_context, 0, 1);

			var _constant_buffers_restored = _set_constant_buffers(
				global.__id3d11_context, 0, _previous_constant_buffers);
			var _shader_resources_restored = _set_shader_resources(
				global.__id3d11_context, 0, _previous_shader_resources);
			var _samplers_restored = _set_samplers(
				global.__id3d11_context, 0, _previous_samplers);

			var _previous_constant_buffer = _previous_constant_buffers[0];
			var _previous_shader_resource = _previous_shader_resources[0];
			var _previous_sampler = _previous_samplers[0];
			var _previous_constant_buffer_release_ok =
				_previous_constant_buffer == 0 ||
				_previous_constant_buffer == _constant_buffer ||
				id3d11_handle_release(_previous_constant_buffer);
			var _previous_shader_resource_release_ok =
				_previous_shader_resource == 0 ||
				_previous_shader_resource == _shader_resource ||
				id3d11_handle_release(_previous_shader_resource);
			var _previous_sampler_release_ok =
				_previous_sampler == 0 ||
				_previous_sampler == _sampler ||
				id3d11_handle_release(_previous_sampler);

			return
				_constant_buffers_set &&
				_shader_resources_set &&
				_samplers_set &&
				array_length(_bound_constant_buffers) == 1 &&
				_bound_constant_buffers[0] == _constant_buffer &&
				array_length(_bound_shader_resources) == 1 &&
				_bound_shader_resources[0] == _shader_resource &&
				array_length(_bound_samplers) == 1 &&
				_bound_samplers[0] == _sampler &&
				_constant_buffers_restored &&
				_shader_resources_restored &&
				_samplers_restored &&
				_previous_constant_buffer_release_ok &&
				_previous_shader_resource_release_ok &&
				_previous_sampler_release_ok;
		};

		var _vs_stage_bindings_ok = _test_stage_bindings(
			id3d11_device_context_vs_set_constant_buffers,
			id3d11_device_context_vs_get_constant_buffers,
			id3d11_device_context_vs_set_shader_resources,
			id3d11_device_context_vs_get_shader_resources,
			id3d11_device_context_vs_set_samplers,
			id3d11_device_context_vs_get_samplers,
			_stage_constant_buffer_result.handle,
			_stage_srv_result.handle,
			_sampler_result.handle);
		var _hs_stage_bindings_ok = _test_stage_bindings(
			id3d11_device_context_hs_set_constant_buffers,
			id3d11_device_context_hs_get_constant_buffers,
			id3d11_device_context_hs_set_shader_resources,
			id3d11_device_context_hs_get_shader_resources,
			id3d11_device_context_hs_set_samplers,
			id3d11_device_context_hs_get_samplers,
			_stage_constant_buffer_result.handle,
			_stage_srv_result.handle,
			_sampler_result.handle);
		var _ds_stage_bindings_ok = _test_stage_bindings(
			id3d11_device_context_ds_set_constant_buffers,
			id3d11_device_context_ds_get_constant_buffers,
			id3d11_device_context_ds_set_shader_resources,
			id3d11_device_context_ds_get_shader_resources,
			id3d11_device_context_ds_set_samplers,
			id3d11_device_context_ds_get_samplers,
			_stage_constant_buffer_result.handle,
			_stage_srv_result.handle,
			_sampler_result.handle);
		var _gs_stage_bindings_ok = _test_stage_bindings(
			id3d11_device_context_gs_set_constant_buffers,
			id3d11_device_context_gs_get_constant_buffers,
			id3d11_device_context_gs_set_shader_resources,
			id3d11_device_context_gs_get_shader_resources,
			id3d11_device_context_gs_set_samplers,
			id3d11_device_context_gs_get_samplers,
			_stage_constant_buffer_result.handle,
			_stage_srv_result.handle,
			_sampler_result.handle);
		var _ps_stage_bindings_ok = _test_stage_bindings(
			id3d11_device_context_ps_set_constant_buffers,
			id3d11_device_context_ps_get_constant_buffers,
			id3d11_device_context_ps_set_shader_resources,
			id3d11_device_context_ps_get_shader_resources,
			id3d11_device_context_ps_set_samplers,
			id3d11_device_context_ps_get_samplers,
			_stage_constant_buffer_result.handle,
			_stage_srv_result.handle,
			_sampler_result.handle);
		var _cs_stage_bindings_ok = _test_stage_bindings(
			id3d11_device_context_cs_set_constant_buffers,
			id3d11_device_context_cs_get_constant_buffers,
			id3d11_device_context_cs_set_shader_resources,
			id3d11_device_context_cs_get_shader_resources,
			id3d11_device_context_cs_set_samplers,
			id3d11_device_context_cs_get_samplers,
			_stage_constant_buffer_result.handle,
			_stage_srv_result.handle,
			_sampler_result.handle);
		var _stage_invalid_constant_slot_rejected =
			!id3d11_device_context_vs_set_constant_buffers(
				global.__id3d11_context, 14, [_stage_constant_buffer_result.handle]);
		var _stage_invalid_resource_slot_rejected =
			!id3d11_device_context_vs_set_shader_resources(
				global.__id3d11_context, 128, [_stage_srv_result.handle]);
		var _stage_invalid_sampler_slot_rejected =
			!id3d11_device_context_vs_set_samplers(
				global.__id3d11_context, 16, [_sampler_result.handle]);
		var _stage_srv_release_ok = id3d11_handle_release(_stage_srv_result.handle);
		var _stage_texture_release_ok = id3d11_handle_release(_stage_texture_result.handle);
		var _stage_constant_buffer_release_ok = id3d11_handle_release(
			_stage_constant_buffer_result.handle);
		var _stage_bindings_smoke_ok =
			_stage_constant_buffer_result.hresult == 0 &&
			_stage_texture_result.hresult == 0 &&
			_stage_srv_result.hresult == 0 &&
			_vs_stage_bindings_ok &&
			_hs_stage_bindings_ok &&
			_ds_stage_bindings_ok &&
			_gs_stage_bindings_ok &&
			_ps_stage_bindings_ok &&
			_cs_stage_bindings_ok &&
			_stage_invalid_constant_slot_rejected &&
			_stage_invalid_resource_slot_rejected &&
			_stage_invalid_sampler_slot_rejected &&
			_stage_srv_release_ok &&
			_stage_texture_release_ok &&
			_stage_constant_buffer_release_ok;

		var _state_kinds_ok =
			id3d11_handle_get_kind(_sampler_result.handle) == ID3D11HandleKind.SamplerState &&
			id3d11_handle_get_kind(_rasterizer_result.handle) == ID3D11HandleKind.RasterizerState &&
			id3d11_handle_get_kind(_blend_result.handle) == ID3D11HandleKind.BlendState &&
			id3d11_handle_get_kind(_depth_stencil_result.handle) == ID3D11HandleKind.DepthStencilState;
		var _state_parent_device = id3d11_device_child_get_device(_sampler_result.handle);
		var _sampler_handle = _sampler_result.handle;
		var _input_layout_release_ok = id3d11_handle_release(_input_layout_result.handle);
		var _state_releases_ok =
			id3d11_handle_release(_sampler_result.handle) &&
			id3d11_handle_release(_rasterizer_result.handle) &&
			id3d11_handle_release(_blend_result.handle) &&
			id3d11_handle_release(_depth_stencil_result.handle);
		var _sampler_state_ok =
			_sampler_result.hresult == 0 &&
			_sampler_roundtrip.filter == ID3D11Filter.Anisotropic &&
			_sampler_roundtrip.addressU == ID3D11TextureAddressMode.Clamp &&
			_sampler_roundtrip.maxAnisotropy == 4;
		var _rasterizer_state_ok =
			_rasterizer_result.hresult == 0 &&
			_rasterizer_roundtrip.fillMode == ID3D11FillMode.Solid &&
			_rasterizer_roundtrip.cullMode == ID3D11CullMode.Back &&
			_rasterizer_roundtrip.depthClipEnable;
		var _blend_state_ok =
			_blend_result.hresult == 0 &&
			array_length(_blend_roundtrip.renderTargets) == 8 &&
			_blend_roundtrip.renderTargets[0].renderTargetWriteMask == ID3D11ColorWriteEnable.All &&
			_invalid_blend_result.hresult != 0 && _invalid_blend_result.handle == 0;
		var _depth_stencil_state_ok =
			_depth_stencil_result.hresult == 0 &&
			_depth_stencil_roundtrip.depthEnable &&
			_depth_stencil_roundtrip.depthWriteMask == ID3D11DepthWriteMask.All &&
			_depth_stencil_roundtrip.depthFunc == ID3D11ComparisonFunc.Less &&
			_depth_stencil_roundtrip.frontFace.stencilFunc == ID3D11ComparisonFunc.Always;
		var _state_stale_rejected = !id3d11_handle_is_valid(_sampler_handle);
		global.__id3d11_state_smoke_ok =
			_sampler_state_ok &&
			_rasterizer_state_ok &&
			_blend_state_ok &&
			_depth_stencil_state_ok &&
			_state_kinds_ok &&
			_state_parent_device == global.__id3d11_device &&
			_state_releases_ok &&
			_state_stale_rejected;

		var _query_desc = new ID3D11QueryDesc();
		_query_desc.query = ID3D11Query.Event;
		_query_desc.miscFlags = 0;
		var _query_result = id3d11_device_create_query(
			global.__id3d11_device,
			_query_desc);
		var _query_roundtrip = id3d11_query_get_desc(_query_result.handle);
		var _query_data_size = id3d11_asynchronous_get_data_size(_query_result.handle);

		var _predicate_desc = new ID3D11QueryDesc();
		_predicate_desc.query = ID3D11Query.OcclusionPredicate;
		_predicate_desc.miscFlags = ID3D11QueryMiscFlag.PredicateHint;
		var _predicate_result = id3d11_device_create_predicate(
			global.__id3d11_device,
			_predicate_desc);
		var _predicate_roundtrip = id3d11_query_get_desc(_predicate_result.handle);
		var _predicate_data_size = id3d11_asynchronous_get_data_size(
			_predicate_result.handle);
		var _invalid_predicate_result = id3d11_device_create_predicate(
			global.__id3d11_device,
			_query_desc);

		var _counter_info = id3d11_device_get_counter_info(global.__id3d11_device);
		var _counter_desc = new ID3D11CounterDesc();
		_counter_desc.counter = ID3D11Counter.DeviceDependent0;
		_counter_desc.miscFlags = 0;
		var _check_counter_result = id3d11_device_check_counter(
			global.__id3d11_device,
			_counter_desc);
		var _counter_result = id3d11_device_create_counter(
			global.__id3d11_device,
			_counter_desc);
		var _counter_supported = _check_counter_result.hresult == 0;
		var _counter_roundtrip = id3d11_counter_get_desc(_counter_result.handle);
		var _counter_data_size = id3d11_asynchronous_get_data_size(_counter_result.handle);
		var _counter_ok = false;
		if (_counter_supported)
		{
			_counter_ok =
				_counter_info.lastDeviceDependentCounter >= ID3D11Counter.DeviceDependent0 &&
				_counter_result.hresult == 0 &&
				_counter_roundtrip.counter == ID3D11Counter.DeviceDependent0 &&
				_counter_data_size > 0;
		}
		else
		{
			_counter_ok = _counter_result.hresult != 0 && _counter_result.handle == 0;
		}

		var _query_data = buffer_create(max(_query_data_size, 1), buffer_fixed, 1);
		var _predicate_begin_ok = id3d11_device_context_begin(
			global.__id3d11_context,
			_predicate_result.handle);
		var _predicate_end_ok = id3d11_device_context_end(
			global.__id3d11_context,
			_predicate_result.handle);
		var _query_end_ok = id3d11_device_context_end(
			global.__id3d11_context,
			_query_result.handle);
		var _context_flush_ok = id3d11_device_context_flush(global.__id3d11_context);
		var _query_get_data_result = 1;
		repeat (1024)
		{
			_query_get_data_result = id3d11_device_context_get_data(
				global.__id3d11_context,
				_query_result.handle,
				_query_data,
				_query_data_size,
				0);
			if (_query_get_data_result != 1)
			{
				break;
			}
		}
		var _query_data_value = 0;
		if (_query_data_size >= 4)
		{
			_query_data_value = buffer_peek(_query_data, 0, buffer_u32);
		}
		var _query_bounds_rejected = id3d11_device_context_get_data(
			global.__id3d11_context,
			_query_result.handle,
			_query_data,
			_query_data_size + 1,
			0) != 0;
		var _query_flags_rejected = id3d11_device_context_get_data(
			global.__id3d11_context,
			_query_result.handle,
			_query_data,
			_query_data_size,
			2) != 0;
		buffer_delete(_query_data);
		global.__id3d11_context_smoke_ok =
			_predicate_begin_ok &&
			_predicate_end_ok &&
			_query_end_ok &&
			_context_flush_ok &&
			_query_data_size == 4 &&
			_query_get_data_result == 0 &&
			_query_data_value != 0 &&
			_query_bounds_rejected &&
			_query_flags_rejected;

		var _direct_execution_ok =
			id3d11_device_context_draw(global.__id3d11_context, 0, 0) &&
			id3d11_device_context_draw_indexed(global.__id3d11_context, 0, 0, 0) &&
			id3d11_device_context_draw_instanced(global.__id3d11_context, 0, 0, 0, 0) &&
			id3d11_device_context_draw_indexed_instanced(
				global.__id3d11_context, 0, 0, 0, 0, 0) &&
			id3d11_device_context_draw_auto(global.__id3d11_context) &&
			id3d11_device_context_dispatch(global.__id3d11_context, 0, 0, 0) &&
			!id3d11_device_context_dispatch(global.__id3d11_context, 65536, 0, 0);

		var _indirect_data = buffer_create(48, buffer_fixed, 1);
		repeat (12)
		{
			buffer_write(_indirect_data, buffer_u32, 0);
		}
		var _indirect_desc = new ID3D11BufferDesc();
		_indirect_desc.byteWidth = 48;
		_indirect_desc.usage = ID3D11Usage.Default;
		_indirect_desc.bindFlags = 0;
		_indirect_desc.cpuAccessFlags = 0;
		_indirect_desc.miscFlags = ID3D11ResourceMiscFlag.DrawIndirectArgs;
		_indirect_desc.structureByteStride = 0;
		var _indirect_result = id3d11_device_create_buffer_with_data(
			global.__id3d11_device,
			_indirect_desc,
			_indirect_data);
		var _indirect_execution_ok =
			id3d11_device_context_draw_indexed_instanced_indirect(
				global.__id3d11_context, _indirect_result.handle, 0) &&
			id3d11_device_context_draw_instanced_indirect(
				global.__id3d11_context, _indirect_result.handle, 20) &&
			id3d11_device_context_dispatch_indirect(
				global.__id3d11_context, _indirect_result.handle, 36) &&
			!id3d11_device_context_draw_instanced_indirect(
				global.__id3d11_context, _indirect_result.handle, 2) &&
			!id3d11_device_context_dispatch_indirect(
				global.__id3d11_context, _indirect_result.handle, 40);
		var _indirect_release_ok = id3d11_handle_release(_indirect_result.handle);
		buffer_delete(_indirect_data);

		var _copy_data = buffer_create(16, buffer_fixed, 1);
		buffer_write(_copy_data, buffer_u32, 10);
		buffer_write(_copy_data, buffer_u32, 20);
		buffer_write(_copy_data, buffer_u32, 30);
		buffer_write(_copy_data, buffer_u32, 40);
		var _copy_desc = new ID3D11BufferDesc();
		_copy_desc.byteWidth = 16;
		_copy_desc.usage = ID3D11Usage.Default;
		_copy_desc.bindFlags = 0;
		_copy_desc.cpuAccessFlags = 0;
		_copy_desc.miscFlags = 0;
		_copy_desc.structureByteStride = 0;
		var _copy_source_result = id3d11_device_create_buffer_with_data(
			global.__id3d11_device,
			_copy_desc,
			_copy_data);
		var _copy_destination_result = id3d11_device_create_buffer(
			global.__id3d11_device,
			_copy_desc);
		var _copy_box = new ID3D11Box();
		_copy_box.left = 4;
		_copy_box.top = 0;
		_copy_box.front = 0;
		_copy_box.right = 12;
		_copy_box.bottom = 1;
		_copy_box.back = 1;
		var _copy_resource_ok = id3d11_device_context_copy_resource(
			global.__id3d11_context,
			_copy_destination_result.handle,
			_copy_source_result.handle);
		var _copy_region_ok = id3d11_device_context_copy_subresource_region(
			global.__id3d11_context,
			_copy_destination_result.handle,
			0,
			4,
			0,
			0,
			_copy_source_result.handle,
			0,
			true,
			_copy_box);
		var _copy_full_region_ok = id3d11_device_context_copy_subresource_region(
			global.__id3d11_context,
			_copy_destination_result.handle,
			0,
			0,
			0,
			0,
			_copy_source_result.handle,
			0,
			false,
			_copy_box);
		var _copy_same_resource_rejected = !id3d11_device_context_copy_resource(
			global.__id3d11_context,
			_copy_source_result.handle,
			_copy_source_result.handle);
		var _copy_region_bounds_rejected = !id3d11_device_context_copy_subresource_region(
			global.__id3d11_context,
			_copy_destination_result.handle,
			0,
			9,
			0,
			0,
			_copy_source_result.handle,
			0,
			true,
			_copy_box);

		var _staging_buffer_desc = new ID3D11BufferDesc();
		_staging_buffer_desc.byteWidth = 16;
		_staging_buffer_desc.usage = ID3D11Usage.Staging;
		_staging_buffer_desc.cpuAccessFlags =
			ID3D11CpuAccessFlag.Read | ID3D11CpuAccessFlag.Write;
		var _staging_buffer_result = id3d11_device_create_buffer(
			global.__id3d11_device,
			_staging_buffer_desc);
		show_debug_message("[ID3D11] transfer buffer created");
		var _map_write_ok = id3d11_device_context_map_write_from_buffer(
			global.__id3d11_context,
			_staging_buffer_result.handle,
			0,
			ID3D11Map.Write,
			0,
			_copy_data);
		show_debug_message("[ID3D11] transfer buffer written");
		var _map_read_data = buffer_create(16, buffer_fixed, 1);
		var _map_read_ok = id3d11_device_context_map_read_to_buffer(
			global.__id3d11_context,
			_staging_buffer_result.handle,
			0,
			ID3D11Map.Read,
			0,
			_map_read_data);
		show_debug_message("[ID3D11] transfer buffer read");
		var _map_roundtrip_ok =
			buffer_peek(_map_read_data, 0, buffer_u32) == 10 &&
			buffer_peek(_map_read_data, 4, buffer_u32) == 20 &&
			buffer_peek(_map_read_data, 8, buffer_u32) == 30 &&
			buffer_peek(_map_read_data, 12, buffer_u32) == 40;
		var _map_short_data = buffer_create(15, buffer_fixed, 1);
		var _map_bounds_rejected = !id3d11_device_context_map_read_to_buffer(
			global.__id3d11_context,
			_staging_buffer_result.handle,
			0,
			ID3D11Map.Read,
			0,
			_map_short_data);
		var _map_type_rejected = !id3d11_device_context_map_write_from_buffer(
			global.__id3d11_context,
			_staging_buffer_result.handle,
			0,
			ID3D11Map.WriteDiscard,
			0,
			_copy_data);
		var _staging_buffer_release_ok = id3d11_handle_release(
			_staging_buffer_result.handle);
		buffer_delete(_map_short_data);
		buffer_delete(_map_read_data);
		var _copy_source_release_ok = id3d11_handle_release(_copy_source_result.handle);
		var _copy_destination_release_ok = id3d11_handle_release(
			_copy_destination_result.handle);
		buffer_delete(_copy_data);

		var _execution_texture_desc = new ID3D11Texture2DDesc();
		_execution_texture_desc.width = 4;
		_execution_texture_desc.height = 4;
		_execution_texture_desc.mipLevels = 3;
		_execution_texture_desc.arraySize = 1;
		_execution_texture_desc.format = 28;
		_execution_texture_desc.sampleCount = 1;
		_execution_texture_desc.sampleQuality = 0;
		_execution_texture_desc.usage = ID3D11Usage.Default;
		_execution_texture_desc.bindFlags =
			ID3D11BindFlag.ShaderResource |
			ID3D11BindFlag.RenderTarget;
		_execution_texture_desc.cpuAccessFlags = 0;
		_execution_texture_desc.miscFlags = ID3D11ResourceMiscFlag.GenerateMips;
		var _execution_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_execution_texture_desc);
		var _execution_srv_result = id3d11_device_create_shader_resource_view_default(
			global.__id3d11_device,
			_execution_texture_result.handle);
		var _execution_rtv_result = id3d11_device_create_render_target_view_default(
			global.__id3d11_device,
			_execution_texture_result.handle);
		var _update_texture_desc = new ID3D11Texture2DDesc();
		_update_texture_desc.width = 2;
		_update_texture_desc.height = 2;
		_update_texture_desc.mipLevels = 1;
		_update_texture_desc.arraySize = 1;
		_update_texture_desc.format = 28;
		_update_texture_desc.sampleCount = 1;
		_update_texture_desc.usage = ID3D11Usage.Default;
		var _update_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_update_texture_desc);
		show_debug_message("[ID3D11] transfer texture created");
		var _update_source = buffer_create(24, buffer_fixed, 1);
		buffer_poke(_update_source, 0, buffer_u32, 101);
		buffer_poke(_update_source, 4, buffer_u32, 102);
		buffer_poke(_update_source, 12, buffer_u32, 103);
		buffer_poke(_update_source, 16, buffer_u32, 104);
		var _update_box = new ID3D11Box();
		_update_box.left = 0;
		_update_box.top = 0;
		_update_box.front = 0;
		_update_box.right = 0;
		_update_box.bottom = 0;
		_update_box.back = 0;
		show_debug_message("[ID3D11] transfer texture update begin");
		var _update_texture_ok = id3d11_device_context_update_subresource(
			global.__id3d11_context,
			_update_texture_result.handle,
			0,
			false,
			_update_box,
			_update_source,
			0,
			24,
			12,
			24);
		show_debug_message("[ID3D11] transfer texture updated");
		var _update_bounds_rejected = !id3d11_device_context_update_subresource(
			global.__id3d11_context,
			_update_texture_result.handle,
			0,
			false,
			_update_box,
			_update_source,
			0,
			19,
			12,
			24);
		var _staging_texture_desc = new ID3D11Texture2DDesc();
		_staging_texture_desc.width = 2;
		_staging_texture_desc.height = 2;
		_staging_texture_desc.mipLevels = 1;
		_staging_texture_desc.arraySize = 1;
		_staging_texture_desc.format = 28;
		_staging_texture_desc.sampleCount = 1;
		_staging_texture_desc.usage = ID3D11Usage.Staging;
		_staging_texture_desc.cpuAccessFlags = ID3D11CpuAccessFlag.Read;
		var _staging_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_staging_texture_desc);
		var _update_copy_ok = id3d11_device_context_copy_resource(
			global.__id3d11_context,
			_staging_texture_result.handle,
			_update_texture_result.handle);
		var _update_readback = buffer_create(16, buffer_fixed, 1);
		var _update_readback_ok = id3d11_device_context_map_read_to_buffer(
			global.__id3d11_context,
			_staging_texture_result.handle,
			0,
			ID3D11Map.Read,
			0,
			_update_readback);
		show_debug_message("[ID3D11] transfer texture read");
		var _update_values_ok =
			buffer_peek(_update_readback, 0, buffer_u32) == 101 &&
			buffer_peek(_update_readback, 4, buffer_u32) == 102 &&
			buffer_peek(_update_readback, 8, buffer_u32) == 103 &&
			buffer_peek(_update_readback, 12, buffer_u32) == 104;
		buffer_delete(_update_readback);
		buffer_delete(_update_source);
		var _execution_uav_texture_desc = new ID3D11Texture2DDesc();
		_execution_uav_texture_desc.width = 1;
		_execution_uav_texture_desc.height = 1;
		_execution_uav_texture_desc.mipLevels = 1;
		_execution_uav_texture_desc.arraySize = 1;
		_execution_uav_texture_desc.format = 28;
		_execution_uav_texture_desc.sampleCount = 1;
		_execution_uav_texture_desc.sampleQuality = 0;
		_execution_uav_texture_desc.usage = ID3D11Usage.Default;
		_execution_uav_texture_desc.bindFlags = ID3D11BindFlag.UnorderedAccess;
		var _execution_uav_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_execution_uav_texture_desc);
		var _execution_uav_result = id3d11_device_create_unordered_access_view_default(
			global.__id3d11_device,
			_execution_uav_texture_result.handle);
		var _clear_rtv_ok = id3d11_device_context_clear_render_target_view(
			global.__id3d11_context,
			_execution_rtv_result.handle,
			0.25,
			0.5,
			0.75,
			1.0);
		var _clear_uav_uint_ok = id3d11_device_context_clear_unordered_access_view_uint(
			global.__id3d11_context,
			_execution_uav_result.handle,
			1,
			2,
			3,
			4);
		var _clear_uav_float_ok = id3d11_device_context_clear_unordered_access_view_float(
			global.__id3d11_context,
			_execution_uav_result.handle,
			0.0,
			0.25,
			0.5,
			1.0);
		var _generate_mips_ok = id3d11_device_context_generate_mips(
			global.__id3d11_context,
			_execution_srv_result.handle);
		var _lod_texture_desc = new ID3D11Texture2DDesc();
		_lod_texture_desc.width = 4;
		_lod_texture_desc.height = 4;
		_lod_texture_desc.mipLevels = 3;
		_lod_texture_desc.arraySize = 1;
		_lod_texture_desc.format = 28;
		_lod_texture_desc.sampleCount = 1;
		_lod_texture_desc.sampleQuality = 0;
		_lod_texture_desc.usage = ID3D11Usage.Default;
		_lod_texture_desc.bindFlags = ID3D11BindFlag.ShaderResource;
		_lod_texture_desc.miscFlags = ID3D11ResourceMiscFlag.ResourceClamp;
		var _lod_texture_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_lod_texture_desc);
		var _resource_min_lod_set_ok = id3d11_device_context_set_resource_min_lod(
			global.__id3d11_context,
			_lod_texture_result.handle,
			1.0);
		var _resource_min_lod = id3d11_device_context_get_resource_min_lod(
			global.__id3d11_context,
			_lod_texture_result.handle);
		var _resource_min_lod_invalid_rejected = !id3d11_device_context_set_resource_min_lod(
			global.__id3d11_context,
			_lod_texture_result.handle,
			-1.0);
		var _generate_mips_wrong_view_rejected = !id3d11_device_context_generate_mips(
			global.__id3d11_context,
			_execution_rtv_result.handle);

		var _structured_desc = new ID3D11BufferDesc();
		_structured_desc.byteWidth = 16;
		_structured_desc.usage = ID3D11Usage.Default;
		_structured_desc.bindFlags = ID3D11BindFlag.UnorderedAccess;
		_structured_desc.cpuAccessFlags = 0;
		_structured_desc.miscFlags = ID3D11ResourceMiscFlag.BufferStructured;
		_structured_desc.structureByteStride = 4;
		var _structured_result = id3d11_device_create_buffer(
			global.__id3d11_device,
			_structured_desc);
		var _counter_uav_desc = new ID3D11UnorderedAccessViewDesc();
		_counter_uav_desc.format = 0;
		_counter_uav_desc.viewDimension = ID3D11UnorderedAccessViewDimension.Buffer;
		_counter_uav_desc.firstElement = 0;
		_counter_uav_desc.numElements = 4;
		_counter_uav_desc.flags = ID3D11BufferUavFlag.Counter;
		var _counter_uav_result = id3d11_device_create_unordered_access_view(
			global.__id3d11_device,
			_structured_result.handle,
			_counter_uav_desc);
		var _count_destination_desc = new ID3D11BufferDesc();
		_count_destination_desc.byteWidth = 4;
		_count_destination_desc.usage = ID3D11Usage.Default;
		var _count_destination_result = id3d11_device_create_buffer(
			global.__id3d11_device,
			_count_destination_desc);
		var _copy_structure_count_ok = id3d11_device_context_copy_structure_count(
			global.__id3d11_context,
			_count_destination_result.handle,
			0,
			_counter_uav_result.handle);
		var _copy_structure_alignment_rejected = !id3d11_device_context_copy_structure_count(
			global.__id3d11_context,
			_count_destination_result.handle,
			1,
			_counter_uav_result.handle);
		var _copy_structure_plain_uav_rejected = !id3d11_device_context_copy_structure_count(
			global.__id3d11_context,
			_count_destination_result.handle,
			0,
			_execution_uav_result.handle);

		var _execution_depth_desc = new ID3D11Texture2DDesc();
		_execution_depth_desc.width = 2;
		_execution_depth_desc.height = 2;
		_execution_depth_desc.mipLevels = 1;
		_execution_depth_desc.arraySize = 1;
		_execution_depth_desc.format = 45;
		_execution_depth_desc.sampleCount = 1;
		_execution_depth_desc.sampleQuality = 0;
		_execution_depth_desc.usage = ID3D11Usage.Default;
		_execution_depth_desc.bindFlags = ID3D11BindFlag.DepthStencil;
		var _execution_depth_result = id3d11_device_create_texture2d(
			global.__id3d11_device,
			_execution_depth_desc);
		var _execution_dsv_result = id3d11_device_create_depth_stencil_view_default(
			global.__id3d11_device,
			_execution_depth_result.handle);
		var _clear_dsv_ok = id3d11_device_context_clear_depth_stencil_view(
			global.__id3d11_context,
			_execution_dsv_result.handle,
			ID3D11ClearFlag.Depth | ID3D11ClearFlag.Stencil,
			1.0,
			255);
		var _clear_dsv_flags_rejected = !id3d11_device_context_clear_depth_stencil_view(
			global.__id3d11_context,
			_execution_dsv_result.handle,
			0,
			1.0,
			0);
		var _clear_dsv_stencil_rejected = !id3d11_device_context_clear_depth_stencil_view(
			global.__id3d11_context,
			_execution_dsv_result.handle,
			ID3D11ClearFlag.Stencil,
			1.0,
			256);

		var _resolve_support = id3d11_device_check_multisample_quality_levels(
			global.__id3d11_device,
			28,
			2);
		var _resolve_create_ok = true;
		var _resolve_execution_ok = true;
		var _resolve_release_ok = true;
		if (_resolve_support.hresult == 0 && _resolve_support.qualityLevels > 0)
		{
			var _resolve_source_desc = new ID3D11Texture2DDesc();
			_resolve_source_desc.width = 2;
			_resolve_source_desc.height = 2;
			_resolve_source_desc.mipLevels = 1;
			_resolve_source_desc.arraySize = 1;
			_resolve_source_desc.format = 28;
			_resolve_source_desc.sampleCount = 2;
			_resolve_source_desc.sampleQuality = 0;
			_resolve_source_desc.usage = ID3D11Usage.Default;
			_resolve_source_desc.bindFlags = ID3D11BindFlag.RenderTarget;
			var _resolve_destination_desc = new ID3D11Texture2DDesc();
			_resolve_destination_desc.width = 2;
			_resolve_destination_desc.height = 2;
			_resolve_destination_desc.mipLevels = 1;
			_resolve_destination_desc.arraySize = 1;
			_resolve_destination_desc.format = 28;
			_resolve_destination_desc.sampleCount = 1;
			_resolve_destination_desc.sampleQuality = 0;
			_resolve_destination_desc.usage = ID3D11Usage.Default;
			_resolve_destination_desc.bindFlags = ID3D11BindFlag.RenderTarget;
			var _resolve_source_result = id3d11_device_create_texture2d(
				global.__id3d11_device,
				_resolve_source_desc);
			var _resolve_destination_result = id3d11_device_create_texture2d(
				global.__id3d11_device,
				_resolve_destination_desc);
			_resolve_create_ok =
				_resolve_source_result.hresult == 0 &&
				_resolve_destination_result.hresult == 0;
			_resolve_execution_ok = id3d11_device_context_resolve_subresource(
				global.__id3d11_context,
				_resolve_destination_result.handle,
				0,
				_resolve_source_result.handle,
				0,
				28) &&
				!id3d11_device_context_resolve_subresource(
					global.__id3d11_context,
					_resolve_source_result.handle,
					0,
					_resolve_destination_result.handle,
					0,
					28);
			_resolve_release_ok =
				id3d11_handle_release(_resolve_source_result.handle) &&
				id3d11_handle_release(_resolve_destination_result.handle);
		}

		var _execution_view_releases_ok =
			id3d11_handle_release(_execution_srv_result.handle) &&
			id3d11_handle_release(_execution_rtv_result.handle) &&
			id3d11_handle_release(_execution_uav_result.handle) &&
			id3d11_handle_release(_execution_dsv_result.handle) &&
			id3d11_handle_release(_counter_uav_result.handle);
		var _execution_resource_releases_ok =
			id3d11_handle_release(_execution_texture_result.handle) &&
			id3d11_handle_release(_execution_uav_texture_result.handle) &&
			id3d11_handle_release(_lod_texture_result.handle) &&
			id3d11_handle_release(_execution_depth_result.handle) &&
			id3d11_handle_release(_structured_result.handle) &&
			id3d11_handle_release(_count_destination_result.handle) &&
			id3d11_handle_release(_update_texture_result.handle) &&
			id3d11_handle_release(_staging_texture_result.handle);
		var _context_execution_smoke_ok =
			_direct_execution_ok &&
			_indirect_result.hresult == 0 &&
			_indirect_execution_ok &&
			_indirect_release_ok &&
			_copy_source_result.hresult == 0 &&
			_copy_destination_result.hresult == 0 &&
			_copy_resource_ok &&
			_copy_region_ok &&
			_copy_full_region_ok &&
			_copy_same_resource_rejected &&
			_copy_region_bounds_rejected &&
			_staging_buffer_result.hresult == 0 &&
			_map_write_ok &&
			_map_read_ok &&
			_map_roundtrip_ok &&
			_map_bounds_rejected &&
			_map_type_rejected &&
			_staging_buffer_release_ok &&
			_copy_source_release_ok &&
			_copy_destination_release_ok &&
			_execution_texture_result.hresult == 0 &&
			_execution_srv_result.hresult == 0 &&
			_execution_rtv_result.hresult == 0 &&
			_update_texture_result.hresult == 0 &&
			_staging_texture_result.hresult == 0 &&
			_update_texture_ok &&
			_update_bounds_rejected &&
			_update_copy_ok &&
			_update_readback_ok &&
			_update_values_ok &&
			_execution_uav_texture_result.hresult == 0 &&
			_execution_uav_result.hresult == 0 &&
			_clear_rtv_ok &&
			_clear_uav_uint_ok &&
			_clear_uav_float_ok &&
			_generate_mips_ok &&
			_lod_texture_result.hresult == 0 &&
			_resource_min_lod_set_ok &&
			_resource_min_lod == 1.0 &&
			_resource_min_lod_invalid_rejected &&
			_generate_mips_wrong_view_rejected &&
			_structured_result.hresult == 0 &&
			_counter_uav_result.hresult == 0 &&
			_count_destination_result.hresult == 0 &&
			_copy_structure_count_ok &&
			_copy_structure_alignment_rejected &&
			_copy_structure_plain_uav_rejected &&
			_execution_depth_result.hresult == 0 &&
			_execution_dsv_result.hresult == 0 &&
			_clear_dsv_ok &&
			_clear_dsv_flags_rejected &&
			_clear_dsv_stencil_rejected &&
			_resolve_create_ok &&
			_resolve_execution_ok &&
			_resolve_release_ok &&
			_execution_view_releases_ok &&
			_execution_resource_releases_ok;
		global.__id3d11_context_smoke_ok =
			global.__id3d11_context_smoke_ok &&
			_context_execution_smoke_ok;

		var _previous_predication = id3d11_device_context_get_predication(
			global.__id3d11_context);
		var _pipeline_predication_set = id3d11_device_context_set_predication(
			global.__id3d11_context,
			_predicate_result.handle,
			true);
		var _bound_predication = id3d11_device_context_get_predication(
			global.__id3d11_context);
		var _pipeline_invalid_predicate_rejected = !id3d11_device_context_set_predication(
			global.__id3d11_context,
			_query_result.handle,
			false);
		var _pipeline_predication_restored = id3d11_device_context_set_predication(
			global.__id3d11_context,
			_previous_predication.predicate,
			_previous_predication.predicateValue != 0);
		var _previous_predicate_release_ok =
			_previous_predication.predicate == 0 ||
			_previous_predication.predicate == _predicate_result.handle ||
			id3d11_handle_release(_previous_predication.predicate);
		var _clear_state_saved_om = id3d11_device_context_om_get_render_targets(
			global.__id3d11_context,
			1);
		var _clear_state_saved_topology = id3d11_device_context_ia_get_primitive_topology(
			global.__id3d11_context);
		var _clear_state_saved_viewports = id3d11_device_context_rs_get_viewports(
			global.__id3d11_context);
		var _clear_state_ok = id3d11_device_context_clear_state(global.__id3d11_context);
		var _cleared_topology = id3d11_device_context_ia_get_primitive_topology(
			global.__id3d11_context);
		var _cleared_viewports = id3d11_device_context_rs_get_viewports(
			global.__id3d11_context);
		var _cleared_om = id3d11_device_context_om_get_render_targets(
			global.__id3d11_context,
			1);
		var _clear_state_restored_om = id3d11_device_context_om_set_render_targets(
			global.__id3d11_context,
			_clear_state_saved_om.renderTargetViews,
			_clear_state_saved_om.depthStencilView);
		var _clear_state_restored_topology = id3d11_device_context_ia_set_primitive_topology(
			global.__id3d11_context,
			_clear_state_saved_topology);
		var _clear_state_restored_viewports = id3d11_device_context_rs_set_viewports(
			global.__id3d11_context,
			_clear_state_saved_viewports);
		var _clear_state_saved_rtv = array_length(_clear_state_saved_om.renderTargetViews) > 0
			? _clear_state_saved_om.renderTargetViews[0]
			: 0;
		var _clear_state_saved_rtv_release_ok =
			_clear_state_saved_rtv == 0 ||
			id3d11_handle_release(_clear_state_saved_rtv);
		var _clear_state_saved_dsv_release_ok =
			_clear_state_saved_om.depthStencilView == 0 ||
			id3d11_handle_release(_clear_state_saved_om.depthStencilView);
		var _clear_state_cleared_rtv = array_length(_cleared_om.renderTargetViews) > 0
			? _cleared_om.renderTargetViews[0]
			: 0;
		var _clear_state_cleared_rtv_release_ok =
			_clear_state_cleared_rtv == 0 ||
			id3d11_handle_release(_clear_state_cleared_rtv);
		var _clear_state_cleared_dsv_release_ok =
			_cleared_om.depthStencilView == 0 ||
			id3d11_handle_release(_cleared_om.depthStencilView);
		var _clear_state_smoke_ok =
			_clear_state_ok &&
			_cleared_topology == 0 &&
			array_length(_cleared_viewports) == 0 &&
			(array_length(_cleared_om.renderTargetViews) == 0 ||
				_cleared_om.renderTargetViews[0] == 0) &&
			_cleared_om.depthStencilView == 0 &&
			_clear_state_restored_om &&
			_clear_state_restored_topology &&
			_clear_state_restored_viewports &&
			_clear_state_saved_rtv_release_ok &&
			_clear_state_saved_dsv_release_ok &&
			_clear_state_cleared_rtv_release_ok &&
			_clear_state_cleared_dsv_release_ok;

		var _immediate_type = id3d11_device_context_get_type(global.__id3d11_context);
		var _immediate_flags = id3d11_device_context_get_context_flags(
			global.__id3d11_context);
		var _deferred_result = id3d11_device_create_deferred_context(
			global.__id3d11_device,
			0);
		var _deferred_type = id3d11_device_context_get_type(_deferred_result.handle);
		var _deferred_flags = id3d11_device_context_get_context_flags(
			_deferred_result.handle);
		var _deferred_topology_set = id3d11_device_context_ia_set_primitive_topology(
			_deferred_result.handle,
			4);
		var _deferred_topology = id3d11_device_context_ia_get_primitive_topology(
			_deferred_result.handle);
		var _command_list_result = id3d11_device_context_finish_command_list(
			_deferred_result.handle,
			false);
		var _command_list_flags = id3d11_command_list_get_context_flags(
			_command_list_result.handle);
		var _command_list_kind = id3d11_handle_get_kind(_command_list_result.handle);
		var _finish_on_immediate_rejected =
			id3d11_device_context_finish_command_list(
				global.__id3d11_context,
				false).hresult != 0;
		var _execute_on_deferred_rejected = !id3d11_device_context_execute_command_list(
			_deferred_result.handle,
			_command_list_result.handle,
			true);
		var _saved_om_for_execute = id3d11_device_context_om_get_render_targets(
			global.__id3d11_context,
			1);
		var _saved_topology_for_execute = id3d11_device_context_ia_get_primitive_topology(
			global.__id3d11_context);
		var _saved_viewports_for_execute = id3d11_device_context_rs_get_viewports(
			global.__id3d11_context);
		var _execute_ok = id3d11_device_context_execute_command_list(
			global.__id3d11_context,
			_command_list_result.handle,
			true);
		var _restore_om_after_execute = id3d11_device_context_om_set_render_targets(
			global.__id3d11_context,
			_saved_om_for_execute.renderTargetViews,
			_saved_om_for_execute.depthStencilView);
		var _restore_topology_after_execute = id3d11_device_context_ia_set_primitive_topology(
			global.__id3d11_context,
			_saved_topology_for_execute);
		var _restore_viewports_after_execute = id3d11_device_context_rs_set_viewports(
			global.__id3d11_context,
			_saved_viewports_for_execute);
		var _saved_execute_rtv = array_length(_saved_om_for_execute.renderTargetViews) > 0
			? _saved_om_for_execute.renderTargetViews[0]
			: 0;
		var _saved_execute_rtv_release_ok =
			_saved_execute_rtv == 0 ||
			id3d11_handle_release(_saved_execute_rtv);
		var _saved_execute_dsv_release_ok =
			_saved_om_for_execute.depthStencilView == 0 ||
			id3d11_handle_release(_saved_om_for_execute.depthStencilView);
		var _command_list_release_ok = id3d11_handle_release(_command_list_result.handle);
		var _deferred_release_ok = id3d11_handle_release(_deferred_result.handle);
		var _deferred_smoke_ok =
			_immediate_type == ID3D11DeviceContextType.Immediate &&
			_immediate_flags == 0 &&
			_deferred_result.hresult == 0 &&
			_deferred_type == ID3D11DeviceContextType.Deferred &&
			_deferred_flags == 0 &&
			_deferred_topology_set &&
			_deferred_topology == 4 &&
			_command_list_result.hresult == 0 &&
			_command_list_kind == ID3D11HandleKind.CommandList &&
			_command_list_flags == 0 &&
			_finish_on_immediate_rejected &&
			_execute_on_deferred_rejected &&
			_execute_ok &&
			_restore_om_after_execute &&
			_restore_topology_after_execute &&
			_restore_viewports_after_execute &&
			_saved_execute_rtv_release_ok &&
			_saved_execute_dsv_release_ok &&
			_command_list_release_ok &&
			_deferred_release_ok;

		global.__id3d11_pipeline_smoke_ok =
			_fixed_pipeline_smoke_ok &&
			_pipeline_binding_smoke_ok &&
			_stage_bindings_smoke_ok &&
			_input_layout_release_ok &&
			_pipeline_predication_set &&
			_bound_predication.predicate == _predicate_result.handle &&
			_bound_predication.predicateValue &&
			_pipeline_invalid_predicate_rejected &&
			_pipeline_predication_restored &&
			_previous_predicate_release_ok &&
			_clear_state_smoke_ok &&
			_deferred_smoke_ok;

		var _async_kinds_ok =
			id3d11_handle_get_kind(_query_result.handle) == ID3D11HandleKind.Query &&
			id3d11_handle_get_kind(_predicate_result.handle) == ID3D11HandleKind.Predicate &&
			(!_counter_supported ||
				id3d11_handle_get_kind(_counter_result.handle) == ID3D11HandleKind.Counter);
		var _async_parent_device = id3d11_device_child_get_device(_query_result.handle);
		var _query_handle = _query_result.handle;
		var _query_release_ok = id3d11_handle_release(_query_result.handle);
		var _predicate_release_ok = id3d11_handle_release(_predicate_result.handle);
		var _counter_release_ok =
			!_counter_supported || id3d11_handle_release(_counter_result.handle);
		global.__id3d11_async_smoke_ok =
			_query_result.hresult == 0 &&
			_query_roundtrip.query == ID3D11Query.Event &&
			_query_roundtrip.miscFlags == 0 &&
			_query_data_size > 0 &&
			_predicate_result.hresult == 0 &&
			_predicate_roundtrip.query == ID3D11Query.OcclusionPredicate &&
			_predicate_roundtrip.miscFlags == ID3D11QueryMiscFlag.PredicateHint &&
			_predicate_data_size > 0 &&
			_invalid_predicate_result.hresult != 0 &&
			_invalid_predicate_result.handle == 0 &&
			_counter_ok &&
			_async_kinds_ok &&
			_async_parent_device == global.__id3d11_device &&
			_query_release_ok &&
			_predicate_release_ok &&
			_counter_release_ok &&
			!id3d11_handle_is_valid(_query_handle);

		global.__id3d11_smoke_ok =
			global.__id3d11_shader_smoke_ok &&
			global.__id3d11_state_smoke_ok &&
			global.__id3d11_async_smoke_ok &&
			global.__id3d11_context_smoke_ok &&
			global.__id3d11_pipeline_smoke_ok &&
			id3d11_is_initialized() &&
			id3d11_handle_is_valid(global.__id3d11_device) &&
			id3d11_handle_is_valid(global.__id3d11_context) &&
			id3d11_handle_is_valid(global.__id3d11_swapchain) &&
			id3d11_handle_get_kind(global.__id3d11_device) == ID3D11HandleKind.Device &&
			id3d11_handle_get_kind(global.__id3d11_context) == ID3D11HandleKind.DeviceContext &&
			id3d11_handle_get_kind(global.__id3d11_swapchain) == ID3D11HandleKind.SwapChain &&
			id3d11_handle_get_kind(_immediate_context) == ID3D11HandleKind.DeviceContext &&
			global.__id3d11_feature_level >= ID3D11FeatureLevel.Level11_0 &&
			id3d11_device_get_removed_reason(global.__id3d11_device) == 0 &&
			_exception_result == 0 &&
			_format_support.hresult == 0 &&
			_format_support.support != 0 &&
			_multisample.hresult == 0 &&
			_multisample.qualityLevels > 0 &&
			_device1_release_ok &&
			_device1_stale_rejected &&
			global.__id3d11_device1 != _device1_stale &&
			id3d11_handle_get_kind(global.__id3d11_device1) == ID3D11HandleKind.Device1 &&
			_buffer_result.hresult == 0 &&
			_buffer_roundtrip.byteWidth == 16 &&
			_buffer_roundtrip.bindFlags == 4 &&
			_buffer_dimension == ID3D11ResourceDimension.Buffer &&
			_buffer_device == global.__id3d11_device &&
			_debug_name_smoke_ok &&
			_buffer_release_ok &&
			_buffer_stale_rejected &&
			_texture1d_result.hresult == 0 &&
			_texture1d_roundtrip.width == 4 &&
			_texture1d_roundtrip.format == 28 &&
			_texture1d_dimension == ID3D11ResourceDimension.Texture1D &&
			_texture1d_release_ok &&
			_texture1d_stale_rejected &&
			_texture2d_result.hresult == 0 &&
			_texture2d_roundtrip.width == 2 &&
			_texture2d_roundtrip.height == 2 &&
			_texture2d_roundtrip.sampleCount == 1 &&
			_texture2d_dimension == ID3D11ResourceDimension.Texture2D &&
			_texture2d_device == global.__id3d11_device &&
			_texture2d_priority_ok &&
			_texture2d_bounds_result.hresult != 0 &&
			_texture2d_bounds_result.handle == 0 &&
			_srv_result.hresult == 0 &&
			_srv_default_result.hresult == 0 &&
			_srv_roundtrip.format == 28 &&
			_srv_roundtrip.viewDimension == ID3D11ShaderResourceViewDimension.Texture2D &&
			_srv_roundtrip.mipLevels == 1 &&
			_srv_resource == _texture2d_result.handle &&
			_srv_kind_ok &&
			_srv_release_ok &&
			_srv_default_release_ok &&
			_rtv_result.hresult == 0 &&
			_rtv_default_result.hresult == 0 &&
			_rtv_roundtrip.format == 28 &&
			_rtv_roundtrip.viewDimension == ID3D11RenderTargetViewDimension.Texture2D &&
			_rtv_resource == _texture2d_result.handle &&
			_rtv_kind_ok &&
			_rtv_release_ok &&
			_rtv_default_release_ok &&
			_uav_result.hresult == 0 &&
			_uav_default_result.hresult == 0 &&
			_uav_roundtrip.format == 28 &&
			_uav_roundtrip.viewDimension == ID3D11UnorderedAccessViewDimension.Texture2D &&
			_uav_resource == _texture2d_result.handle &&
			_uav_kind_ok &&
			_uav_release_ok &&
			_uav_default_release_ok &&
			_depth_texture_result.hresult == 0 &&
			_dsv_result.hresult == 0 &&
			_dsv_default_result.hresult == 0 &&
			_dsv_roundtrip.format == 45 &&
			_dsv_roundtrip.viewDimension == ID3D11DepthStencilViewDimension.Texture2D &&
			_dsv_resource == _depth_texture_result.handle &&
			_dsv_kind_ok &&
			_dsv_release_ok &&
			_dsv_default_release_ok &&
			_depth_texture_release_ok &&
			_texture2d_release_ok &&
			_texture2d_stale_rejected &&
			_texture3d_result.hresult == 0 &&
			_texture3d_roundtrip.width == 2 &&
			_texture3d_roundtrip.height == 2 &&
			_texture3d_roundtrip.depth == 2 &&
			_texture3d_dimension == ID3D11ResourceDimension.Texture3D &&
			_texture3d_release_ok &&
			_texture3d_stale_rejected;
	}
}

show_debug_message(
	$"[ID3D11] bootstrap={global.__id3d11_bootstrap_ok} smoke={global.__id3d11_smoke_ok} shader={global.__id3d11_shader_smoke_ok} state={global.__id3d11_state_smoke_ok} async={global.__id3d11_async_smoke_ok} context={global.__id3d11_context_smoke_ok} pipeline={global.__id3d11_pipeline_smoke_ok} feature_level={global.__id3d11_feature_level}");

// Headless smoke only: do not tear down when running demos/rooms.
// Marker file is reliable if env does not reach Runner through gm-cli.
var _smoke_auto_exit =
	environment_get_variable("ID3D11_SMOKE_AUTO_EXIT") == "1" ||
	file_exists("ID3D11_SMOKE_AUTO_EXIT");
if (_smoke_auto_exit)
{
	if (global.__id3d11_bootstrap_ok)
	{
		id3d11_shutdown();
		global.__id3d11_device = 0;
		global.__id3d11_context = 0;
		global.__id3d11_swapchain = 0;
		global.__id3d11_device1 = 0;
		show_debug_message("[ID3D11] shutdown complete");
	}
	game_end();
}

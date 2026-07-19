// ##### extgen :: Auto-generated file do not edit!! #####

#include "ID3D11Internal_native.h"
#include "ID3D11Internal_exports.h"

using namespace gm_structs;
using namespace gm::wire::codec;

static std::queue<gm::wire::GMBuffer> __buffer_queue;

// Internal function used for queueing buffers to native code
GMEXPORT double __EXT_NATIVE__ID3D11_queue_buffer(char* __arg_buffer, double __arg_buffer_length)
{
    gm::wire::GMBuffer __buff{__arg_buffer, static_cast<uint64_t>(__arg_buffer_length)};
    __buffer_queue.push(__buff);

    return 1.0;
}

GMEXPORT double __EXT_NATIVE__id3d11_get_version(char* __ret_buffer, double __ret_buffer_length)
{
    auto&& __result = id3d11_get_version();
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11Version
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_is_initialized()
{
    auto&& __result = id3d11_is_initialized();
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_shutdown()
{
    id3d11_shutdown();
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_get_last_hresult()
{
    auto&& __result = id3d11_get_last_hresult();
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_get_device_handle(char* __ret_buffer, double __ret_buffer_length)
{
    auto&& __result = id3d11_get_device_handle();
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_get_context_handle(char* __ret_buffer, double __ret_buffer_length)
{
    auto&& __result = id3d11_get_context_handle();
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_get_swapchain_handle(char* __ret_buffer, double __ret_buffer_length)
{
    auto&& __result = id3d11_get_swapchain_handle();
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_handle_query_interface(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: handle, type: UInt64
    std::uint64_t handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: interfaceKind, type: enum ID3D11HandleKind
    gm_enums::ID3D11HandleKind interfaceKind = gm::wire::codec::readValue<gm_enums::ID3D11HandleKind>(__br);

    auto&& __result = id3d11_handle_query_interface(handle, interfaceKind);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_handle_is_valid(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: handle, type: UInt64
    std::uint64_t handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_handle_is_valid(handle);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_handle_get_kind(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: handle, type: UInt64
    std::uint64_t handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_handle_get_kind(handle);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: enum ID3D11HandleKind
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_handle_release(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: handle, type: UInt64
    std::uint64_t handle = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_handle_release(handle);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_get_feature_level(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_get_feature_level(device);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: enum ID3D11FeatureLevel
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_get_creation_flags(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_get_creation_flags(device);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_get_removed_reason(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_get_removed_reason(device);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_get_exception_mode(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_get_exception_mode(device);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_set_exception_mode(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: raiseFlags, type: UInt32
    std::uint32_t raiseFlags = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_set_exception_mode(device, raiseFlags);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_get_immediate_context(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_get_immediate_context(device);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_check_format_support(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: format, type: UInt32
    std::uint32_t format = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_check_format_support(device, format);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11FormatSupportResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_check_multisample_quality_levels(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: format, type: UInt32
    std::uint32_t format = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: sampleCount, type: UInt32
    std::uint32_t sampleCount = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_check_multisample_quality_levels(device, format, sampleCount);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11MultisampleQualityResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_get_counter_info(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_get_counter_info(device);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CounterInfo
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_buffer(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11BufferDesc
    gm_structs::ID3D11BufferDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11BufferDesc>(__br);

    auto&& __result = id3d11_device_create_buffer(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_buffer_with_data(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11BufferDesc
    gm_structs::ID3D11BufferDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11BufferDesc>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = id3d11_device_create_buffer_with_data(device, desc, data);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_buffer_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: bufferHandle, type: UInt64
    std::uint64_t bufferHandle = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_buffer_get_desc(bufferHandle);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11BufferDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_child_get_device(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: deviceChild, type: UInt64
    std::uint64_t deviceChild = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_child_get_device(deviceChild);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_child_set_debug_name(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: deviceChild, type: UInt64
    std::uint64_t deviceChild = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: name, type: String
    std::string_view name = gm::wire::codec::readValue<std::string_view>(__br);

    auto&& __result = id3d11_device_child_set_debug_name(deviceChild, name);
    return static_cast<double>(__result);
}

GMEXPORT char* __EXT_NATIVE__id3d11_device_child_get_debug_name(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: deviceChild, type: UInt64
    std::uint64_t deviceChild = gm::wire::codec::readValue<std::uint64_t>(__br);

    static std::string __result;
    __result = id3d11_device_child_get_debug_name(deviceChild);
    return (char*)__result.c_str();
}

GMEXPORT double __EXT_NATIVE__id3d11_device_child_set_private_data(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: deviceChild, type: UInt64
    std::uint64_t deviceChild = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: guid, type: String
    std::string_view guid = gm::wire::codec::readValue<std::string_view>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = id3d11_device_child_set_private_data(deviceChild, guid, data);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_child_get_private_data(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: deviceChild, type: UInt64
    std::uint64_t deviceChild = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: guid, type: String
    std::string_view guid = gm::wire::codec::readValue<std::string_view>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = id3d11_device_child_get_private_data(deviceChild, guid, data);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_resource_get_dimension(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_resource_get_dimension(resource);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: enum ID3D11ResourceDimension
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_resource_get_eviction_priority(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_resource_get_eviction_priority(resource);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_resource_set_eviction_priority(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: evictionPriority, type: UInt32
    std::uint32_t evictionPriority = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_resource_set_eviction_priority(resource, evictionPriority);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_texture1d(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11Texture1DDesc
    gm_structs::ID3D11Texture1DDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11Texture1DDesc>(__br);

    auto&& __result = id3d11_device_create_texture1d(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_texture1d_with_data(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11Texture1DDesc
    gm_structs::ID3D11Texture1DDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11Texture1DDesc>(__br);

    // field: subresources, type: struct ID3D11SubresourceData[]
    std::vector<gm_structs::ID3D11SubresourceData> subresources = gm::wire::codec::readVector<gm_structs::ID3D11SubresourceData>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = id3d11_device_create_texture1d_with_data(device, desc, subresources, data);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_texture2d(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11Texture2DDesc
    gm_structs::ID3D11Texture2DDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11Texture2DDesc>(__br);

    auto&& __result = id3d11_device_create_texture2d(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_texture2d_with_data(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11Texture2DDesc
    gm_structs::ID3D11Texture2DDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11Texture2DDesc>(__br);

    // field: subresources, type: struct ID3D11SubresourceData[]
    std::vector<gm_structs::ID3D11SubresourceData> subresources = gm::wire::codec::readVector<gm_structs::ID3D11SubresourceData>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = id3d11_device_create_texture2d_with_data(device, desc, subresources, data);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_texture3d(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11Texture3DDesc
    gm_structs::ID3D11Texture3DDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11Texture3DDesc>(__br);

    auto&& __result = id3d11_device_create_texture3d(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_texture3d_with_data(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11Texture3DDesc
    gm_structs::ID3D11Texture3DDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11Texture3DDesc>(__br);

    // field: subresources, type: struct ID3D11SubresourceData[]
    std::vector<gm_structs::ID3D11SubresourceData> subresources = gm::wire::codec::readVector<gm_structs::ID3D11SubresourceData>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = id3d11_device_create_texture3d_with_data(device, desc, subresources, data);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_texture1d_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: texture, type: UInt64
    std::uint64_t texture = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_texture1d_get_desc(texture);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11Texture1DDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_texture2d_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: texture, type: UInt64
    std::uint64_t texture = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_texture2d_get_desc(texture);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11Texture2DDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_texture3d_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: texture, type: UInt64
    std::uint64_t texture = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_texture3d_get_desc(texture);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11Texture3DDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_shader_resource_view_default(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_shader_resource_view_default(device, resource);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_shader_resource_view(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11ShaderResourceViewDesc
    gm_structs::ID3D11ShaderResourceViewDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11ShaderResourceViewDesc>(__br);

    auto&& __result = id3d11_device_create_shader_resource_view(device, resource, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_render_target_view_default(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_render_target_view_default(device, resource);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_render_target_view(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11RenderTargetViewDesc
    gm_structs::ID3D11RenderTargetViewDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11RenderTargetViewDesc>(__br);

    auto&& __result = id3d11_device_create_render_target_view(device, resource, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_depth_stencil_view_default(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_depth_stencil_view_default(device, resource);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_depth_stencil_view(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11DepthStencilViewDesc
    gm_structs::ID3D11DepthStencilViewDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11DepthStencilViewDesc>(__br);

    auto&& __result = id3d11_device_create_depth_stencil_view(device, resource, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_unordered_access_view_default(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_unordered_access_view_default(device, resource);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_unordered_access_view(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11UnorderedAccessViewDesc
    gm_structs::ID3D11UnorderedAccessViewDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11UnorderedAccessViewDesc>(__br);

    auto&& __result = id3d11_device_create_unordered_access_view(device, resource, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_view_get_resource(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: view, type: UInt64
    std::uint64_t view = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_view_get_resource(view);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_shader_resource_view_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: view, type: UInt64
    std::uint64_t view = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_shader_resource_view_get_desc(view);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11ShaderResourceViewDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_render_target_view_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: view, type: UInt64
    std::uint64_t view = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_render_target_view_get_desc(view);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11RenderTargetViewDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_depth_stencil_view_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: view, type: UInt64
    std::uint64_t view = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_depth_stencil_view_get_desc(view);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11DepthStencilViewDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_unordered_access_view_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: view, type: UInt64
    std::uint64_t view = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_unordered_access_view_get_desc(view);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11UnorderedAccessViewDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_compile_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: source, type: String
    std::string_view source = gm::wire::codec::readValue<std::string_view>(__br);

    // field: sourceName, type: String
    std::string_view sourceName = gm::wire::codec::readValue<std::string_view>(__br);

    // field: entryPoint, type: String
    std::string_view entryPoint = gm::wire::codec::readValue<std::string_view>(__br);

    // field: target, type: String
    std::string_view target = gm::wire::codec::readValue<std::string_view>(__br);

    // field: flags1, type: UInt32
    std::uint32_t flags1 = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: flags2, type: UInt32
    std::uint32_t flags2 = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: bytecode, type: Buffer
    gm::wire::GMBuffer bytecode = __buffer_queue.front();
    __buffer_queue.pop();

    // field: errors, type: Buffer
    gm::wire::GMBuffer errors = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = id3d11_compile_shader(source, sourceName, entryPoint, target, flags1, flags2, bytecode, errors);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11ShaderCompileResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_vertex_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: bytecode, type: Buffer
    gm::wire::GMBuffer bytecode = __buffer_queue.front();
    __buffer_queue.pop();

    // field: bytecodeSize, type: UInt64
    std::uint64_t bytecodeSize = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classLinkage, type: UInt64
    std::uint64_t classLinkage = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_vertex_shader(device, bytecode, bytecodeSize, classLinkage);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_hull_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: bytecode, type: Buffer
    gm::wire::GMBuffer bytecode = __buffer_queue.front();
    __buffer_queue.pop();

    // field: bytecodeSize, type: UInt64
    std::uint64_t bytecodeSize = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classLinkage, type: UInt64
    std::uint64_t classLinkage = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_hull_shader(device, bytecode, bytecodeSize, classLinkage);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_domain_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: bytecode, type: Buffer
    gm::wire::GMBuffer bytecode = __buffer_queue.front();
    __buffer_queue.pop();

    // field: bytecodeSize, type: UInt64
    std::uint64_t bytecodeSize = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classLinkage, type: UInt64
    std::uint64_t classLinkage = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_domain_shader(device, bytecode, bytecodeSize, classLinkage);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_geometry_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: bytecode, type: Buffer
    gm::wire::GMBuffer bytecode = __buffer_queue.front();
    __buffer_queue.pop();

    // field: bytecodeSize, type: UInt64
    std::uint64_t bytecodeSize = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classLinkage, type: UInt64
    std::uint64_t classLinkage = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_geometry_shader(device, bytecode, bytecodeSize, classLinkage);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_pixel_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: bytecode, type: Buffer
    gm::wire::GMBuffer bytecode = __buffer_queue.front();
    __buffer_queue.pop();

    // field: bytecodeSize, type: UInt64
    std::uint64_t bytecodeSize = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classLinkage, type: UInt64
    std::uint64_t classLinkage = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_pixel_shader(device, bytecode, bytecodeSize, classLinkage);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_compute_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: bytecode, type: Buffer
    gm::wire::GMBuffer bytecode = __buffer_queue.front();
    __buffer_queue.pop();

    // field: bytecodeSize, type: UInt64
    std::uint64_t bytecodeSize = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classLinkage, type: UInt64
    std::uint64_t classLinkage = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_compute_shader(device, bytecode, bytecodeSize, classLinkage);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_geometry_shader_with_stream_output(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: bytecode, type: Buffer
    gm::wire::GMBuffer bytecode = __buffer_queue.front();
    __buffer_queue.pop();

    // field: bytecodeSize, type: UInt64
    std::uint64_t bytecodeSize = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: declarations, type: struct ID3D11StreamOutputDeclarationEntry[]
    std::vector<gm_structs::ID3D11StreamOutputDeclarationEntry> declarations = gm::wire::codec::readVector<gm_structs::ID3D11StreamOutputDeclarationEntry>(__br);

    // field: bufferStrides, type: UInt32[]
    std::vector<std::uint32_t> bufferStrides = gm::wire::codec::readVector<std::uint32_t>(__br);

    // field: rasterizedStream, type: UInt32
    std::uint32_t rasterizedStream = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: classLinkage, type: UInt64
    std::uint64_t classLinkage = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_geometry_shader_with_stream_output(device, bytecode, bytecodeSize, declarations, bufferStrides, rasterizedStream, classLinkage);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_input_layout(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: elements, type: struct ID3D11InputElementDesc[]
    std::vector<gm_structs::ID3D11InputElementDesc> elements = gm::wire::codec::readVector<gm_structs::ID3D11InputElementDesc>(__br);

    // field: shaderBytecode, type: Buffer
    gm::wire::GMBuffer shaderBytecode = __buffer_queue.front();
    __buffer_queue.pop();

    // field: bytecodeSize, type: UInt64
    std::uint64_t bytecodeSize = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_input_layout(device, elements, shaderBytecode, bytecodeSize);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_class_linkage(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_create_class_linkage(device);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_sampler_state(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11SamplerDesc
    gm_structs::ID3D11SamplerDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11SamplerDesc>(__br);

    auto&& __result = id3d11_device_create_sampler_state(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_sampler_state_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: state, type: UInt64
    std::uint64_t state = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_sampler_state_get_desc(state);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11SamplerDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_rasterizer_state(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11RasterizerDesc
    gm_structs::ID3D11RasterizerDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11RasterizerDesc>(__br);

    auto&& __result = id3d11_device_create_rasterizer_state(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_rasterizer_state_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: state, type: UInt64
    std::uint64_t state = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_rasterizer_state_get_desc(state);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11RasterizerDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_blend_state(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11BlendDesc
    gm_structs::ID3D11BlendDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11BlendDesc>(__br);

    auto&& __result = id3d11_device_create_blend_state(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_blend_state_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: state, type: UInt64
    std::uint64_t state = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_blend_state_get_desc(state);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11BlendDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_depth_stencil_state(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11DepthStencilDesc
    gm_structs::ID3D11DepthStencilDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11DepthStencilDesc>(__br);

    auto&& __result = id3d11_device_create_depth_stencil_state(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_depth_stencil_state_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: state, type: UInt64
    std::uint64_t state = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_depth_stencil_state_get_desc(state);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11DepthStencilDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_query(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11QueryDesc
    gm_structs::ID3D11QueryDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11QueryDesc>(__br);

    auto&& __result = id3d11_device_create_query(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_predicate(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11QueryDesc
    gm_structs::ID3D11QueryDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11QueryDesc>(__br);

    auto&& __result = id3d11_device_create_predicate(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_create_counter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11CounterDesc
    gm_structs::ID3D11CounterDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11CounterDesc>(__br);

    auto&& __result = id3d11_device_create_counter(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_asynchronous_get_data_size(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: asynchronous, type: UInt64
    std::uint64_t asynchronous = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_asynchronous_get_data_size(asynchronous);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_query_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: query, type: UInt64
    std::uint64_t query = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_query_get_desc(query);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11QueryDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_counter_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: counter, type: UInt64
    std::uint64_t counter = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_counter_get_desc(counter);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CounterDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_check_counter(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: device, type: UInt64
    std::uint64_t device = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: desc, type: struct ID3D11CounterDesc
    gm_structs::ID3D11CounterDesc desc = gm::wire::codec::readValue<gm_structs::ID3D11CounterDesc>(__br);

    auto&& __result = id3d11_device_check_counter(device, desc);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CheckCounterResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_begin(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: asynchronous, type: UInt64
    std::uint64_t asynchronous = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_begin(context, asynchronous);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_end(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: asynchronous, type: UInt64
    std::uint64_t asynchronous = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_end(context, asynchronous);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_get_data(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: asynchronous, type: UInt64
    std::uint64_t asynchronous = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: data, type: Buffer
    gm::wire::GMBuffer data = __buffer_queue.front();
    __buffer_queue.pop();

    // field: dataSize, type: UInt64
    std::uint64_t dataSize = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: flags, type: UInt32
    std::uint32_t flags = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_get_data(context, asynchronous, data, dataSize, flags);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_flush(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_flush(context);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_clear_state(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_clear_state(context);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_draw_indexed(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: indexCount, type: UInt32
    std::uint32_t indexCount = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: startIndexLocation, type: UInt32
    std::uint32_t startIndexLocation = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: baseVertexLocation, type: Int32
    std::int32_t baseVertexLocation = gm::wire::codec::readValue<std::int32_t>(__br);

    auto&& __result = id3d11_device_context_draw_indexed(context, indexCount, startIndexLocation, baseVertexLocation);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_draw(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: vertexCount, type: UInt32
    std::uint32_t vertexCount = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: startVertexLocation, type: UInt32
    std::uint32_t startVertexLocation = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_draw(context, vertexCount, startVertexLocation);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_draw_indexed_instanced(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: indexCountPerInstance, type: UInt32
    std::uint32_t indexCountPerInstance = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: instanceCount, type: UInt32
    std::uint32_t instanceCount = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: startIndexLocation, type: UInt32
    std::uint32_t startIndexLocation = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: baseVertexLocation, type: Int32
    std::int32_t baseVertexLocation = gm::wire::codec::readValue<std::int32_t>(__br);

    // field: startInstanceLocation, type: UInt32
    std::uint32_t startInstanceLocation = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_draw_indexed_instanced(context, indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_draw_instanced(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: vertexCountPerInstance, type: UInt32
    std::uint32_t vertexCountPerInstance = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: instanceCount, type: UInt32
    std::uint32_t instanceCount = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: startVertexLocation, type: UInt32
    std::uint32_t startVertexLocation = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: startInstanceLocation, type: UInt32
    std::uint32_t startInstanceLocation = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_draw_instanced(context, vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_draw_auto(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_draw_auto(context);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_draw_indexed_instanced_indirect(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: argumentBuffer, type: UInt64
    std::uint64_t argumentBuffer = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: alignedByteOffset, type: UInt32
    std::uint32_t alignedByteOffset = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_draw_indexed_instanced_indirect(context, argumentBuffer, alignedByteOffset);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_draw_instanced_indirect(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: argumentBuffer, type: UInt64
    std::uint64_t argumentBuffer = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: alignedByteOffset, type: UInt32
    std::uint32_t alignedByteOffset = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_draw_instanced_indirect(context, argumentBuffer, alignedByteOffset);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_dispatch(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: threadGroupCountX, type: UInt32
    std::uint32_t threadGroupCountX = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: threadGroupCountY, type: UInt32
    std::uint32_t threadGroupCountY = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: threadGroupCountZ, type: UInt32
    std::uint32_t threadGroupCountZ = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_dispatch(context, threadGroupCountX, threadGroupCountY, threadGroupCountZ);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_dispatch_indirect(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: argumentBuffer, type: UInt64
    std::uint64_t argumentBuffer = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: alignedByteOffset, type: UInt32
    std::uint32_t alignedByteOffset = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_dispatch_indirect(context, argumentBuffer, alignedByteOffset);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_copy_subresource_region(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destinationResource, type: UInt64
    std::uint64_t destinationResource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destinationSubresource, type: UInt32
    std::uint32_t destinationSubresource = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: destinationX, type: UInt32
    std::uint32_t destinationX = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: destinationY, type: UInt32
    std::uint32_t destinationY = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: destinationZ, type: UInt32
    std::uint32_t destinationZ = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: sourceResource, type: UInt64
    std::uint64_t sourceResource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: sourceSubresource, type: UInt32
    std::uint32_t sourceSubresource = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: useSourceBox, type: Bool
    bool useSourceBox = gm::wire::codec::readValue<bool>(__br);

    // field: sourceBox, type: struct ID3D11Box
    gm_structs::ID3D11Box sourceBox = gm::wire::codec::readValue<gm_structs::ID3D11Box>(__br);

    auto&& __result = id3d11_device_context_copy_subresource_region(context, destinationResource, destinationSubresource, destinationX, destinationY, destinationZ, sourceResource, sourceSubresource, useSourceBox, sourceBox);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_copy_resource(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destinationResource, type: UInt64
    std::uint64_t destinationResource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: sourceResource, type: UInt64
    std::uint64_t sourceResource = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_copy_resource(context, destinationResource, sourceResource);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_update_subresource(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destinationResource, type: UInt64
    std::uint64_t destinationResource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destinationSubresource, type: UInt32
    std::uint32_t destinationSubresource = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: useDestinationBox, type: Bool
    bool useDestinationBox = gm::wire::codec::readValue<bool>(__br);

    // field: destinationBox, type: struct ID3D11Box
    gm_structs::ID3D11Box destinationBox = gm::wire::codec::readValue<gm_structs::ID3D11Box>(__br);

    // field: sourceData, type: Buffer
    gm::wire::GMBuffer sourceData = __buffer_queue.front();
    __buffer_queue.pop();

    // field: sourceOffset, type: UInt64
    std::uint64_t sourceOffset = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: sourceLength, type: UInt64
    std::uint64_t sourceLength = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: sourceRowPitch, type: UInt32
    std::uint32_t sourceRowPitch = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: sourceDepthPitch, type: UInt32
    std::uint32_t sourceDepthPitch = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_update_subresource(context, destinationResource, destinationSubresource, useDestinationBox, destinationBox, sourceData, sourceOffset, sourceLength, sourceRowPitch, sourceDepthPitch);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_map_read_to_buffer(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: subresource, type: UInt32
    std::uint32_t subresource = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: mapType, type: enum ID3D11Map
    gm_enums::ID3D11Map mapType = gm::wire::codec::readValue<gm_enums::ID3D11Map>(__br);

    // field: mapFlags, type: UInt32
    std::uint32_t mapFlags = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: destinationData, type: Buffer
    gm::wire::GMBuffer destinationData = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = id3d11_device_context_map_read_to_buffer(context, resource, subresource, mapType, mapFlags, destinationData);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_map_write_from_buffer(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: subresource, type: UInt32
    std::uint32_t subresource = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: mapType, type: enum ID3D11Map
    gm_enums::ID3D11Map mapType = gm::wire::codec::readValue<gm_enums::ID3D11Map>(__br);

    // field: mapFlags, type: UInt32
    std::uint32_t mapFlags = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: sourceData, type: Buffer
    gm::wire::GMBuffer sourceData = __buffer_queue.front();
    __buffer_queue.pop();

    auto&& __result = id3d11_device_context_map_write_from_buffer(context, resource, subresource, mapType, mapFlags, sourceData);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_copy_structure_count(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destinationBuffer, type: UInt64
    std::uint64_t destinationBuffer = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destinationAlignedByteOffset, type: UInt32
    std::uint32_t destinationAlignedByteOffset = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: sourceView, type: UInt64
    std::uint64_t sourceView = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_copy_structure_count(context, destinationBuffer, destinationAlignedByteOffset, sourceView);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_clear_render_target_view(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: renderTargetView, type: UInt64
    std::uint64_t renderTargetView = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: red, type: Float32
    float red = gm::wire::codec::readValue<float>(__br);

    // field: green, type: Float32
    float green = gm::wire::codec::readValue<float>(__br);

    // field: blue, type: Float32
    float blue = gm::wire::codec::readValue<float>(__br);

    // field: alpha, type: Float32
    float alpha = gm::wire::codec::readValue<float>(__br);

    auto&& __result = id3d11_device_context_clear_render_target_view(context, renderTargetView, red, green, blue, alpha);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_clear_unordered_access_view_uint(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: unorderedAccessView, type: UInt64
    std::uint64_t unorderedAccessView = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value0, type: UInt32
    std::uint32_t value0 = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: value1, type: UInt32
    std::uint32_t value1 = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: value2, type: UInt32
    std::uint32_t value2 = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: value3, type: UInt32
    std::uint32_t value3 = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_clear_unordered_access_view_uint(context, unorderedAccessView, value0, value1, value2, value3);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_clear_unordered_access_view_float(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: unorderedAccessView, type: UInt64
    std::uint64_t unorderedAccessView = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: value0, type: Float32
    float value0 = gm::wire::codec::readValue<float>(__br);

    // field: value1, type: Float32
    float value1 = gm::wire::codec::readValue<float>(__br);

    // field: value2, type: Float32
    float value2 = gm::wire::codec::readValue<float>(__br);

    // field: value3, type: Float32
    float value3 = gm::wire::codec::readValue<float>(__br);

    auto&& __result = id3d11_device_context_clear_unordered_access_view_float(context, unorderedAccessView, value0, value1, value2, value3);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_clear_depth_stencil_view(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: depthStencilView, type: UInt64
    std::uint64_t depthStencilView = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: clearFlags, type: UInt32
    std::uint32_t clearFlags = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: depth, type: Float32
    float depth = gm::wire::codec::readValue<float>(__br);

    // field: stencil, type: UInt32
    std::uint32_t stencil = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_clear_depth_stencil_view(context, depthStencilView, clearFlags, depth, stencil);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_generate_mips(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: shaderResourceView, type: UInt64
    std::uint64_t shaderResourceView = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_generate_mips(context, shaderResourceView);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_set_resource_min_lod(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: minimumLod, type: Float32
    float minimumLod = gm::wire::codec::readValue<float>(__br);

    auto&& __result = id3d11_device_context_set_resource_min_lod(context, resource, minimumLod);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_get_resource_min_lod(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: resource, type: UInt64
    std::uint64_t resource = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_get_resource_min_lod(context, resource);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_resolve_subresource(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destinationResource, type: UInt64
    std::uint64_t destinationResource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: destinationSubresource, type: UInt32
    std::uint32_t destinationSubresource = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: sourceResource, type: UInt64
    std::uint64_t sourceResource = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: sourceSubresource, type: UInt32
    std::uint32_t sourceSubresource = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: format, type: UInt32
    std::uint32_t format = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_resolve_subresource(context, destinationResource, destinationSubresource, sourceResource, sourceSubresource, format);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ia_set_input_layout(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: inputLayout, type: UInt64
    std::uint64_t inputLayout = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ia_set_input_layout(context, inputLayout);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ia_get_input_layout(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ia_get_input_layout(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ia_set_primitive_topology(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: topology, type: enum ID3D11PrimitiveTopology
    gm_enums::ID3D11PrimitiveTopology topology = gm::wire::codec::readValue<gm_enums::ID3D11PrimitiveTopology>(__br);

    auto&& __result = id3d11_device_context_ia_set_primitive_topology(context, topology);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ia_get_primitive_topology(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ia_get_primitive_topology(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: enum ID3D11PrimitiveTopology
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_rs_set_state(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: state, type: UInt64
    std::uint64_t state = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_rs_set_state(context, state);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_rs_get_state(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_rs_get_state(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_om_set_blend_state(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: state, type: UInt64
    std::uint64_t state = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: blendFactor, type: Float32[]
    std::vector<float> blendFactor = gm::wire::codec::readVector<float>(__br);

    // field: sampleMask, type: UInt32
    std::uint32_t sampleMask = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_om_set_blend_state(context, state, blendFactor, sampleMask);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_om_get_blend_state(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_om_get_blend_state(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11BlendStateBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_om_set_depth_stencil_state(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: state, type: UInt64
    std::uint64_t state = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: stencilRef, type: UInt32
    std::uint32_t stencilRef = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_om_set_depth_stencil_state(context, state, stencilRef);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_om_get_depth_stencil_state(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_om_get_depth_stencil_state(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11DepthStencilStateBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_om_set_render_targets(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: renderTargetViews, type: UInt64[]
    std::vector<std::uint64_t> renderTargetViews = gm::wire::codec::readVector<std::uint64_t>(__br);

    // field: depthStencilView, type: UInt64
    std::uint64_t depthStencilView = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_om_set_render_targets(context, renderTargetViews, depthStencilView);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_om_get_render_targets(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_om_get_render_targets(context, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11OutputMergerTargets
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_om_set_render_targets_and_unordered_access_views(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: keepRenderTargets, type: Bool
    bool keepRenderTargets = gm::wire::codec::readValue<bool>(__br);

    // field: renderTargetViews, type: UInt64[]
    std::vector<std::uint64_t> renderTargetViews = gm::wire::codec::readVector<std::uint64_t>(__br);

    // field: depthStencilView, type: UInt64
    std::uint64_t depthStencilView = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: uavStartSlot, type: UInt32
    std::uint32_t uavStartSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: keepUnorderedAccessViews, type: Bool
    bool keepUnorderedAccessViews = gm::wire::codec::readValue<bool>(__br);

    // field: unorderedAccessViews, type: struct ID3D11UnorderedAccessViewBinding[]
    std::vector<gm_structs::ID3D11UnorderedAccessViewBinding> unorderedAccessViews = gm::wire::codec::readVector<gm_structs::ID3D11UnorderedAccessViewBinding>(__br);

    auto&& __result = id3d11_device_context_om_set_render_targets_and_unordered_access_views(context, keepRenderTargets, renderTargetViews, depthStencilView, uavStartSlot, keepUnorderedAccessViews, unorderedAccessViews);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_om_get_render_targets_and_unordered_access_views(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: renderTargetCount, type: UInt32
    std::uint32_t renderTargetCount = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: uavStartSlot, type: UInt32
    std::uint32_t uavStartSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: uavCount, type: UInt32
    std::uint32_t uavCount = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_om_get_render_targets_and_unordered_access_views(context, renderTargetCount, uavStartSlot, uavCount);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11OutputMergerTargetsAndUAVs
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_so_set_targets(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: targets, type: struct ID3D11StreamOutputTarget[]
    std::vector<gm_structs::ID3D11StreamOutputTarget> targets = gm::wire::codec::readVector<gm_structs::ID3D11StreamOutputTarget>(__br);

    auto&& __result = id3d11_device_context_so_set_targets(context, targets);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_so_get_targets(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_so_get_targets(context, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_set_unordered_access_views(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: views, type: struct ID3D11UnorderedAccessViewBinding[]
    std::vector<gm_structs::ID3D11UnorderedAccessViewBinding> views = gm::wire::codec::readVector<gm_structs::ID3D11UnorderedAccessViewBinding>(__br);

    auto&& __result = id3d11_device_context_cs_set_unordered_access_views(context, startSlot, views);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_get_unordered_access_views(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_cs_get_unordered_access_views(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_set_predication(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: predicate, type: UInt64
    std::uint64_t predicate = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: predicateValue, type: Bool
    bool predicateValue = gm::wire::codec::readValue<bool>(__br);

    auto&& __result = id3d11_device_context_set_predication(context, predicate, predicateValue);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_get_predication(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_get_predication(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11PredicationBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ia_set_vertex_buffers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: bindings, type: struct ID3D11VertexBufferBinding[]
    std::vector<gm_structs::ID3D11VertexBufferBinding> bindings = gm::wire::codec::readVector<gm_structs::ID3D11VertexBufferBinding>(__br);

    auto&& __result = id3d11_device_context_ia_set_vertex_buffers(context, startSlot, bindings);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ia_get_vertex_buffers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_ia_get_vertex_buffers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11VertexBufferBinding[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ia_set_index_buffer(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: buffer, type: UInt64
    std::uint64_t buffer = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: format, type: UInt32
    std::uint32_t format = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: offset, type: UInt32
    std::uint32_t offset = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_ia_set_index_buffer(context, buffer, format, offset);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ia_get_index_buffer(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ia_get_index_buffer(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11IndexBufferBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_rs_set_viewports(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: viewports, type: struct ID3D11Viewport[]
    std::vector<gm_structs::ID3D11Viewport> viewports = gm::wire::codec::readVector<gm_structs::ID3D11Viewport>(__br);

    auto&& __result = id3d11_device_context_rs_set_viewports(context, viewports);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_rs_get_viewports(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_rs_get_viewports(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11Viewport[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_rs_set_scissor_rects(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: rects, type: struct ID3D11Rect[]
    std::vector<gm_structs::ID3D11Rect> rects = gm::wire::codec::readVector<gm_structs::ID3D11Rect>(__br);

    auto&& __result = id3d11_device_context_rs_set_scissor_rects(context, rects);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_rs_get_scissor_rects(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_rs_get_scissor_rects(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11Rect[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_vs_set_constant_buffers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: buffers, type: UInt64[]
    std::vector<std::uint64_t> buffers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_vs_set_constant_buffers(context, startSlot, buffers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_vs_get_constant_buffers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_vs_get_constant_buffers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_vs_set_shader_resources(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: views, type: UInt64[]
    std::vector<std::uint64_t> views = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_vs_set_shader_resources(context, startSlot, views);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_vs_get_shader_resources(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_vs_get_shader_resources(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_vs_set_samplers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: samplers, type: UInt64[]
    std::vector<std::uint64_t> samplers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_vs_set_samplers(context, startSlot, samplers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_vs_get_samplers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_vs_get_samplers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_hs_set_constant_buffers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: buffers, type: UInt64[]
    std::vector<std::uint64_t> buffers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_hs_set_constant_buffers(context, startSlot, buffers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_hs_get_constant_buffers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_hs_get_constant_buffers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_hs_set_shader_resources(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: views, type: UInt64[]
    std::vector<std::uint64_t> views = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_hs_set_shader_resources(context, startSlot, views);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_hs_get_shader_resources(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_hs_get_shader_resources(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_hs_set_samplers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: samplers, type: UInt64[]
    std::vector<std::uint64_t> samplers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_hs_set_samplers(context, startSlot, samplers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_hs_get_samplers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_hs_get_samplers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ds_set_constant_buffers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: buffers, type: UInt64[]
    std::vector<std::uint64_t> buffers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ds_set_constant_buffers(context, startSlot, buffers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ds_get_constant_buffers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_ds_get_constant_buffers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ds_set_shader_resources(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: views, type: UInt64[]
    std::vector<std::uint64_t> views = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ds_set_shader_resources(context, startSlot, views);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ds_get_shader_resources(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_ds_get_shader_resources(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ds_set_samplers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: samplers, type: UInt64[]
    std::vector<std::uint64_t> samplers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ds_set_samplers(context, startSlot, samplers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ds_get_samplers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_ds_get_samplers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_gs_set_constant_buffers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: buffers, type: UInt64[]
    std::vector<std::uint64_t> buffers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_gs_set_constant_buffers(context, startSlot, buffers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_gs_get_constant_buffers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_gs_get_constant_buffers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_gs_set_shader_resources(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: views, type: UInt64[]
    std::vector<std::uint64_t> views = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_gs_set_shader_resources(context, startSlot, views);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_gs_get_shader_resources(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_gs_get_shader_resources(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_gs_set_samplers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: samplers, type: UInt64[]
    std::vector<std::uint64_t> samplers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_gs_set_samplers(context, startSlot, samplers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_gs_get_samplers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_gs_get_samplers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ps_set_constant_buffers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: buffers, type: UInt64[]
    std::vector<std::uint64_t> buffers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ps_set_constant_buffers(context, startSlot, buffers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ps_get_constant_buffers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_ps_get_constant_buffers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ps_set_shader_resources(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: views, type: UInt64[]
    std::vector<std::uint64_t> views = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ps_set_shader_resources(context, startSlot, views);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ps_get_shader_resources(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_ps_get_shader_resources(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ps_set_samplers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: samplers, type: UInt64[]
    std::vector<std::uint64_t> samplers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ps_set_samplers(context, startSlot, samplers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ps_get_samplers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_ps_get_samplers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_set_constant_buffers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: buffers, type: UInt64[]
    std::vector<std::uint64_t> buffers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_cs_set_constant_buffers(context, startSlot, buffers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_get_constant_buffers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_cs_get_constant_buffers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_set_shader_resources(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: views, type: UInt64[]
    std::vector<std::uint64_t> views = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_cs_set_shader_resources(context, startSlot, views);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_get_shader_resources(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_cs_get_shader_resources(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_set_samplers(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: samplers, type: UInt64[]
    std::vector<std::uint64_t> samplers = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_cs_set_samplers(context, startSlot, samplers);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_get_samplers(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: startSlot, type: UInt32
    std::uint32_t startSlot = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: count, type: UInt32
    std::uint32_t count = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_device_context_cs_get_samplers(context, startSlot, count);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64[]
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_vs_set_shader(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: shader, type: UInt64
    std::uint64_t shader = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classInstances, type: UInt64[]
    std::vector<std::uint64_t> classInstances = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_vs_set_shader(context, shader, classInstances);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_vs_get_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_vs_get_shader(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11ShaderBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_hs_set_shader(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: shader, type: UInt64
    std::uint64_t shader = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classInstances, type: UInt64[]
    std::vector<std::uint64_t> classInstances = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_hs_set_shader(context, shader, classInstances);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_hs_get_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_hs_get_shader(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11ShaderBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ds_set_shader(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: shader, type: UInt64
    std::uint64_t shader = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classInstances, type: UInt64[]
    std::vector<std::uint64_t> classInstances = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ds_set_shader(context, shader, classInstances);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ds_get_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ds_get_shader(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11ShaderBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_gs_set_shader(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: shader, type: UInt64
    std::uint64_t shader = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classInstances, type: UInt64[]
    std::vector<std::uint64_t> classInstances = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_gs_set_shader(context, shader, classInstances);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_gs_get_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_gs_get_shader(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11ShaderBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ps_set_shader(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: shader, type: UInt64
    std::uint64_t shader = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classInstances, type: UInt64[]
    std::vector<std::uint64_t> classInstances = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ps_set_shader(context, shader, classInstances);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_ps_get_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_ps_get_shader(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11ShaderBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_set_shader(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: shader, type: UInt64
    std::uint64_t shader = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classInstances, type: UInt64[]
    std::vector<std::uint64_t> classInstances = gm::wire::codec::readVector<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_cs_set_shader(context, shader, classInstances);
    return static_cast<double>(__result);
}

GMEXPORT double __EXT_NATIVE__id3d11_device_context_cs_get_shader(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: context, type: UInt64
    std::uint64_t context = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_device_context_cs_get_shader(context);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11ShaderBinding
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_class_linkage_get_class_instance(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: linkage, type: UInt64
    std::uint64_t linkage = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classInstanceName, type: String
    std::string_view classInstanceName = gm::wire::codec::readValue<std::string_view>(__br);

    // field: instanceIndex, type: UInt32
    std::uint32_t instanceIndex = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_class_linkage_get_class_instance(linkage, classInstanceName, instanceIndex);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_class_linkage_create_class_instance(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: linkage, type: UInt64
    std::uint64_t linkage = gm::wire::codec::readValue<std::uint64_t>(__br);

    // field: classTypeName, type: String
    std::string_view classTypeName = gm::wire::codec::readValue<std::string_view>(__br);

    // field: constantBufferOffset, type: UInt32
    std::uint32_t constantBufferOffset = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: constantVectorOffset, type: UInt32
    std::uint32_t constantVectorOffset = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: textureOffset, type: UInt32
    std::uint32_t textureOffset = gm::wire::codec::readValue<std::uint32_t>(__br);

    // field: samplerOffset, type: UInt32
    std::uint32_t samplerOffset = gm::wire::codec::readValue<std::uint32_t>(__br);

    auto&& __result = id3d11_class_linkage_create_class_instance(linkage, classTypeName, constantBufferOffset, constantVectorOffset, textureOffset, samplerOffset);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11CreateHandleResult
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_class_instance_get_class_linkage(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: instance, type: UInt64
    std::uint64_t instance = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_class_instance_get_class_linkage(instance);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: UInt64
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT double __EXT_NATIVE__id3d11_class_instance_get_desc(char* __arg_buffer, double __arg_buffer_length, char* __ret_buffer, double __ret_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: instance, type: UInt64
    std::uint64_t instance = gm::wire::codec::readValue<std::uint64_t>(__br);

    auto&& __result = id3d11_class_instance_get_desc(instance);
    gm::byteio::BufferWriter __bw{__ret_buffer, static_cast<size_t>(__ret_buffer_length)};

    // return: __result, type: struct ID3D11ClassInstanceDesc
    gm::wire::codec::writeValue(__bw, __result);
    return 0;
}

GMEXPORT char* __EXT_NATIVE__id3d11_class_instance_get_instance_name(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: instance, type: UInt64
    std::uint64_t instance = gm::wire::codec::readValue<std::uint64_t>(__br);

    static std::string __result;
    __result = id3d11_class_instance_get_instance_name(instance);
    return (char*)__result.c_str();
}

GMEXPORT char* __EXT_NATIVE__id3d11_class_instance_get_type_name(char* __arg_buffer, double __arg_buffer_length)
{
    gm::byteio::BufferReader __br{__arg_buffer, static_cast<size_t>(__arg_buffer_length)};

    // field: instance, type: UInt64
    std::uint64_t instance = gm::wire::codec::readValue<std::uint64_t>(__br);

    static std::string __result;
    __result = id3d11_class_instance_get_type_name(instance);
    return (char*)__result.c_str();
}


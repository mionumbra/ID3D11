cmake_minimum_required(VERSION 3.25)

project(ID3D11DynamicLinkageProbe LANGUAGES CXX)

add_executable(ID3D11DynamicLinkageProbe dynamic_linkage_probe.cpp)
target_compile_features(ID3D11DynamicLinkageProbe PRIVATE cxx_std_20)
target_compile_options(ID3D11DynamicLinkageProbe PRIVATE /W4 /permissive- /utf-8)
target_compile_definitions(ID3D11DynamicLinkageProbe PRIVATE
    WIN32_LEAN_AND_MEAN
    NOMINMAX)
target_link_libraries(ID3D11DynamicLinkageProbe PRIVATE d3d11 dxgi d3dcompiler)

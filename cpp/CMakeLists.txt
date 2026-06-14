cmake_minimum_required(VERSION 3.23)

project(GMD3D11)

set(CMAKE_CXX_STANDARD 17)

add_library(GMD3D11 SHARED
    # Buffers
    src/buffers/Buffer.cpp
    src/buffers/ComputeBuffer.cpp
    src/buffers/ConstantBuffer.cpp
    src/buffers/ReadbackBuffer.cpp
    src/buffers/StructuredBuffer.cpp
    src/buffers/VertexBuffer.cpp
    src/buffers/IndexBuffer.cpp
    src/buffers/RawBuffer.cpp
    src/buffers/UploadBuffer.cpp
    src/buffers/AppendConsumeBuffer.cpp
    src/buffers/IndirectArgsBuffer.cpp

    # Shaders
    src/shaders/Shader.cpp
    src/shaders/VertexShader.cpp
    src/shaders/PixelShader.cpp
    src/shaders/GeometryShader.cpp
    src/shaders/ComputeShader.cpp
    src/shaders/HullShader.cpp
    src/shaders/DomainShader.cpp

    # Textures
    src/textures/Sampler.cpp
    src/textures/Texture2D.cpp
    src/textures/Texture3D.cpp
    src/textures/TextureArray.cpp

    # Views
    src/views/DSV.cpp
    src/views/RTV.cpp
    src/views/SRV.cpp
    src/views/UAV.cpp

    # Pipeline control
    src/pipeline/Viewport.cpp
    src/pipeline/ScissorRect.cpp
    src/pipeline/OcclusionQuery.cpp
    src/pipeline/TimestampQuery.cpp

    # Core
    src/main.cpp
    src/utils.cpp
)

target_include_directories(GMD3D11 PRIVATE
    include/
)

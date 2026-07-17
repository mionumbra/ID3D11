// ##### extgen :: Auto-generated file do not edit!! #####

#pragma once
#include <cstdint>
#include <string_view>
#include <vector>
#include <array>
#include <optional>
#include "core/GMExtWire.h"

namespace gm_consts
{
}


namespace gm_enums
{
    enum class ID3D11HandleKind : std::uint32_t
    {
        Invalid = 0,
        Device = 1,
        DeviceContext = 2,
        SwapChain = 3,
        Buffer = 4,
        Texture1D = 5,
        Texture2D = 6,
        Texture3D = 7,
        Shader = 8,
        View = 9,
        State = 10,
        Query = 11,
        CommandList = 12,
        Fence = 13,
        Device1 = 14,
        Device2 = 15,
        Device3 = 16,
        Device4 = 17,
        Device5 = 18,
        DeviceContext1 = 19,
        DeviceContext2 = 20,
        DeviceContext3 = 21,
        DeviceContext4 = 22,
        Multithread = 23,
        DeviceChild = 24,
        Resource = 25,
        Texture2D1 = 26,
        Texture3D1 = 27,
        ShaderResourceView = 28,
        ShaderResourceView1 = 29,
        RenderTargetView = 30,
        RenderTargetView1 = 31,
        DepthStencilView = 32,
        UnorderedAccessView = 33,
        UnorderedAccessView1 = 34,
        VertexShader = 35,
        HullShader = 36,
        DomainShader = 37,
        GeometryShader = 38,
        PixelShader = 39,
        ComputeShader = 40,
        InputLayout = 41,
        SamplerState = 42,
        DepthStencilState = 43,
        BlendState = 44,
        BlendState1 = 45,
        RasterizerState = 46,
        RasterizerState1 = 47,
        RasterizerState2 = 48,
        Asynchronous = 49,
        Predicate = 50,
        Counter = 51,
        Query1 = 52,
        ClassInstance = 53,
        ClassLinkage = 54,
        VideoDecoder = 55,
        VideoProcessorEnumerator = 56,
        VideoProcessorEnumerator1 = 57,
        VideoProcessor = 58,
        AuthenticatedChannel = 59,
        CryptoSession = 60,
        VideoDecoderOutputView = 61,
        VideoProcessorInputView = 62,
        VideoProcessorOutputView = 63,
        VideoContext = 64,
        VideoContext1 = 65,
        VideoContext2 = 66,
        VideoContext3 = 67,
        VideoDevice = 68,
        VideoDevice1 = 69,
        VideoDevice2 = 70
    };

    enum class ID3D11FeatureLevel : std::uint32_t
    {
        Level9_1 = 37120,
        Level9_2 = 37376,
        Level9_3 = 37632,
        Level10_0 = 40960,
        Level10_1 = 41216,
        Level11_0 = 45056,
        Level11_1 = 45312,
        Level12_0 = 49152,
        Level12_1 = 49408,
        Level12_2 = 49664
    };

    enum class ID3D11Usage : std::uint32_t
    {
        Default = 0,
        Immutable = 1,
        Dynamic = 2,
        Staging = 3
    };

    enum class ID3D11BindFlag : std::uint32_t
    {
        VertexBuffer = 1,
        IndexBuffer = 2,
        ConstantBuffer = 4,
        ShaderResource = 8,
        StreamOutput = 16,
        RenderTarget = 32,
        DepthStencil = 64,
        UnorderedAccess = 128,
        Decoder = 512,
        VideoEncoder = 1024
    };

    enum class ID3D11CpuAccessFlag : std::uint32_t
    {
        Write = 65536,
        Read = 131072
    };

    enum class ID3D11ResourceMiscFlag : std::uint32_t
    {
        GenerateMips = 1,
        Shared = 2,
        TextureCube = 4,
        DrawIndirectArgs = 16,
        BufferAllowRawViews = 32,
        BufferStructured = 64,
        ResourceClamp = 128,
        SharedKeyedMutex = 256,
        GdiCompatible = 512,
        SharedNtHandle = 2048,
        RestrictedContent = 4096,
        RestrictSharedResource = 8192,
        RestrictSharedResourceDriver = 16384,
        Guarded = 32768,
        TilePool = 131072,
        Tiled = 262144,
        HardwareProtected = 524288,
        SharedDisplayable = 1048576,
        SharedExclusiveWriter = 2097152,
        NoShaderAccess = 4194304
    };

    enum class ID3D11BufferUavFlag : std::uint32_t
    {
        Raw = 1,
        Append = 2,
        Counter = 4
    };

    enum class ID3D11ClearFlag : std::uint32_t
    {
        Depth = 1,
        Stencil = 2
    };

    enum class ID3D11ResourceDimension : std::uint32_t
    {
        Unknown = 0,
        Buffer = 1,
        Texture1D = 2,
        Texture2D = 3,
        Texture3D = 4
    };

    enum class ID3D11ShaderResourceViewDimension : std::uint32_t
    {
        Unknown = 0,
        Buffer = 1,
        Texture1D = 2,
        Texture1DArray = 3,
        Texture2D = 4,
        Texture2DArray = 5,
        Texture2DMS = 6,
        Texture2DMSArray = 7,
        Texture3D = 8,
        TextureCube = 9,
        TextureCubeArray = 10,
        BufferEx = 11
    };

    enum class ID3D11RenderTargetViewDimension : std::uint32_t
    {
        Unknown = 0,
        Buffer = 1,
        Texture1D = 2,
        Texture1DArray = 3,
        Texture2D = 4,
        Texture2DArray = 5,
        Texture2DMS = 6,
        Texture2DMSArray = 7,
        Texture3D = 8
    };

    enum class ID3D11DepthStencilViewDimension : std::uint32_t
    {
        Unknown = 0,
        Texture1D = 1,
        Texture1DArray = 2,
        Texture2D = 3,
        Texture2DArray = 4,
        Texture2DMS = 5,
        Texture2DMSArray = 6
    };

    enum class ID3D11UnorderedAccessViewDimension : std::uint32_t
    {
        Unknown = 0,
        Buffer = 1,
        Texture1D = 2,
        Texture1DArray = 3,
        Texture2D = 4,
        Texture2DArray = 5,
        Texture3D = 8
    };

    enum class ID3D11InputClassification : std::uint32_t
    {
        PerVertexData = 0,
        PerInstanceData = 1
    };

    enum class ID3D11Filter : std::uint32_t
    {
        MinMagMipPoint = 0,
        MinMagPointMipLinear = 1,
        MinPointMagLinearMipPoint = 4,
        MinPointMagMipLinear = 5,
        MinLinearMagMipPoint = 16,
        MinLinearMagPointMipLinear = 17,
        MinMagLinearMipPoint = 20,
        MinMagMipLinear = 21,
        Anisotropic = 85,
        ComparisonMinMagMipPoint = 128,
        ComparisonMinMagPointMipLinear = 129,
        ComparisonMinPointMagLinearMipPoint = 132,
        ComparisonMinPointMagMipLinear = 133,
        ComparisonMinLinearMagMipPoint = 144,
        ComparisonMinLinearMagPointMipLinear = 145,
        ComparisonMinMagLinearMipPoint = 148,
        ComparisonMinMagMipLinear = 149,
        ComparisonAnisotropic = 213,
        MinimumMinMagMipPoint = 256,
        MinimumMinMagPointMipLinear = 257,
        MinimumMinPointMagLinearMipPoint = 260,
        MinimumMinPointMagMipLinear = 261,
        MinimumMinLinearMagMipPoint = 272,
        MinimumMinLinearMagPointMipLinear = 273,
        MinimumMinMagLinearMipPoint = 276,
        MinimumMinMagMipLinear = 277,
        MinimumAnisotropic = 341,
        MaximumMinMagMipPoint = 384,
        MaximumMinMagPointMipLinear = 385,
        MaximumMinPointMagLinearMipPoint = 388,
        MaximumMinPointMagMipLinear = 389,
        MaximumMinLinearMagMipPoint = 400,
        MaximumMinLinearMagPointMipLinear = 401,
        MaximumMinMagLinearMipPoint = 404,
        MaximumMinMagMipLinear = 405,
        MaximumAnisotropic = 469
    };

    enum class ID3D11TextureAddressMode : std::uint32_t
    {
        Wrap = 1,
        Mirror = 2,
        Clamp = 3,
        Border = 4,
        MirrorOnce = 5
    };

    enum class ID3D11ComparisonFunc : std::uint32_t
    {
        Never = 1,
        Less = 2,
        Equal = 3,
        LessEqual = 4,
        Greater = 5,
        NotEqual = 6,
        GreaterEqual = 7,
        Always = 8
    };

    enum class ID3D11FillMode : std::uint32_t
    {
        Wireframe = 2,
        Solid = 3
    };

    enum class ID3D11CullMode : std::uint32_t
    {
        None = 1,
        Front = 2,
        Back = 3
    };

    enum class ID3D11Blend : std::uint32_t
    {
        Zero = 1,
        One = 2,
        SrcColor = 3,
        InvSrcColor = 4,
        SrcAlpha = 5,
        InvSrcAlpha = 6,
        DestAlpha = 7,
        InvDestAlpha = 8,
        DestColor = 9,
        InvDestColor = 10,
        SrcAlphaSat = 11,
        BlendFactor = 14,
        InvBlendFactor = 15,
        Src1Color = 16,
        InvSrc1Color = 17,
        Src1Alpha = 18,
        InvSrc1Alpha = 19
    };

    enum class ID3D11BlendOp : std::uint32_t
    {
        Add = 1,
        Subtract = 2,
        RevSubtract = 3,
        Min = 4,
        Max = 5
    };

    enum class ID3D11ColorWriteEnable : std::uint32_t
    {
        Red = 1,
        Green = 2,
        Blue = 4,
        Alpha = 8,
        All = 15
    };

    enum class ID3D11DepthWriteMask : std::uint32_t
    {
        Zero = 0,
        All = 1
    };

    enum class ID3D11StencilOp : std::uint32_t
    {
        Keep = 1,
        Zero = 2,
        Replace = 3,
        IncrSat = 4,
        DecrSat = 5,
        Invert = 6,
        Incr = 7,
        Decr = 8
    };

    enum class ID3D11Query : std::uint32_t
    {
        Event = 0,
        Occlusion = 1,
        Timestamp = 2,
        TimestampDisjoint = 3,
        PipelineStatistics = 4,
        OcclusionPredicate = 5,
        StreamOutputStatistics = 6,
        StreamOutputOverflowPredicate = 7,
        StreamOutputStatisticsStream0 = 8,
        StreamOutputOverflowPredicateStream0 = 9,
        StreamOutputStatisticsStream1 = 10,
        StreamOutputOverflowPredicateStream1 = 11,
        StreamOutputStatisticsStream2 = 12,
        StreamOutputOverflowPredicateStream2 = 13,
        StreamOutputStatisticsStream3 = 14,
        StreamOutputOverflowPredicateStream3 = 15
    };

    enum class ID3D11QueryMiscFlag : std::uint32_t
    {
        PredicateHint = 1
    };

    enum class ID3D11AsyncGetDataFlag : std::uint32_t
    {
        DoNotFlush = 1
    };

    enum class ID3D11Counter : std::uint32_t
    {
        DeviceDependent0 = 1073741824
    };

    enum class ID3D11CounterType : std::uint32_t
    {
        Float32 = 0,
        Uint16 = 1,
        Uint32 = 2,
        Uint64 = 3
    };

    enum class ID3D11PrimitiveTopology : std::uint32_t
    {
        Undefined = 0,
        PointList = 1,
        LineList = 2,
        LineStrip = 3,
        TriangleList = 4,
        TriangleStrip = 5,
        LineListAdjacency = 10,
        LineStripAdjacency = 11,
        TriangleListAdjacency = 12,
        TriangleStripAdjacency = 13,
        PatchList1 = 33,
        PatchList2 = 34,
        PatchList3 = 35,
        PatchList4 = 36,
        PatchList5 = 37,
        PatchList6 = 38,
        PatchList7 = 39,
        PatchList8 = 40,
        PatchList9 = 41,
        PatchList10 = 42,
        PatchList11 = 43,
        PatchList12 = 44,
        PatchList13 = 45,
        PatchList14 = 46,
        PatchList15 = 47,
        PatchList16 = 48,
        PatchList17 = 49,
        PatchList18 = 50,
        PatchList19 = 51,
        PatchList20 = 52,
        PatchList21 = 53,
        PatchList22 = 54,
        PatchList23 = 55,
        PatchList24 = 56,
        PatchList25 = 57,
        PatchList26 = 58,
        PatchList27 = 59,
        PatchList28 = 60,
        PatchList29 = 61,
        PatchList30 = 62,
        PatchList31 = 63,
        PatchList32 = 64
    };

}


namespace gm_structs
{
    struct ID3D11Version;
    struct ID3D11FormatSupportResult;
    struct ID3D11MultisampleQualityResult;
    struct ID3D11CounterInfo;
    struct ID3D11BufferDesc;
    struct ID3D11SubresourceData;
    struct ID3D11Texture1DDesc;
    struct ID3D11Texture2DDesc;
    struct ID3D11Texture3DDesc;
    struct ID3D11ShaderResourceViewDesc;
    struct ID3D11RenderTargetViewDesc;
    struct ID3D11DepthStencilViewDesc;
    struct ID3D11UnorderedAccessViewDesc;
    struct ID3D11InputElementDesc;
    struct ID3D11StreamOutputDeclarationEntry;
    struct ID3D11ShaderCompileResult;
    struct ID3D11SamplerDesc;
    struct ID3D11RasterizerDesc;
    struct ID3D11RenderTargetBlendDesc;
    struct ID3D11DepthStencilOpDesc;
    struct ID3D11QueryDesc;
    struct ID3D11CounterDesc;
    struct ID3D11CheckCounterResult;
    struct ID3D11BlendStateBinding;
    struct ID3D11DepthStencilStateBinding;
    struct ID3D11PredicationBinding;
    struct ID3D11VertexBufferBinding;
    struct ID3D11IndexBufferBinding;
    struct ID3D11Viewport;
    struct ID3D11Rect;
    struct ID3D11Box;
    struct ID3D11ShaderBinding;
    struct ID3D11ClassInstanceDesc;
    struct ID3D11CreateHandleResult;
    struct ID3D11BlendDesc;
    struct ID3D11DepthStencilDesc;

    struct ID3D11Version
    {
        std::uint32_t major;
        std::uint32_t minor;
        std::uint32_t patch;
        std::uint32_t abi;
    };

    struct ID3D11FormatSupportResult
    {
        std::int32_t hresult;
        std::uint32_t support;
    };

    struct ID3D11MultisampleQualityResult
    {
        std::int32_t hresult;
        std::uint32_t qualityLevels;
    };

    struct ID3D11CounterInfo
    {
        std::uint32_t lastDeviceDependentCounter;
        std::uint32_t numSimultaneousCounters;
        std::uint32_t numDetectableParallelUnits;
    };

    struct ID3D11BufferDesc
    {
        std::uint32_t byteWidth;
        std::uint32_t usage;
        std::uint32_t bindFlags;
        std::uint32_t cpuAccessFlags;
        std::uint32_t miscFlags;
        std::uint32_t structureByteStride;
    };

    struct ID3D11SubresourceData
    {
        std::uint64_t offset;
        std::uint32_t rowPitch;
        std::uint32_t slicePitch;
        std::uint64_t dataSize;
    };

    struct ID3D11Texture1DDesc
    {
        std::uint32_t width;
        std::uint32_t mipLevels;
        std::uint32_t arraySize;
        std::uint32_t format;
        std::uint32_t usage;
        std::uint32_t bindFlags;
        std::uint32_t cpuAccessFlags;
        std::uint32_t miscFlags;
    };

    struct ID3D11Texture2DDesc
    {
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t mipLevels;
        std::uint32_t arraySize;
        std::uint32_t format;
        std::uint32_t sampleCount;
        std::uint32_t sampleQuality;
        std::uint32_t usage;
        std::uint32_t bindFlags;
        std::uint32_t cpuAccessFlags;
        std::uint32_t miscFlags;
    };

    struct ID3D11Texture3DDesc
    {
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t depth;
        std::uint32_t mipLevels;
        std::uint32_t format;
        std::uint32_t usage;
        std::uint32_t bindFlags;
        std::uint32_t cpuAccessFlags;
        std::uint32_t miscFlags;
    };

    struct ID3D11ShaderResourceViewDesc
    {
        std::uint32_t format;
        std::uint32_t viewDimension;
        std::uint32_t firstElement;
        std::uint32_t numElements;
        std::uint32_t flags;
        std::uint32_t mostDetailedMip;
        std::uint32_t mipLevels;
        std::uint32_t firstArraySlice;
        std::uint32_t arraySize;
        std::uint32_t first2DArrayFace;
        std::uint32_t numCubes;
    };

    struct ID3D11RenderTargetViewDesc
    {
        std::uint32_t format;
        std::uint32_t viewDimension;
        std::uint32_t firstElement;
        std::uint32_t numElements;
        std::uint32_t mipSlice;
        std::uint32_t firstArraySlice;
        std::uint32_t arraySize;
        std::uint32_t firstWSlice;
        std::uint32_t wSize;
    };

    struct ID3D11DepthStencilViewDesc
    {
        std::uint32_t format;
        std::uint32_t viewDimension;
        std::uint32_t flags;
        std::uint32_t mipSlice;
        std::uint32_t firstArraySlice;
        std::uint32_t arraySize;
    };

    struct ID3D11UnorderedAccessViewDesc
    {
        std::uint32_t format;
        std::uint32_t viewDimension;
        std::uint32_t firstElement;
        std::uint32_t numElements;
        std::uint32_t flags;
        std::uint32_t mipSlice;
        std::uint32_t firstArraySlice;
        std::uint32_t arraySize;
        std::uint32_t firstWSlice;
        std::uint32_t wSize;
    };

    struct ID3D11InputElementDesc
    {
        std::string semanticName;
        std::uint32_t semanticIndex;
        std::uint32_t format;
        std::uint32_t inputSlot;
        std::uint32_t alignedByteOffset;
        std::uint32_t inputSlotClass;
        std::uint32_t instanceDataStepRate;
    };

    struct ID3D11StreamOutputDeclarationEntry
    {
        std::string semanticName;
        std::uint32_t stream;
        std::uint32_t semanticIndex;
        std::uint32_t startComponent;
        std::uint32_t componentCount;
        std::uint32_t outputSlot;
    };

    struct ID3D11ShaderCompileResult
    {
        std::int32_t hresult;
        std::uint64_t bytecodeSize;
        std::uint64_t errorSize;
    };

    struct ID3D11SamplerDesc
    {
        std::uint32_t filter;
        std::uint32_t addressU;
        std::uint32_t addressV;
        std::uint32_t addressW;
        float mipLodBias;
        std::uint32_t maxAnisotropy;
        std::uint32_t comparisonFunc;
        float borderColorR;
        float borderColorG;
        float borderColorB;
        float borderColorA;
        float minLod;
        float maxLod;
    };

    struct ID3D11RasterizerDesc
    {
        std::uint32_t fillMode;
        std::uint32_t cullMode;
        bool frontCounterClockwise;
        std::int32_t depthBias;
        float depthBiasClamp;
        float slopeScaledDepthBias;
        bool depthClipEnable;
        bool scissorEnable;
        bool multisampleEnable;
        bool antialiasedLineEnable;
    };

    struct ID3D11RenderTargetBlendDesc
    {
        bool blendEnable;
        std::uint32_t srcBlend;
        std::uint32_t destBlend;
        std::uint32_t blendOp;
        std::uint32_t srcBlendAlpha;
        std::uint32_t destBlendAlpha;
        std::uint32_t blendOpAlpha;
        std::uint32_t renderTargetWriteMask;
    };

    struct ID3D11DepthStencilOpDesc
    {
        std::uint32_t stencilFailOp;
        std::uint32_t stencilDepthFailOp;
        std::uint32_t stencilPassOp;
        std::uint32_t stencilFunc;
    };

    struct ID3D11QueryDesc
    {
        std::uint32_t query;
        std::uint32_t miscFlags;
    };

    struct ID3D11CounterDesc
    {
        std::uint32_t counter;
        std::uint32_t miscFlags;
    };

    struct ID3D11CheckCounterResult
    {
        std::int32_t hresult;
        std::uint32_t type;
        std::uint32_t activeCounters;
        std::string name;
        std::string units;
        std::string description;
    };

    struct ID3D11BlendStateBinding
    {
        std::uint64_t state;
        std::vector<float> blendFactor;
        std::uint32_t sampleMask;
    };

    struct ID3D11DepthStencilStateBinding
    {
        std::uint64_t state;
        std::uint32_t stencilRef;
    };

    struct ID3D11PredicationBinding
    {
        std::uint64_t predicate;
        bool predicateValue;
    };

    struct ID3D11VertexBufferBinding
    {
        std::uint64_t buffer;
        std::uint32_t stride;
        std::uint32_t offset;
    };

    struct ID3D11IndexBufferBinding
    {
        std::uint64_t buffer;
        std::uint32_t format;
        std::uint32_t offset;
    };

    struct ID3D11Viewport
    {
        float topLeftX;
        float topLeftY;
        float width;
        float height;
        float minDepth;
        float maxDepth;
    };

    struct ID3D11Rect
    {
        std::int32_t left;
        std::int32_t top;
        std::int32_t right;
        std::int32_t bottom;
    };

    struct ID3D11Box
    {
        std::uint32_t left;
        std::uint32_t top;
        std::uint32_t front;
        std::uint32_t right;
        std::uint32_t bottom;
        std::uint32_t back;
    };

    struct ID3D11ShaderBinding
    {
        std::uint64_t shader;
        std::vector<std::uint64_t> classInstances;
    };

    struct ID3D11ClassInstanceDesc
    {
        std::uint32_t instanceId;
        std::uint32_t instanceIndex;
        std::uint32_t typeId;
        std::uint32_t constantBuffer;
        std::uint32_t baseConstantBufferOffset;
        std::uint32_t baseTexture;
        std::uint32_t baseSampler;
        bool created;
    };

    struct ID3D11CreateHandleResult
    {
        std::int32_t hresult;
        std::uint64_t handle;
    };

    struct ID3D11BlendDesc
    {
        bool alphaToCoverageEnable;
        bool independentBlendEnable;
        std::vector<gm_structs::ID3D11RenderTargetBlendDesc> renderTargets;
    };

    struct ID3D11DepthStencilDesc
    {
        bool depthEnable;
        std::uint32_t depthWriteMask;
        std::uint32_t depthFunc;
        bool stencilEnable;
        std::uint32_t stencilReadMask;
        std::uint32_t stencilWriteMask;
        gm_structs::ID3D11DepthStencilOpDesc frontFace;
        gm_structs::ID3D11DepthStencilOpDesc backFace;
    };

}

namespace gm::wire::codec
{
    template<>
    inline void writeValue<gm_structs::ID3D11Version>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11Version& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.major);
        gm::wire::codec::writeValue(_buf, obj.minor);
        gm::wire::codec::writeValue(_buf, obj.patch);
        gm::wire::codec::writeValue(_buf, obj.abi);
    }

    template<>
    inline gm_structs::ID3D11Version readValue<gm_structs::ID3D11Version>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11Version obj;
        obj.major = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.minor = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.patch = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.abi = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11FormatSupportResult>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11FormatSupportResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.hresult);
        gm::wire::codec::writeValue(_buf, obj.support);
    }

    template<>
    inline gm_structs::ID3D11FormatSupportResult readValue<gm_structs::ID3D11FormatSupportResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11FormatSupportResult obj;
        obj.hresult = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.support = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11MultisampleQualityResult>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11MultisampleQualityResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.hresult);
        gm::wire::codec::writeValue(_buf, obj.qualityLevels);
    }

    template<>
    inline gm_structs::ID3D11MultisampleQualityResult readValue<gm_structs::ID3D11MultisampleQualityResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11MultisampleQualityResult obj;
        obj.hresult = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.qualityLevels = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11CounterInfo>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11CounterInfo& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.lastDeviceDependentCounter);
        gm::wire::codec::writeValue(_buf, obj.numSimultaneousCounters);
        gm::wire::codec::writeValue(_buf, obj.numDetectableParallelUnits);
    }

    template<>
    inline gm_structs::ID3D11CounterInfo readValue<gm_structs::ID3D11CounterInfo>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11CounterInfo obj;
        obj.lastDeviceDependentCounter = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.numSimultaneousCounters = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.numDetectableParallelUnits = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11BufferDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11BufferDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.byteWidth);
        gm::wire::codec::writeValue(_buf, obj.usage);
        gm::wire::codec::writeValue(_buf, obj.bindFlags);
        gm::wire::codec::writeValue(_buf, obj.cpuAccessFlags);
        gm::wire::codec::writeValue(_buf, obj.miscFlags);
        gm::wire::codec::writeValue(_buf, obj.structureByteStride);
    }

    template<>
    inline gm_structs::ID3D11BufferDesc readValue<gm_structs::ID3D11BufferDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11BufferDesc obj;
        obj.byteWidth = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.usage = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.bindFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.cpuAccessFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.miscFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.structureByteStride = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11SubresourceData>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11SubresourceData& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.offset);
        gm::wire::codec::writeValue(_buf, obj.rowPitch);
        gm::wire::codec::writeValue(_buf, obj.slicePitch);
        gm::wire::codec::writeValue(_buf, obj.dataSize);
    }

    template<>
    inline gm_structs::ID3D11SubresourceData readValue<gm_structs::ID3D11SubresourceData>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11SubresourceData obj;
        obj.offset = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.rowPitch = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.slicePitch = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.dataSize = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11Texture1DDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11Texture1DDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.width);
        gm::wire::codec::writeValue(_buf, obj.mipLevels);
        gm::wire::codec::writeValue(_buf, obj.arraySize);
        gm::wire::codec::writeValue(_buf, obj.format);
        gm::wire::codec::writeValue(_buf, obj.usage);
        gm::wire::codec::writeValue(_buf, obj.bindFlags);
        gm::wire::codec::writeValue(_buf, obj.cpuAccessFlags);
        gm::wire::codec::writeValue(_buf, obj.miscFlags);
    }

    template<>
    inline gm_structs::ID3D11Texture1DDesc readValue<gm_structs::ID3D11Texture1DDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11Texture1DDesc obj;
        obj.width = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.mipLevels = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.arraySize = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.format = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.usage = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.bindFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.cpuAccessFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.miscFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11Texture2DDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11Texture2DDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.width);
        gm::wire::codec::writeValue(_buf, obj.height);
        gm::wire::codec::writeValue(_buf, obj.mipLevels);
        gm::wire::codec::writeValue(_buf, obj.arraySize);
        gm::wire::codec::writeValue(_buf, obj.format);
        gm::wire::codec::writeValue(_buf, obj.sampleCount);
        gm::wire::codec::writeValue(_buf, obj.sampleQuality);
        gm::wire::codec::writeValue(_buf, obj.usage);
        gm::wire::codec::writeValue(_buf, obj.bindFlags);
        gm::wire::codec::writeValue(_buf, obj.cpuAccessFlags);
        gm::wire::codec::writeValue(_buf, obj.miscFlags);
    }

    template<>
    inline gm_structs::ID3D11Texture2DDesc readValue<gm_structs::ID3D11Texture2DDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11Texture2DDesc obj;
        obj.width = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.height = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.mipLevels = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.arraySize = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.format = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.sampleCount = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.sampleQuality = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.usage = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.bindFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.cpuAccessFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.miscFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11Texture3DDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11Texture3DDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.width);
        gm::wire::codec::writeValue(_buf, obj.height);
        gm::wire::codec::writeValue(_buf, obj.depth);
        gm::wire::codec::writeValue(_buf, obj.mipLevels);
        gm::wire::codec::writeValue(_buf, obj.format);
        gm::wire::codec::writeValue(_buf, obj.usage);
        gm::wire::codec::writeValue(_buf, obj.bindFlags);
        gm::wire::codec::writeValue(_buf, obj.cpuAccessFlags);
        gm::wire::codec::writeValue(_buf, obj.miscFlags);
    }

    template<>
    inline gm_structs::ID3D11Texture3DDesc readValue<gm_structs::ID3D11Texture3DDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11Texture3DDesc obj;
        obj.width = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.height = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.depth = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.mipLevels = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.format = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.usage = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.bindFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.cpuAccessFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.miscFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11ShaderResourceViewDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11ShaderResourceViewDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.format);
        gm::wire::codec::writeValue(_buf, obj.viewDimension);
        gm::wire::codec::writeValue(_buf, obj.firstElement);
        gm::wire::codec::writeValue(_buf, obj.numElements);
        gm::wire::codec::writeValue(_buf, obj.flags);
        gm::wire::codec::writeValue(_buf, obj.mostDetailedMip);
        gm::wire::codec::writeValue(_buf, obj.mipLevels);
        gm::wire::codec::writeValue(_buf, obj.firstArraySlice);
        gm::wire::codec::writeValue(_buf, obj.arraySize);
        gm::wire::codec::writeValue(_buf, obj.first2DArrayFace);
        gm::wire::codec::writeValue(_buf, obj.numCubes);
    }

    template<>
    inline gm_structs::ID3D11ShaderResourceViewDesc readValue<gm_structs::ID3D11ShaderResourceViewDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11ShaderResourceViewDesc obj;
        obj.format = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.viewDimension = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.firstElement = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.numElements = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.flags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.mostDetailedMip = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.mipLevels = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.firstArraySlice = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.arraySize = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.first2DArrayFace = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.numCubes = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11RenderTargetViewDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11RenderTargetViewDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.format);
        gm::wire::codec::writeValue(_buf, obj.viewDimension);
        gm::wire::codec::writeValue(_buf, obj.firstElement);
        gm::wire::codec::writeValue(_buf, obj.numElements);
        gm::wire::codec::writeValue(_buf, obj.mipSlice);
        gm::wire::codec::writeValue(_buf, obj.firstArraySlice);
        gm::wire::codec::writeValue(_buf, obj.arraySize);
        gm::wire::codec::writeValue(_buf, obj.firstWSlice);
        gm::wire::codec::writeValue(_buf, obj.wSize);
    }

    template<>
    inline gm_structs::ID3D11RenderTargetViewDesc readValue<gm_structs::ID3D11RenderTargetViewDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11RenderTargetViewDesc obj;
        obj.format = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.viewDimension = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.firstElement = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.numElements = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.mipSlice = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.firstArraySlice = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.arraySize = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.firstWSlice = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.wSize = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11DepthStencilViewDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11DepthStencilViewDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.format);
        gm::wire::codec::writeValue(_buf, obj.viewDimension);
        gm::wire::codec::writeValue(_buf, obj.flags);
        gm::wire::codec::writeValue(_buf, obj.mipSlice);
        gm::wire::codec::writeValue(_buf, obj.firstArraySlice);
        gm::wire::codec::writeValue(_buf, obj.arraySize);
    }

    template<>
    inline gm_structs::ID3D11DepthStencilViewDesc readValue<gm_structs::ID3D11DepthStencilViewDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11DepthStencilViewDesc obj;
        obj.format = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.viewDimension = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.flags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.mipSlice = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.firstArraySlice = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.arraySize = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11UnorderedAccessViewDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11UnorderedAccessViewDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.format);
        gm::wire::codec::writeValue(_buf, obj.viewDimension);
        gm::wire::codec::writeValue(_buf, obj.firstElement);
        gm::wire::codec::writeValue(_buf, obj.numElements);
        gm::wire::codec::writeValue(_buf, obj.flags);
        gm::wire::codec::writeValue(_buf, obj.mipSlice);
        gm::wire::codec::writeValue(_buf, obj.firstArraySlice);
        gm::wire::codec::writeValue(_buf, obj.arraySize);
        gm::wire::codec::writeValue(_buf, obj.firstWSlice);
        gm::wire::codec::writeValue(_buf, obj.wSize);
    }

    template<>
    inline gm_structs::ID3D11UnorderedAccessViewDesc readValue<gm_structs::ID3D11UnorderedAccessViewDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11UnorderedAccessViewDesc obj;
        obj.format = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.viewDimension = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.firstElement = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.numElements = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.flags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.mipSlice = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.firstArraySlice = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.arraySize = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.firstWSlice = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.wSize = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11InputElementDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11InputElementDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.semanticName);
        gm::wire::codec::writeValue(_buf, obj.semanticIndex);
        gm::wire::codec::writeValue(_buf, obj.format);
        gm::wire::codec::writeValue(_buf, obj.inputSlot);
        gm::wire::codec::writeValue(_buf, obj.alignedByteOffset);
        gm::wire::codec::writeValue(_buf, obj.inputSlotClass);
        gm::wire::codec::writeValue(_buf, obj.instanceDataStepRate);
    }

    template<>
    inline gm_structs::ID3D11InputElementDesc readValue<gm_structs::ID3D11InputElementDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11InputElementDesc obj;
        obj.semanticName = gm::wire::codec::readValue<std::string>(_buf);
        obj.semanticIndex = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.format = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.inputSlot = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.alignedByteOffset = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.inputSlotClass = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.instanceDataStepRate = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11StreamOutputDeclarationEntry>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11StreamOutputDeclarationEntry& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.semanticName);
        gm::wire::codec::writeValue(_buf, obj.stream);
        gm::wire::codec::writeValue(_buf, obj.semanticIndex);
        gm::wire::codec::writeValue(_buf, obj.startComponent);
        gm::wire::codec::writeValue(_buf, obj.componentCount);
        gm::wire::codec::writeValue(_buf, obj.outputSlot);
    }

    template<>
    inline gm_structs::ID3D11StreamOutputDeclarationEntry readValue<gm_structs::ID3D11StreamOutputDeclarationEntry>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11StreamOutputDeclarationEntry obj;
        obj.semanticName = gm::wire::codec::readValue<std::string>(_buf);
        obj.stream = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.semanticIndex = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.startComponent = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.componentCount = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.outputSlot = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11ShaderCompileResult>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11ShaderCompileResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.hresult);
        gm::wire::codec::writeValue(_buf, obj.bytecodeSize);
        gm::wire::codec::writeValue(_buf, obj.errorSize);
    }

    template<>
    inline gm_structs::ID3D11ShaderCompileResult readValue<gm_structs::ID3D11ShaderCompileResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11ShaderCompileResult obj;
        obj.hresult = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.bytecodeSize = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.errorSize = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11SamplerDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11SamplerDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.filter);
        gm::wire::codec::writeValue(_buf, obj.addressU);
        gm::wire::codec::writeValue(_buf, obj.addressV);
        gm::wire::codec::writeValue(_buf, obj.addressW);
        gm::wire::codec::writeValue(_buf, obj.mipLodBias);
        gm::wire::codec::writeValue(_buf, obj.maxAnisotropy);
        gm::wire::codec::writeValue(_buf, obj.comparisonFunc);
        gm::wire::codec::writeValue(_buf, obj.borderColorR);
        gm::wire::codec::writeValue(_buf, obj.borderColorG);
        gm::wire::codec::writeValue(_buf, obj.borderColorB);
        gm::wire::codec::writeValue(_buf, obj.borderColorA);
        gm::wire::codec::writeValue(_buf, obj.minLod);
        gm::wire::codec::writeValue(_buf, obj.maxLod);
    }

    template<>
    inline gm_structs::ID3D11SamplerDesc readValue<gm_structs::ID3D11SamplerDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11SamplerDesc obj;
        obj.filter = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.addressU = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.addressV = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.addressW = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.mipLodBias = gm::wire::codec::readValue<float>(_buf);
        obj.maxAnisotropy = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.comparisonFunc = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.borderColorR = gm::wire::codec::readValue<float>(_buf);
        obj.borderColorG = gm::wire::codec::readValue<float>(_buf);
        obj.borderColorB = gm::wire::codec::readValue<float>(_buf);
        obj.borderColorA = gm::wire::codec::readValue<float>(_buf);
        obj.minLod = gm::wire::codec::readValue<float>(_buf);
        obj.maxLod = gm::wire::codec::readValue<float>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11RasterizerDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11RasterizerDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.fillMode);
        gm::wire::codec::writeValue(_buf, obj.cullMode);
        gm::wire::codec::writeValue(_buf, obj.frontCounterClockwise);
        gm::wire::codec::writeValue(_buf, obj.depthBias);
        gm::wire::codec::writeValue(_buf, obj.depthBiasClamp);
        gm::wire::codec::writeValue(_buf, obj.slopeScaledDepthBias);
        gm::wire::codec::writeValue(_buf, obj.depthClipEnable);
        gm::wire::codec::writeValue(_buf, obj.scissorEnable);
        gm::wire::codec::writeValue(_buf, obj.multisampleEnable);
        gm::wire::codec::writeValue(_buf, obj.antialiasedLineEnable);
    }

    template<>
    inline gm_structs::ID3D11RasterizerDesc readValue<gm_structs::ID3D11RasterizerDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11RasterizerDesc obj;
        obj.fillMode = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.cullMode = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.frontCounterClockwise = gm::wire::codec::readValue<bool>(_buf);
        obj.depthBias = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.depthBiasClamp = gm::wire::codec::readValue<float>(_buf);
        obj.slopeScaledDepthBias = gm::wire::codec::readValue<float>(_buf);
        obj.depthClipEnable = gm::wire::codec::readValue<bool>(_buf);
        obj.scissorEnable = gm::wire::codec::readValue<bool>(_buf);
        obj.multisampleEnable = gm::wire::codec::readValue<bool>(_buf);
        obj.antialiasedLineEnable = gm::wire::codec::readValue<bool>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11RenderTargetBlendDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11RenderTargetBlendDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.blendEnable);
        gm::wire::codec::writeValue(_buf, obj.srcBlend);
        gm::wire::codec::writeValue(_buf, obj.destBlend);
        gm::wire::codec::writeValue(_buf, obj.blendOp);
        gm::wire::codec::writeValue(_buf, obj.srcBlendAlpha);
        gm::wire::codec::writeValue(_buf, obj.destBlendAlpha);
        gm::wire::codec::writeValue(_buf, obj.blendOpAlpha);
        gm::wire::codec::writeValue(_buf, obj.renderTargetWriteMask);
    }

    template<>
    inline gm_structs::ID3D11RenderTargetBlendDesc readValue<gm_structs::ID3D11RenderTargetBlendDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11RenderTargetBlendDesc obj;
        obj.blendEnable = gm::wire::codec::readValue<bool>(_buf);
        obj.srcBlend = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.destBlend = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.blendOp = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.srcBlendAlpha = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.destBlendAlpha = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.blendOpAlpha = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.renderTargetWriteMask = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11DepthStencilOpDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11DepthStencilOpDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.stencilFailOp);
        gm::wire::codec::writeValue(_buf, obj.stencilDepthFailOp);
        gm::wire::codec::writeValue(_buf, obj.stencilPassOp);
        gm::wire::codec::writeValue(_buf, obj.stencilFunc);
    }

    template<>
    inline gm_structs::ID3D11DepthStencilOpDesc readValue<gm_structs::ID3D11DepthStencilOpDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11DepthStencilOpDesc obj;
        obj.stencilFailOp = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.stencilDepthFailOp = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.stencilPassOp = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.stencilFunc = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11QueryDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11QueryDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.query);
        gm::wire::codec::writeValue(_buf, obj.miscFlags);
    }

    template<>
    inline gm_structs::ID3D11QueryDesc readValue<gm_structs::ID3D11QueryDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11QueryDesc obj;
        obj.query = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.miscFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11CounterDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11CounterDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.counter);
        gm::wire::codec::writeValue(_buf, obj.miscFlags);
    }

    template<>
    inline gm_structs::ID3D11CounterDesc readValue<gm_structs::ID3D11CounterDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11CounterDesc obj;
        obj.counter = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.miscFlags = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11CheckCounterResult>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11CheckCounterResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.hresult);
        gm::wire::codec::writeValue(_buf, obj.type);
        gm::wire::codec::writeValue(_buf, obj.activeCounters);
        gm::wire::codec::writeValue(_buf, obj.name);
        gm::wire::codec::writeValue(_buf, obj.units);
        gm::wire::codec::writeValue(_buf, obj.description);
    }

    template<>
    inline gm_structs::ID3D11CheckCounterResult readValue<gm_structs::ID3D11CheckCounterResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11CheckCounterResult obj;
        obj.hresult = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.type = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.activeCounters = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.name = gm::wire::codec::readValue<std::string>(_buf);
        obj.units = gm::wire::codec::readValue<std::string>(_buf);
        obj.description = gm::wire::codec::readValue<std::string>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11BlendStateBinding>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11BlendStateBinding& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.state);
        gm::wire::codec::writeValue(_buf, obj.blendFactor);
        gm::wire::codec::writeValue(_buf, obj.sampleMask);
    }

    template<>
    inline gm_structs::ID3D11BlendStateBinding readValue<gm_structs::ID3D11BlendStateBinding>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11BlendStateBinding obj;
        obj.state = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.blendFactor = gm::wire::codec::readVector<float>(_buf);
        obj.sampleMask = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11DepthStencilStateBinding>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11DepthStencilStateBinding& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.state);
        gm::wire::codec::writeValue(_buf, obj.stencilRef);
    }

    template<>
    inline gm_structs::ID3D11DepthStencilStateBinding readValue<gm_structs::ID3D11DepthStencilStateBinding>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11DepthStencilStateBinding obj;
        obj.state = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.stencilRef = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11PredicationBinding>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11PredicationBinding& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.predicate);
        gm::wire::codec::writeValue(_buf, obj.predicateValue);
    }

    template<>
    inline gm_structs::ID3D11PredicationBinding readValue<gm_structs::ID3D11PredicationBinding>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11PredicationBinding obj;
        obj.predicate = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.predicateValue = gm::wire::codec::readValue<bool>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11VertexBufferBinding>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11VertexBufferBinding& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.buffer);
        gm::wire::codec::writeValue(_buf, obj.stride);
        gm::wire::codec::writeValue(_buf, obj.offset);
    }

    template<>
    inline gm_structs::ID3D11VertexBufferBinding readValue<gm_structs::ID3D11VertexBufferBinding>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11VertexBufferBinding obj;
        obj.buffer = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.stride = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.offset = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11IndexBufferBinding>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11IndexBufferBinding& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.buffer);
        gm::wire::codec::writeValue(_buf, obj.format);
        gm::wire::codec::writeValue(_buf, obj.offset);
    }

    template<>
    inline gm_structs::ID3D11IndexBufferBinding readValue<gm_structs::ID3D11IndexBufferBinding>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11IndexBufferBinding obj;
        obj.buffer = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.format = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.offset = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11Viewport>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11Viewport& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.topLeftX);
        gm::wire::codec::writeValue(_buf, obj.topLeftY);
        gm::wire::codec::writeValue(_buf, obj.width);
        gm::wire::codec::writeValue(_buf, obj.height);
        gm::wire::codec::writeValue(_buf, obj.minDepth);
        gm::wire::codec::writeValue(_buf, obj.maxDepth);
    }

    template<>
    inline gm_structs::ID3D11Viewport readValue<gm_structs::ID3D11Viewport>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11Viewport obj;
        obj.topLeftX = gm::wire::codec::readValue<float>(_buf);
        obj.topLeftY = gm::wire::codec::readValue<float>(_buf);
        obj.width = gm::wire::codec::readValue<float>(_buf);
        obj.height = gm::wire::codec::readValue<float>(_buf);
        obj.minDepth = gm::wire::codec::readValue<float>(_buf);
        obj.maxDepth = gm::wire::codec::readValue<float>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11Rect>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11Rect& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.left);
        gm::wire::codec::writeValue(_buf, obj.top);
        gm::wire::codec::writeValue(_buf, obj.right);
        gm::wire::codec::writeValue(_buf, obj.bottom);
    }

    template<>
    inline gm_structs::ID3D11Rect readValue<gm_structs::ID3D11Rect>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11Rect obj;
        obj.left = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.top = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.right = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.bottom = gm::wire::codec::readValue<std::int32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11Box>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11Box& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.left);
        gm::wire::codec::writeValue(_buf, obj.top);
        gm::wire::codec::writeValue(_buf, obj.front);
        gm::wire::codec::writeValue(_buf, obj.right);
        gm::wire::codec::writeValue(_buf, obj.bottom);
        gm::wire::codec::writeValue(_buf, obj.back);
    }

    template<>
    inline gm_structs::ID3D11Box readValue<gm_structs::ID3D11Box>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11Box obj;
        obj.left = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.top = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.front = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.right = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.bottom = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.back = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11ShaderBinding>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11ShaderBinding& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.shader);
        gm::wire::codec::writeValue(_buf, obj.classInstances);
    }

    template<>
    inline gm_structs::ID3D11ShaderBinding readValue<gm_structs::ID3D11ShaderBinding>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11ShaderBinding obj;
        obj.shader = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.classInstances = gm::wire::codec::readVector<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11ClassInstanceDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11ClassInstanceDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.instanceId);
        gm::wire::codec::writeValue(_buf, obj.instanceIndex);
        gm::wire::codec::writeValue(_buf, obj.typeId);
        gm::wire::codec::writeValue(_buf, obj.constantBuffer);
        gm::wire::codec::writeValue(_buf, obj.baseConstantBufferOffset);
        gm::wire::codec::writeValue(_buf, obj.baseTexture);
        gm::wire::codec::writeValue(_buf, obj.baseSampler);
        gm::wire::codec::writeValue(_buf, obj.created);
    }

    template<>
    inline gm_structs::ID3D11ClassInstanceDesc readValue<gm_structs::ID3D11ClassInstanceDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11ClassInstanceDesc obj;
        obj.instanceId = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.instanceIndex = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.typeId = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.constantBuffer = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.baseConstantBufferOffset = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.baseTexture = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.baseSampler = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.created = gm::wire::codec::readValue<bool>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11CreateHandleResult>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11CreateHandleResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.hresult);
        gm::wire::codec::writeValue(_buf, obj.handle);
    }

    template<>
    inline gm_structs::ID3D11CreateHandleResult readValue<gm_structs::ID3D11CreateHandleResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11CreateHandleResult obj;
        obj.hresult = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.handle = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11BlendDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11BlendDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.alphaToCoverageEnable);
        gm::wire::codec::writeValue(_buf, obj.independentBlendEnable);
        gm::wire::codec::writeValue(_buf, obj.renderTargets);
    }

    template<>
    inline gm_structs::ID3D11BlendDesc readValue<gm_structs::ID3D11BlendDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11BlendDesc obj;
        obj.alphaToCoverageEnable = gm::wire::codec::readValue<bool>(_buf);
        obj.independentBlendEnable = gm::wire::codec::readValue<bool>(_buf);
        obj.renderTargets = gm::wire::codec::readVector<gm_structs::ID3D11RenderTargetBlendDesc>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::ID3D11DepthStencilDesc>(gm::byteio::IByteWriter& _buf, const gm_structs::ID3D11DepthStencilDesc& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.depthEnable);
        gm::wire::codec::writeValue(_buf, obj.depthWriteMask);
        gm::wire::codec::writeValue(_buf, obj.depthFunc);
        gm::wire::codec::writeValue(_buf, obj.stencilEnable);
        gm::wire::codec::writeValue(_buf, obj.stencilReadMask);
        gm::wire::codec::writeValue(_buf, obj.stencilWriteMask);
        gm::wire::codec::writeValue(_buf, obj.frontFace);
        gm::wire::codec::writeValue(_buf, obj.backFace);
    }

    template<>
    inline gm_structs::ID3D11DepthStencilDesc readValue<gm_structs::ID3D11DepthStencilDesc>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::ID3D11DepthStencilDesc obj;
        obj.depthEnable = gm::wire::codec::readValue<bool>(_buf);
        obj.depthWriteMask = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.depthFunc = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.stencilEnable = gm::wire::codec::readValue<bool>(_buf);
        obj.stencilReadMask = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.stencilWriteMask = gm::wire::codec::readValue<std::uint32_t>(_buf);
        obj.frontFace = gm::wire::codec::readValue<gm_structs::ID3D11DepthStencilOpDesc>(_buf);
        obj.backFace = gm::wire::codec::readValue<gm_structs::ID3D11DepthStencilOpDesc>(_buf);
        return obj;
    }

}

namespace gm::wire::details
{
    template<>
    struct gm_struct_traits<gm_structs::ID3D11Version>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 0;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11FormatSupportResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 1;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11MultisampleQualityResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 2;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11CounterInfo>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 3;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11BufferDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 4;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11SubresourceData>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 5;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11Texture1DDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 6;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11Texture2DDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 7;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11Texture3DDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 8;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11ShaderResourceViewDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 9;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11RenderTargetViewDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 10;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11DepthStencilViewDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 11;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11UnorderedAccessViewDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 12;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11InputElementDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 13;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11StreamOutputDeclarationEntry>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 14;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11ShaderCompileResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 15;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11SamplerDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 16;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11RasterizerDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 17;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11RenderTargetBlendDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 18;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11DepthStencilOpDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 19;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11QueryDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 20;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11CounterDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 21;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11CheckCounterResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 22;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11BlendStateBinding>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 23;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11DepthStencilStateBinding>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 24;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11PredicationBinding>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 25;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11VertexBufferBinding>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 26;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11IndexBufferBinding>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 27;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11Viewport>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 28;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11Rect>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 29;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11Box>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 30;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11ShaderBinding>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 31;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11ClassInstanceDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 32;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11CreateHandleResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 33;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11BlendDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 34;
    };

    template<>
    struct gm_struct_traits<gm_structs::ID3D11DepthStencilDesc>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 35;
    };

}

gm_structs::ID3D11Version id3d11_get_version();
bool id3d11_is_initialized();
std::int32_t id3d11_get_last_hresult();
std::uint64_t id3d11_get_device_handle();
std::uint64_t id3d11_get_context_handle();
std::uint64_t id3d11_get_swapchain_handle();
std::uint64_t id3d11_handle_query_interface(std::uint64_t handle, gm_enums::ID3D11HandleKind interfaceKind);
bool id3d11_handle_is_valid(std::uint64_t handle);
gm_enums::ID3D11HandleKind id3d11_handle_get_kind(std::uint64_t handle);
bool id3d11_handle_release(std::uint64_t handle);
gm_enums::ID3D11FeatureLevel id3d11_device_get_feature_level(std::uint64_t device);
std::uint32_t id3d11_device_get_creation_flags(std::uint64_t device);
std::int32_t id3d11_device_get_removed_reason(std::uint64_t device);
std::uint32_t id3d11_device_get_exception_mode(std::uint64_t device);
std::int32_t id3d11_device_set_exception_mode(std::uint64_t device, std::uint32_t raiseFlags);
std::uint64_t id3d11_device_get_immediate_context(std::uint64_t device);
gm_structs::ID3D11FormatSupportResult id3d11_device_check_format_support(std::uint64_t device, std::uint32_t format);
gm_structs::ID3D11MultisampleQualityResult id3d11_device_check_multisample_quality_levels(std::uint64_t device, std::uint32_t format, std::uint32_t sampleCount);
gm_structs::ID3D11CounterInfo id3d11_device_get_counter_info(std::uint64_t device);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_buffer(std::uint64_t device, const gm_structs::ID3D11BufferDesc& desc);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_buffer_with_data(std::uint64_t device, const gm_structs::ID3D11BufferDesc& desc, gm::wire::GMBuffer data);
gm_structs::ID3D11BufferDesc id3d11_buffer_get_desc(std::uint64_t bufferHandle);
std::uint64_t id3d11_device_child_get_device(std::uint64_t deviceChild);
gm_enums::ID3D11ResourceDimension id3d11_resource_get_dimension(std::uint64_t resource);
std::uint32_t id3d11_resource_get_eviction_priority(std::uint64_t resource);
bool id3d11_resource_set_eviction_priority(std::uint64_t resource, std::uint32_t evictionPriority);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture1d(std::uint64_t device, const gm_structs::ID3D11Texture1DDesc& desc);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture1d_with_data(std::uint64_t device, const gm_structs::ID3D11Texture1DDesc& desc, const std::vector<gm_structs::ID3D11SubresourceData>& subresources, gm::wire::GMBuffer data);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture2d(std::uint64_t device, const gm_structs::ID3D11Texture2DDesc& desc);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture2d_with_data(std::uint64_t device, const gm_structs::ID3D11Texture2DDesc& desc, const std::vector<gm_structs::ID3D11SubresourceData>& subresources, gm::wire::GMBuffer data);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture3d(std::uint64_t device, const gm_structs::ID3D11Texture3DDesc& desc);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_texture3d_with_data(std::uint64_t device, const gm_structs::ID3D11Texture3DDesc& desc, const std::vector<gm_structs::ID3D11SubresourceData>& subresources, gm::wire::GMBuffer data);
gm_structs::ID3D11Texture1DDesc id3d11_texture1d_get_desc(std::uint64_t texture);
gm_structs::ID3D11Texture2DDesc id3d11_texture2d_get_desc(std::uint64_t texture);
gm_structs::ID3D11Texture3DDesc id3d11_texture3d_get_desc(std::uint64_t texture);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_shader_resource_view_default(std::uint64_t device, std::uint64_t resource);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_shader_resource_view(std::uint64_t device, std::uint64_t resource, const gm_structs::ID3D11ShaderResourceViewDesc& desc);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_render_target_view_default(std::uint64_t device, std::uint64_t resource);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_render_target_view(std::uint64_t device, std::uint64_t resource, const gm_structs::ID3D11RenderTargetViewDesc& desc);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_depth_stencil_view_default(std::uint64_t device, std::uint64_t resource);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_depth_stencil_view(std::uint64_t device, std::uint64_t resource, const gm_structs::ID3D11DepthStencilViewDesc& desc);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_unordered_access_view_default(std::uint64_t device, std::uint64_t resource);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_unordered_access_view(std::uint64_t device, std::uint64_t resource, const gm_structs::ID3D11UnorderedAccessViewDesc& desc);
std::uint64_t id3d11_view_get_resource(std::uint64_t view);
gm_structs::ID3D11ShaderResourceViewDesc id3d11_shader_resource_view_get_desc(std::uint64_t view);
gm_structs::ID3D11RenderTargetViewDesc id3d11_render_target_view_get_desc(std::uint64_t view);
gm_structs::ID3D11DepthStencilViewDesc id3d11_depth_stencil_view_get_desc(std::uint64_t view);
gm_structs::ID3D11UnorderedAccessViewDesc id3d11_unordered_access_view_get_desc(std::uint64_t view);
gm_structs::ID3D11ShaderCompileResult id3d11_compile_shader(std::string_view source, std::string_view sourceName, std::string_view entryPoint, std::string_view target, std::uint32_t flags1, std::uint32_t flags2, gm::wire::GMBuffer bytecode, gm::wire::GMBuffer errors);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_vertex_shader(std::uint64_t device, gm::wire::GMBuffer bytecode, std::uint64_t bytecodeSize, std::uint64_t classLinkage);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_hull_shader(std::uint64_t device, gm::wire::GMBuffer bytecode, std::uint64_t bytecodeSize, std::uint64_t classLinkage);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_domain_shader(std::uint64_t device, gm::wire::GMBuffer bytecode, std::uint64_t bytecodeSize, std::uint64_t classLinkage);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_geometry_shader(std::uint64_t device, gm::wire::GMBuffer bytecode, std::uint64_t bytecodeSize, std::uint64_t classLinkage);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_pixel_shader(std::uint64_t device, gm::wire::GMBuffer bytecode, std::uint64_t bytecodeSize, std::uint64_t classLinkage);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_compute_shader(std::uint64_t device, gm::wire::GMBuffer bytecode, std::uint64_t bytecodeSize, std::uint64_t classLinkage);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_geometry_shader_with_stream_output(std::uint64_t device, gm::wire::GMBuffer bytecode, std::uint64_t bytecodeSize, const std::vector<gm_structs::ID3D11StreamOutputDeclarationEntry>& declarations, const std::vector<std::uint32_t>& bufferStrides, std::uint32_t rasterizedStream, std::uint64_t classLinkage);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_input_layout(std::uint64_t device, const std::vector<gm_structs::ID3D11InputElementDesc>& elements, gm::wire::GMBuffer shaderBytecode, std::uint64_t bytecodeSize);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_class_linkage(std::uint64_t device);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_sampler_state(std::uint64_t device, const gm_structs::ID3D11SamplerDesc& desc);
gm_structs::ID3D11SamplerDesc id3d11_sampler_state_get_desc(std::uint64_t state);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_rasterizer_state(std::uint64_t device, const gm_structs::ID3D11RasterizerDesc& desc);
gm_structs::ID3D11RasterizerDesc id3d11_rasterizer_state_get_desc(std::uint64_t state);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_blend_state(std::uint64_t device, const gm_structs::ID3D11BlendDesc& desc);
gm_structs::ID3D11BlendDesc id3d11_blend_state_get_desc(std::uint64_t state);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_depth_stencil_state(std::uint64_t device, const gm_structs::ID3D11DepthStencilDesc& desc);
gm_structs::ID3D11DepthStencilDesc id3d11_depth_stencil_state_get_desc(std::uint64_t state);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_query(std::uint64_t device, const gm_structs::ID3D11QueryDesc& desc);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_predicate(std::uint64_t device, const gm_structs::ID3D11QueryDesc& desc);
gm_structs::ID3D11CreateHandleResult id3d11_device_create_counter(std::uint64_t device, const gm_structs::ID3D11CounterDesc& desc);
std::uint32_t id3d11_asynchronous_get_data_size(std::uint64_t asynchronous);
gm_structs::ID3D11QueryDesc id3d11_query_get_desc(std::uint64_t query);
gm_structs::ID3D11CounterDesc id3d11_counter_get_desc(std::uint64_t counter);
gm_structs::ID3D11CheckCounterResult id3d11_device_check_counter(std::uint64_t device, const gm_structs::ID3D11CounterDesc& desc);
bool id3d11_device_context_begin(std::uint64_t context, std::uint64_t asynchronous);
bool id3d11_device_context_end(std::uint64_t context, std::uint64_t asynchronous);
std::int32_t id3d11_device_context_get_data(std::uint64_t context, std::uint64_t asynchronous, gm::wire::GMBuffer data, std::uint64_t dataSize, std::uint32_t flags);
bool id3d11_device_context_flush(std::uint64_t context);
bool id3d11_device_context_draw_indexed(std::uint64_t context, std::uint32_t indexCount, std::uint32_t startIndexLocation, std::int32_t baseVertexLocation);
bool id3d11_device_context_draw(std::uint64_t context, std::uint32_t vertexCount, std::uint32_t startVertexLocation);
bool id3d11_device_context_draw_indexed_instanced(std::uint64_t context, std::uint32_t indexCountPerInstance, std::uint32_t instanceCount, std::uint32_t startIndexLocation, std::int32_t baseVertexLocation, std::uint32_t startInstanceLocation);
bool id3d11_device_context_draw_instanced(std::uint64_t context, std::uint32_t vertexCountPerInstance, std::uint32_t instanceCount, std::uint32_t startVertexLocation, std::uint32_t startInstanceLocation);
bool id3d11_device_context_draw_auto(std::uint64_t context);
bool id3d11_device_context_draw_indexed_instanced_indirect(std::uint64_t context, std::uint64_t argumentBuffer, std::uint32_t alignedByteOffset);
bool id3d11_device_context_draw_instanced_indirect(std::uint64_t context, std::uint64_t argumentBuffer, std::uint32_t alignedByteOffset);
bool id3d11_device_context_dispatch(std::uint64_t context, std::uint32_t threadGroupCountX, std::uint32_t threadGroupCountY, std::uint32_t threadGroupCountZ);
bool id3d11_device_context_dispatch_indirect(std::uint64_t context, std::uint64_t argumentBuffer, std::uint32_t alignedByteOffset);
bool id3d11_device_context_copy_subresource_region(std::uint64_t context, std::uint64_t destinationResource, std::uint32_t destinationSubresource, std::uint32_t destinationX, std::uint32_t destinationY, std::uint32_t destinationZ, std::uint64_t sourceResource, std::uint32_t sourceSubresource, bool useSourceBox, const gm_structs::ID3D11Box& sourceBox);
bool id3d11_device_context_copy_resource(std::uint64_t context, std::uint64_t destinationResource, std::uint64_t sourceResource);
bool id3d11_device_context_copy_structure_count(std::uint64_t context, std::uint64_t destinationBuffer, std::uint32_t destinationAlignedByteOffset, std::uint64_t sourceView);
bool id3d11_device_context_clear_render_target_view(std::uint64_t context, std::uint64_t renderTargetView, float red, float green, float blue, float alpha);
bool id3d11_device_context_clear_unordered_access_view_uint(std::uint64_t context, std::uint64_t unorderedAccessView, std::uint32_t value0, std::uint32_t value1, std::uint32_t value2, std::uint32_t value3);
bool id3d11_device_context_clear_unordered_access_view_float(std::uint64_t context, std::uint64_t unorderedAccessView, float value0, float value1, float value2, float value3);
bool id3d11_device_context_clear_depth_stencil_view(std::uint64_t context, std::uint64_t depthStencilView, std::uint32_t clearFlags, float depth, std::uint32_t stencil);
bool id3d11_device_context_generate_mips(std::uint64_t context, std::uint64_t shaderResourceView);
bool id3d11_device_context_set_resource_min_lod(std::uint64_t context, std::uint64_t resource, float minimumLod);
float id3d11_device_context_get_resource_min_lod(std::uint64_t context, std::uint64_t resource);
bool id3d11_device_context_resolve_subresource(std::uint64_t context, std::uint64_t destinationResource, std::uint32_t destinationSubresource, std::uint64_t sourceResource, std::uint32_t sourceSubresource, std::uint32_t format);
bool id3d11_device_context_ia_set_input_layout(std::uint64_t context, std::uint64_t inputLayout);
std::uint64_t id3d11_device_context_ia_get_input_layout(std::uint64_t context);
bool id3d11_device_context_ia_set_primitive_topology(std::uint64_t context, gm_enums::ID3D11PrimitiveTopology topology);
gm_enums::ID3D11PrimitiveTopology id3d11_device_context_ia_get_primitive_topology(std::uint64_t context);
bool id3d11_device_context_rs_set_state(std::uint64_t context, std::uint64_t state);
std::uint64_t id3d11_device_context_rs_get_state(std::uint64_t context);
bool id3d11_device_context_om_set_blend_state(std::uint64_t context, std::uint64_t state, const std::vector<float>& blendFactor, std::uint32_t sampleMask);
gm_structs::ID3D11BlendStateBinding id3d11_device_context_om_get_blend_state(std::uint64_t context);
bool id3d11_device_context_om_set_depth_stencil_state(std::uint64_t context, std::uint64_t state, std::uint32_t stencilRef);
gm_structs::ID3D11DepthStencilStateBinding id3d11_device_context_om_get_depth_stencil_state(std::uint64_t context);
bool id3d11_device_context_set_predication(std::uint64_t context, std::uint64_t predicate, bool predicateValue);
gm_structs::ID3D11PredicationBinding id3d11_device_context_get_predication(std::uint64_t context);
bool id3d11_device_context_ia_set_vertex_buffers(std::uint64_t context, std::uint32_t startSlot, const std::vector<gm_structs::ID3D11VertexBufferBinding>& bindings);
std::vector<gm_structs::ID3D11VertexBufferBinding> id3d11_device_context_ia_get_vertex_buffers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_ia_set_index_buffer(std::uint64_t context, std::uint64_t buffer, std::uint32_t format, std::uint32_t offset);
gm_structs::ID3D11IndexBufferBinding id3d11_device_context_ia_get_index_buffer(std::uint64_t context);
bool id3d11_device_context_rs_set_viewports(std::uint64_t context, const std::vector<gm_structs::ID3D11Viewport>& viewports);
std::vector<gm_structs::ID3D11Viewport> id3d11_device_context_rs_get_viewports(std::uint64_t context);
bool id3d11_device_context_rs_set_scissor_rects(std::uint64_t context, const std::vector<gm_structs::ID3D11Rect>& rects);
std::vector<gm_structs::ID3D11Rect> id3d11_device_context_rs_get_scissor_rects(std::uint64_t context);
bool id3d11_device_context_vs_set_constant_buffers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& buffers);
std::vector<std::uint64_t> id3d11_device_context_vs_get_constant_buffers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_vs_set_shader_resources(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& views);
std::vector<std::uint64_t> id3d11_device_context_vs_get_shader_resources(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_vs_set_samplers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& samplers);
std::vector<std::uint64_t> id3d11_device_context_vs_get_samplers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_hs_set_constant_buffers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& buffers);
std::vector<std::uint64_t> id3d11_device_context_hs_get_constant_buffers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_hs_set_shader_resources(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& views);
std::vector<std::uint64_t> id3d11_device_context_hs_get_shader_resources(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_hs_set_samplers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& samplers);
std::vector<std::uint64_t> id3d11_device_context_hs_get_samplers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_ds_set_constant_buffers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& buffers);
std::vector<std::uint64_t> id3d11_device_context_ds_get_constant_buffers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_ds_set_shader_resources(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& views);
std::vector<std::uint64_t> id3d11_device_context_ds_get_shader_resources(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_ds_set_samplers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& samplers);
std::vector<std::uint64_t> id3d11_device_context_ds_get_samplers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_gs_set_constant_buffers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& buffers);
std::vector<std::uint64_t> id3d11_device_context_gs_get_constant_buffers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_gs_set_shader_resources(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& views);
std::vector<std::uint64_t> id3d11_device_context_gs_get_shader_resources(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_gs_set_samplers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& samplers);
std::vector<std::uint64_t> id3d11_device_context_gs_get_samplers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_ps_set_constant_buffers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& buffers);
std::vector<std::uint64_t> id3d11_device_context_ps_get_constant_buffers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_ps_set_shader_resources(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& views);
std::vector<std::uint64_t> id3d11_device_context_ps_get_shader_resources(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_ps_set_samplers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& samplers);
std::vector<std::uint64_t> id3d11_device_context_ps_get_samplers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_cs_set_constant_buffers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& buffers);
std::vector<std::uint64_t> id3d11_device_context_cs_get_constant_buffers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_cs_set_shader_resources(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& views);
std::vector<std::uint64_t> id3d11_device_context_cs_get_shader_resources(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_cs_set_samplers(std::uint64_t context, std::uint32_t startSlot, const std::vector<std::uint64_t>& samplers);
std::vector<std::uint64_t> id3d11_device_context_cs_get_samplers(std::uint64_t context, std::uint32_t startSlot, std::uint32_t count);
bool id3d11_device_context_vs_set_shader(std::uint64_t context, std::uint64_t shader, const std::vector<std::uint64_t>& classInstances);
gm_structs::ID3D11ShaderBinding id3d11_device_context_vs_get_shader(std::uint64_t context);
bool id3d11_device_context_hs_set_shader(std::uint64_t context, std::uint64_t shader, const std::vector<std::uint64_t>& classInstances);
gm_structs::ID3D11ShaderBinding id3d11_device_context_hs_get_shader(std::uint64_t context);
bool id3d11_device_context_ds_set_shader(std::uint64_t context, std::uint64_t shader, const std::vector<std::uint64_t>& classInstances);
gm_structs::ID3D11ShaderBinding id3d11_device_context_ds_get_shader(std::uint64_t context);
bool id3d11_device_context_gs_set_shader(std::uint64_t context, std::uint64_t shader, const std::vector<std::uint64_t>& classInstances);
gm_structs::ID3D11ShaderBinding id3d11_device_context_gs_get_shader(std::uint64_t context);
bool id3d11_device_context_ps_set_shader(std::uint64_t context, std::uint64_t shader, const std::vector<std::uint64_t>& classInstances);
gm_structs::ID3D11ShaderBinding id3d11_device_context_ps_get_shader(std::uint64_t context);
bool id3d11_device_context_cs_set_shader(std::uint64_t context, std::uint64_t shader, const std::vector<std::uint64_t>& classInstances);
gm_structs::ID3D11ShaderBinding id3d11_device_context_cs_get_shader(std::uint64_t context);
gm_structs::ID3D11CreateHandleResult id3d11_class_linkage_get_class_instance(std::uint64_t linkage, std::string_view classInstanceName, std::uint32_t instanceIndex);
gm_structs::ID3D11CreateHandleResult id3d11_class_linkage_create_class_instance(std::uint64_t linkage, std::string_view classTypeName, std::uint32_t constantBufferOffset, std::uint32_t constantVectorOffset, std::uint32_t textureOffset, std::uint32_t samplerOffset);
std::uint64_t id3d11_class_instance_get_class_linkage(std::uint64_t instance);
gm_structs::ID3D11ClassInstanceDesc id3d11_class_instance_get_desc(std::uint64_t instance);
std::string id3d11_class_instance_get_instance_name(std::uint64_t instance);
std::string id3d11_class_instance_get_type_name(std::uint64_t instance);

$ErrorActionPreference = "Stop"

$gmlPath = Join-Path $PSScriptRoot "../scripts/__id3d11_api/__id3d11_api.gml"
$source = Get-Content -LiteralPath $gmlPath -Raw
$inputStructs = @(
    "ID3D11BufferDesc",
    "ID3D11SubresourceData",
    "ID3D11Texture1DDesc",
    "ID3D11Texture2DDesc",
    "ID3D11Texture3DDesc",
    "ID3D11ShaderResourceViewDesc",
    "ID3D11RenderTargetViewDesc",
    "ID3D11DepthStencilViewDesc",
    "ID3D11UnorderedAccessViewDesc",
    "ID3D11InputElementDesc",
    "ID3D11StreamOutputDeclarationEntry",
    "ID3D11SamplerDesc",
    "ID3D11RasterizerDesc",
    "ID3D11RenderTargetBlendDesc",
    "ID3D11BlendDesc",
    "ID3D11DepthStencilOpDesc",
    "ID3D11DepthStencilDesc",
    "ID3D11QueryDesc",
    "ID3D11CounterDesc",
    "ID3D11VertexBufferBinding",
    "ID3D11IndexBufferBinding",
    "ID3D11Viewport",
    "ID3D11Rect",
    "ID3D11Box",
    "ID3D11StreamOutputTarget",
    "ID3D11UnorderedAccessViewBinding",
    "ID3D11OutputMergerTargetsAndUAVs"
)

foreach ($structName in $inputStructs)
{
    $escapedName = [Regex]::Escape($structName)
    $pattern = "(?ms)function $escapedName\(\) constructor\s*\{.*?^\}"
    $match = [Regex]::Match($source, $pattern)
    if (!$match.Success)
    {
        throw "Generated GML constructor was not found: $structName"
    }

    $patchedConstructor = $match.Value -replace "self\.semanticName = undefined;", 'self.semanticName = "";'
    $boolFields = "frontCounterClockwise|depthClipEnable|scissorEnable|multisampleEnable|antialiasedLineEnable|blendEnable|alphaToCoverageEnable|independentBlendEnable|depthEnable|stencilEnable"
    $patchedConstructor = $patchedConstructor -replace "self\.($boolFields) = undefined;", 'self.$1 = false;'
    $patchedConstructor = $patchedConstructor -replace "self\.renderTargets = undefined;", "self.renderTargets = [];"
    $patchedConstructor = $patchedConstructor -replace "self\.frontFace = undefined;", "self.frontFace = new ID3D11DepthStencilOpDesc();"
    $patchedConstructor = $patchedConstructor -replace "self\.backFace = undefined;", "self.backFace = new ID3D11DepthStencilOpDesc();"
    $patchedConstructor = $patchedConstructor -replace "= undefined;", "= 0;"
    $source = $source.Remove($match.Index, $match.Length).Insert($match.Index, $patchedConstructor)
}

Set-Content -LiteralPath $gmlPath -Value $source -Encoding utf8
Write-Host "Patched numeric descriptor constructors with zero defaults."

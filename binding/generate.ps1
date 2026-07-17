$ErrorActionPreference = "Stop"

$bindingRoot = $PSScriptRoot
$configPath = Join-Path $bindingRoot "config.json"
$generatorOutput = & extgen --config $configPath 2>&1
$generatorOutput | Write-Host

if ($LASTEXITCODE -ne 0 -or ($generatorOutput -match "(?m)\[[^]]+\]\s+Failed:"))
{
    throw "extgen failed to generate the ID3D11 bindings."
}

$requiredOutputs = @(
    (Join-Path $bindingRoot "code_gen/native/ID3D11Internal_native.cpp"),
    (Join-Path $bindingRoot "code_gen/native/ID3D11Internal_native.h"),
    (Join-Path $bindingRoot "../scripts/__id3d11_api/__id3d11_api.gml"),
    (Join-Path $bindingRoot "../scripts/__id3d11_runtime/__id3d11_runtime.gml"),
    (Join-Path $bindingRoot "../extensions/ID3D11/ID3D11.yy")
)

foreach ($outputPath in $requiredOutputs)
{
    if (!(Test-Path -LiteralPath $outputPath))
    {
        throw "extgen did not produce required output: $outputPath"
    }
}

$gmlDefaultsPatch = Join-Path $bindingRoot "patch-gml-defaults.ps1"
& $gmlDefaultsPatch

$extensionPatch = Join-Path $bindingRoot "patch-extension.ps1"
& $extensionPatch

Write-Host "ID3D11 bindings generated successfully."

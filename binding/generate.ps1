$ErrorActionPreference = "Stop"

if ($PSVersionTable.PSEdition -ne "Core" -or $PSVersionTable.PSVersion.Major -lt 7)
{
    throw "PowerShell 7 or newer is required."
}

$bindingRoot = $PSScriptRoot
$repositoryRoot = Split-Path -Parent $bindingRoot
$configPath = Join-Path $bindingRoot "config.json"
if ($null -eq (Get-Command extgen -ErrorAction SilentlyContinue))
{
    throw "extgen was not found on PATH. This project requires extgen v1.225bddc."
}

$extgenVersionOutput = & extgen --version 2>&1
$extgenVersion = $extgenVersionOutput |
    Where-Object { $_ -match '^extgen\s+v' } |
    Select-Object -First 1
if ($extgenVersion -ne "extgen v1.225bddc")
{
    throw "Unsupported extgen version '$extgenVersion'. This project requires extgen v1.225bddc."
}

$managedPaths = @(
    "binding/code_gen",
    "binding/CMakeLists.txt",
    "binding/cmake",
    "scripts/__id3d11_api/__id3d11_api.gml",
    "scripts/__id3d11_runtime/__id3d11_runtime.gml",
    "extensions/ID3D11/ID3D11.yy",
    "docs/generated/id3d11.json",
    "binding/out/docs"
)
$requiredFiles = @(
    "binding/code_gen/core/GMExtUtils.cpp",
    "binding/code_gen/core/GMExtUtils.h",
    "binding/code_gen/core/GMExtWire.cpp",
    "binding/code_gen/core/GMExtWire.h",
    "binding/code_gen/native/ID3D11Internal_exports.h",
    "binding/code_gen/native/ID3D11Internal_native.cpp",
    "binding/code_gen/native/ID3D11Internal_native.h",
    "binding/CMakeLists.txt",
    "scripts/__id3d11_api/__id3d11_api.gml",
    "scripts/__id3d11_runtime/__id3d11_runtime.gml",
    "extensions/ID3D11/ID3D11.yy",
    "docs/generated/id3d11.json"
)

$repositoryBytes = [System.Text.Encoding]::UTF8.GetBytes(
    [System.IO.Path]::GetFullPath($repositoryRoot).ToUpperInvariant())
$repositoryHash = [System.Convert]::ToHexString(
    [System.Security.Cryptography.SHA256]::HashData($repositoryBytes))
$lockPath = Join-Path ([System.IO.Path]::GetTempPath()) "id3d11-generate-$repositoryHash.lock"
$backupRoot = Join-Path ([System.IO.Path]::GetTempPath()) `
    "id3d11-generate-$([guid]::NewGuid().ToString('N'))"
$existingPaths = [System.Collections.Generic.HashSet[string]]::new(
    [System.StringComparer]::OrdinalIgnoreCase)
$lockStream = $null
$committed = $false
$snapshotComplete = $false

try
{
    try
    {
        $lockStream = [System.IO.File]::Open(
            $lockPath,
            [System.IO.FileMode]::OpenOrCreate,
            [System.IO.FileAccess]::ReadWrite,
            [System.IO.FileShare]::None)
    }
    catch
    {
        throw "Another binding generation is already using this repository."
    }

    [void](New-Item -ItemType Directory -Path $backupRoot)
    foreach ($relativePath in $managedPaths)
    {
        $sourcePath = Join-Path $repositoryRoot $relativePath
        if (!(Test-Path -LiteralPath $sourcePath))
        {
            continue
        }
        $backupPath = Join-Path $backupRoot $relativePath
        [void](New-Item -ItemType Directory -Path (Split-Path -Parent $backupPath) -Force)
        Copy-Item -LiteralPath $sourcePath -Destination $backupPath -Recurse -Force
        [void]$existingPaths.Add($relativePath)
    }
    $snapshotComplete = $true

    Push-Location $bindingRoot
    try
    {
        $generatorOutput = & extgen --config $configPath 2>&1
        $generatorExitCode = $LASTEXITCODE
        $generatorOutput | Write-Host
        if ($generatorExitCode -ne 0 -or
            ($generatorOutput -match "(?m)\[[^]]+\]\s+Failed:"))
        {
            throw "extgen failed to generate the ID3D11 bindings."
        }
    }
    finally
    {
        Pop-Location
    }

    & (Join-Path $bindingRoot "patch-gml-defaults.ps1")
    & (Join-Path $bindingRoot "patch-extension.ps1")

    foreach ($relativePath in $requiredFiles)
    {
        $outputPath = Join-Path $repositoryRoot $relativePath
        if (!(Test-Path -LiteralPath $outputPath -PathType Leaf) -or
            (Get-Item -LiteralPath $outputPath).Length -eq 0)
        {
            throw "Generation did not produce a valid output: $outputPath"
        }
    }
    Get-Content -LiteralPath (Join-Path $repositoryRoot "extensions/ID3D11/ID3D11.yy") `
        -Raw | ConvertFrom-Json | Out-Null
    Get-Content -LiteralPath (Join-Path $repositoryRoot "docs/generated/id3d11.json") `
        -Raw | ConvertFrom-Json | Out-Null

    $committed = $true
    Write-Host "ID3D11 bindings generated successfully."
}
finally
{
    if (!$committed -and $snapshotComplete -and (Test-Path -LiteralPath $backupRoot))
    {
        Write-Warning "Generation failed; restoring managed outputs."
        foreach ($relativePath in $managedPaths)
        {
            $targetPath = Join-Path $repositoryRoot $relativePath
            if (Test-Path -LiteralPath $targetPath)
            {
                Remove-Item -LiteralPath $targetPath -Recurse -Force
            }
        }
        foreach ($relativePath in $existingPaths)
        {
            $backupPath = Join-Path $backupRoot $relativePath
            $targetPath = Join-Path $repositoryRoot $relativePath
            [void](New-Item -ItemType Directory -Path (Split-Path -Parent $targetPath) -Force)
            Copy-Item -LiteralPath $backupPath -Destination $targetPath -Recurse -Force
        }
    }
    if (Test-Path -LiteralPath $backupRoot)
    {
        Remove-Item -LiteralPath $backupRoot -Recurse -Force
    }
    if ($null -ne $lockStream)
    {
        $lockStream.Dispose()
    }
    Remove-Item -LiteralPath $lockPath -Force -ErrorAction SilentlyContinue
}

[CmdletBinding()]
param(
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Release",

    [switch]$SkipGenerate,
    [switch]$SkipGameMaker,

    [switch]$SkipSmoke,

    [ValidateRange(10, 3600)]
    [int]$SmokeTimeoutSeconds = 180,

    [switch]$Legacy
)

$ErrorActionPreference = "Stop"
$repositoryRoot = $PSScriptRoot

function Invoke-Checked
{
    param(
        [Parameter(Mandatory)]
        [string]$Command,

        [Parameter(ValueFromRemainingArguments)]
        [string[]]$Arguments
    )

    & $Command @Arguments
    if ($LASTEXITCODE -ne 0)
    {
        throw "Command failed with exit code ${LASTEXITCODE}: $Command $Arguments"
    }
}

if ($Legacy)
{
    $legacyBuild = Join-Path $repositoryRoot "cpp/build-v145"
    Invoke-Checked cmake -S (Join-Path $repositoryRoot "cpp") -B $legacyBuild `
        -G "Visual Studio 18 2026" -A x64 -T v145
    Invoke-Checked cmake --build $legacyBuild --config $Configuration
    Copy-Item -LiteralPath (Join-Path $legacyBuild "$Configuration/GMD3D11.dll") `
        -Destination (Join-Path $repositoryRoot "datafiles/GMD3D11.dll") -Force
    Invoke-Checked python (Join-Path $repositoryRoot "gmlgen.py")
    Write-Host "Legacy GMD3D11 build completed."
    exit 0
}

$bindingRoot = Join-Path $repositoryRoot "binding"
if (!$SkipGenerate)
{
    & (Join-Path $bindingRoot "generate.ps1")
}

Push-Location $bindingRoot
try
{
    Invoke-Checked cmake --preset win-v145
    $buildPreset = if ($Configuration -eq "Debug") { "win-v145-debug" } else { "win-v145-release" }
    Invoke-Checked cmake --build --preset $buildPreset
}
finally
{
    Pop-Location
}

if (!$SkipGameMaker)
{
    Invoke-Checked gm-cli compile (Join-Path $repositoryRoot "ID3D11.yyp") `
        --target=windows --runtime=vm
}

if (!$SkipSmoke -and !$SkipGameMaker)
{
    & (Join-Path $repositoryRoot "scripts/smoke.ps1") `
        -SkipCompile `
        -TimeoutSeconds $SmokeTimeoutSeconds
    if ($LASTEXITCODE -ne 0)
    {
        throw "GameMaker smoke test failed."
    }
}

Write-Host "ID3D11 $Configuration build completed."

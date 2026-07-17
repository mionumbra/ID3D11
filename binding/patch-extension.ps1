$ErrorActionPreference = "Stop"

$extensionPath = Join-Path $PSScriptRoot "../extensions/ID3D11/ID3D11.yy"
$extension = Get-Content -LiteralPath $extensionPath -Raw | ConvertFrom-Json
$dllFile = $extension.files | Where-Object { $_.filename -eq "ID3D11.dll" } | Select-Object -First 1

if ($null -eq $dllFile)
{
    throw "ID3D11.dll is missing from the generated extension resource."
}

$bootstrap = [ordered]@{
    '$GMExtensionFunction' = ''
    '%Name' = '__id3d11_bootstrap_raw'
    argCount = 3
    args = @(1, 1, 1)
    documentation = '@param {String} _device`r`n@param {String} _context`r`n@param {String} _swapchain`r`n@returns {Real}'
    externalName = '__id3d11_bootstrap_raw'
    help = ''
    hidden = $true
    kind = 4
    name = '__id3d11_bootstrap_raw'
    resourceType = 'GMExtensionFunction'
    resourceVersion = '2.0'
    returnType = 2
}

$generatedFunctions = @($dllFile.functions | Where-Object { $_.name -ne '__id3d11_bootstrap_raw' })
$dllFile.functions = @($generatedFunctions + [pscustomobject]$bootstrap)
$extension | ConvertTo-Json -Depth 100 | Set-Content -LiteralPath $extensionPath -Encoding utf8

Write-Host "Patched native D3D11 bootstrap metadata into ID3D11.yy."

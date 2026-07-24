[CmdletBinding()]
param(
    [switch]$SkipCompile,

    [ValidateRange(10, 3600)]
    [int]$TimeoutSeconds = 180,

    [string]$LogPath
)

$ErrorActionPreference = "Stop"
$repositoryRoot = Split-Path -Parent $PSScriptRoot
$projectPath = Join-Path $repositoryRoot "ID3D11.yyp"

if (!(Test-Path -LiteralPath $projectPath))
{
    throw "GameMaker project was not found: $projectPath"
}

$gmCli = Get-Command gm-cli -ErrorAction Stop
$gmCliPath = $gmCli.Source
if ([string]::IsNullOrWhiteSpace($gmCliPath))
{
    throw "Could not resolve the gm-cli script path."
}

function Invoke-GmCli
{
    param(
        [Parameter(Mandatory)]
        [string[]]$Arguments
    )

    & $gmCliPath @Arguments
    if ($LASTEXITCODE -ne 0)
    {
        throw "gm-cli failed with exit code ${LASTEXITCODE}: $Arguments"
    }
}

if (!$SkipCompile)
{
    Write-Host "Compiling GameMaker project..."
    Invoke-GmCli @(
        "compile", $projectPath,
        "--target=windows",
        "--runtime=vm"
    )
}

$temporaryLog = $false
if ([string]::IsNullOrWhiteSpace($LogPath))
{
    $LogPath = Join-Path ([System.IO.Path]::GetTempPath()) "id3d11-smoke-$([guid]::NewGuid()).log"
    $temporaryLog = $true
}

$logDirectory = Split-Path -Parent $LogPath
if (![string]::IsNullOrWhiteSpace($logDirectory) -and !(Test-Path -LiteralPath $logDirectory))
{
    throw "Smoke log directory does not exist: $logDirectory"
}

$stdoutPath = "$LogPath.stdout"
$stderrPath = "$LogPath.stderr"
$process = $null
$smokePassed = $false
try
{
    $startInfo = [System.Diagnostics.ProcessStartInfo]::new()
    $startInfo.FileName = (Get-Command pwsh -ErrorAction Stop).Source
    $startInfo.UseShellExecute = $false
    $startInfo.Environment["ID3D11_SMOKE"] = "1"
    $startInfo.Environment["ID3D11_SMOKE_AUTO_EXIT"] = "1"
    $startInfo.CreateNoWindow = $true
    $startInfo.RedirectStandardOutput = $true
    $startInfo.RedirectStandardError = $true
    $startInfo.StandardOutputEncoding = [System.Text.Encoding]::UTF8
    $startInfo.StandardErrorEncoding = [System.Text.Encoding]::UTF8
    $startInfo.ArgumentList.Add("-NoProfile")
    $startInfo.ArgumentList.Add("-File")
    $startInfo.ArgumentList.Add($gmCliPath)
    $startInfo.ArgumentList.Add("run")
    $startInfo.ArgumentList.Add($projectPath)
    $startInfo.ArgumentList.Add("--target=windows")
    $startInfo.ArgumentList.Add("--runtime=vm")

    $process = [System.Diagnostics.Process]::new()
    $process.StartInfo = $startInfo
    [void]$process.Start()
    $stdoutTask = $process.StandardOutput.ReadToEndAsync()
    $stderrTask = $process.StandardError.ReadToEndAsync()

    if (!$process.WaitForExit($TimeoutSeconds * 1000))
    {
        $process.Kill($true)
        throw "Smoke test timed out after $TimeoutSeconds seconds."
    }

    $stdout = $stdoutTask.GetAwaiter().GetResult()
    $stderr = $stderrTask.GetAwaiter().GetResult()
    Set-Content -LiteralPath $stdoutPath -Value $stdout -Encoding utf8
    Set-Content -LiteralPath $stderrPath -Value $stderr -Encoding utf8
    Set-Content -LiteralPath $LogPath -Value ($stdout + $stderr) -Encoding utf8

    $combinedOutput = $stdout + "`n" + $stderr
    if ($process.ExitCode -ne 0)
    {
        $failureDetail = $stderr.Trim()
        if ([string]::IsNullOrWhiteSpace($failureDetail))
        {
            $failureDetail = "No stderr output was captured."
        }
        throw "gm-cli run failed with exit code $($process.ExitCode): $failureDetail`nSee log: $LogPath"
    }

    $resultLines = [regex]::Matches(
        $combinedOutput,
        '(?m)\[ID3D11\] bootstrap=\d+ smoke=\d+ shader=\d+ state=\d+ async=\d+ context=\d+ pipeline=\d+ feature_level=\d+\s*$')
    if ($resultLines.Count -ne 1)
    {
        throw "Smoke result line was missing or appeared more than once. See log: $LogPath"
    }

    $result = $resultLines[0].Value.Trim()
    if ($result -notmatch 'bootstrap=1 smoke=1 shader=1 state=1 async=1 context=1 pipeline=1 feature_level=\d+')
    {
        throw "Smoke assertions failed: $result"
    }

    $hasCleanGameEnd = $combinedOutput -match '(?m)###game_end###0\s*$'
    $hasCleanRunnerExit =
        $combinedOutput -match '(?m)Runner\.exe DONE \(0\)\s*$' -or
        $combinedOutput -match '(?m)Game exited\s*$'
    if (!$hasCleanGameEnd -or !$hasCleanRunnerExit)
    {
        throw "Runner did not report a clean game_end. See log: $LogPath"
    }

    $smokePassed = $true
    Write-Host $result
    Write-Host "Smoke test passed. Log: $LogPath"
}
catch
{
    if ($process -and !$process.HasExited)
    {
        $process.Kill($true)
    }
    if (Test-Path -LiteralPath $LogPath)
    {
        Write-Host "Smoke log: $LogPath"
    }
    throw
}
finally
{
    if ($process)
    {
        $process.Dispose()
    }
    if ($temporaryLog -and $smokePassed)
    {
        Remove-Item -LiteralPath $LogPath, $stdoutPath, $stderrPath -Force -ErrorAction SilentlyContinue
    }
}

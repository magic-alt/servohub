$ErrorActionPreference = "Stop"

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$VenvDir = Join-Path $ScriptDir ".venv"
$Python = Join-Path $VenvDir "Scripts\python.exe"

Write-Host "[ServoHub] Creating Python 3.12 virtual environment..."
py -3.12 -m venv $VenvDir

Write-Host "[ServoHub] Installing pinned CANopen generator..."
& $Python -m pip install --upgrade pip
& $Python -m pip install -r (Join-Path $ScriptDir "requirements.txt")

Write-Host "[ServoHub] Verifying generator..."
& $Python (Join-Path $ScriptDir "generate.py") doctor

Write-Host ""
Write-Host "Ready. Common commands:"
Write-Host "  & `"$Python`" `"$ScriptDir\generate.py`" list"
Write-Host "  & `"$Python`" `"$ScriptDir\generate.py`" generate"
Write-Host "  & `"$Python`" `"$ScriptDir\generate.py`" migrate-jsonc"

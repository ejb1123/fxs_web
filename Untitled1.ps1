function CheckPython() {
    $testPath = Get-Item "HKLM:\SOFTWARE\Python\PythonCore\2.7\InstallPath"
  
  
    if (Test-Path $testPath) {
        return $true
    }
    elseif (Test-Path "C:\FiveM-dev\python27") { 
        return $true
    }
    else {
        return $false
    }
}

function CreateMainPath() {
    New-Item -Path C:\FiveM-dev
}

function DownloadPythonInstaller() {
    $url = "https://www.python.org/ftp/python/2.7.13/python-2.7.13.amd64.msi"
    $output = "$env:TEMP\python27installer.msi"
    $start_time = Get-Date
  
    Invoke-WebRequest -Uri $url -OutFile $output
    Write-Output "Time taken: $((Get-Date).Subtract($start_time).Seconds) second(s)"
}

function InstallPython() {
    DownloadPythonInstaller
    msiexec.exe /i "$env:TEMP\python27installer.msi" /norestart  /qb ADDLOCAL=ALL TARGETDIR=C:\FiveM-dev\python27 ALLUSERS=1  
}

function CheckPremake5() {
    if (Test-Path -Path C:\FiveM-dev\Premake5\Premake5.exe) {
        return $true
    }
    else {
        return $false;
    }
}

function InstallPremake5 () {
    Expand-Archive -Path "$env:TEMP\premake-5.0.0-alpha11-windows.zip" -DestinationPath C:\FiveM-Dev\Premake5
}

function DownloadPremake5() {
    $url = "https://github.com/premake/premake-core/releases/download/v5.0.0-alpha11/premake-5.0.0-alpha11-windows.zip"
    $output = "$env:TEMP\premake-5.0.0-alpha11-windows.zip"
    $start_time = Get-Date  
    Invoke-WebRequest -Uri $url -OutFile $output
    Write-Output "Time taken: $((Get-Date).Subtract($start_time).Seconds) second(s)"
}
function CheckBoost () {
  if (Test-Path -Path C:\FiveM-Dev\Boost) {
    return $true
  }
  else {
    return $false
  }
}
function DownloadBoost () {
    $url = "https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.zip/download"
    $output = "$env:TEMP\boost_1_63_0.zip.zip"
    if (!(Test-Path -Path "$env:TEMP\boost_1_63_0.zip.zip")) {
        $start_time = Get-Date 
        Invoke-WebRequest -Uri $url -OutFile $output -UserAgent [Microsoft.PowerShell.Commands.PSUserAgent]::Chrome
        Write-Output "Time taken: $((Get-Date).Subtract($start_time).Seconds) second(s)"
    }
}
function InstallBoost () {
    Expand-Archive -Path "$env:TEMP\boost_1_63_0.zip.zip" -DestinationPath C:\FiveM-Dev\Boost
}
if (Test-Path -Path C:\FiveM-dev) {
    
}
else {
    CreateMainPath
}

if (CheckPython) {
    "Python Exists"
}
else {
    "Installing Python"
    InstallPython
}
if (CheckPremake5) {
    "Premake5 exists"
}
else {
    DownloadPremake5
    InstallPremake5
}
if (CheckBoost) {
    "Boost exists"
}
else {
    DownloadBoost
    InstallBoost
}

git clone https://github.com/citizenfx/fivem.git
Push-Location fivem

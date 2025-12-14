@echo off
setlocal EnableExtensions EnableDelayedExpansion

REM --- Configuration ---
set "SERVER_BUILD_URL=https://www.slsoft.de/extern/software/akhenaten/buildnumber.txt"
set "SERVER_ZIP_URL=https://www.slsoft.de/extern/software/akhenaten/windows_build.zip"
set "LOCAL_BUILD_FILE=%~dp0buildnumber.txt"

REM --- Lokale buildnumber.txt neben der .bat prüfen ---
set "CURRENT_DIR=%CD%"
if exist "%CURRENT_DIR%\buildnumber_nightly.txt" (
    set "SERVER_BUILD_URL=https://www.slsoft.de/extern/software/akhenaten/buildnumber_nightly.txt"
    set "SERVER_ZIP_URL=https://www.slsoft.de/extern/software/akhenaten/windows_build_nightly.zip"
    set "LOCAL_BUILD_FILE=%~dp0buildnumber_nightly.txt"
)

set "TEMP_DIR=%TEMP%\akhenaten_update"
if not exist "%TEMP_DIR%\" md "%TEMP_DIR%"

echo Checking Buildnumber on Server ...

REM --- Get server buildnumber ---
set "SERVER_BUILD="
for /f "usebackq delims=" %%A in (`
  powershell -NoProfile -Command "(Invoke-WebRequest -UseBasicParsing -Uri '%SERVER_BUILD_URL%').Content.Trim()"
`) do set "SERVER_BUILD=%%A"

if not defined SERVER_BUILD (
  echo Error: Can't fetch buildnumber from server.
  exit /b 1
)
echo Server Buildnummer: !SERVER_BUILD!

REM --- Get local buildnumber (trimmed) ---
if exist "%LOCAL_BUILD_FILE%" (
  for /f "usebackq delims=" %%A in ("%LOCAL_BUILD_FILE%") do set "LOCAL_BUILD=%%A"
) else (
  set "LOCAL_BUILD=0"
)
if not defined LOCAL_BUILD set "LOCAL_BUILD=0"
echo Local Buildnummer: !LOCAL_BUILD!

REM --- Force numeric values (non-numeric -> 0) ---
set /a SERVER_BUILD_NUM=1*!SERVER_BUILD! >nul 2>&1
set /a LOCAL_BUILD_NUM=1*!LOCAL_BUILD!  >nul 2>&1

REM --- Compare ---
if !SERVER_BUILD_NUM! GTR !LOCAL_BUILD_NUM! (
  echo New version available. Downloading...

  set "ZIP_PATH=%TEMP_DIR%\akhenaten.zip"

  REM --- Download Zip ---
  powershell -NoProfile -Command "Invoke-WebRequest -Uri '%SERVER_ZIP_URL%' -OutFile '!ZIP_PATH!'"
  if errorlevel 1 (
    echo Error on download archive.
    exit /b 1
  )

  echo Update downloaded to !ZIP_PATH!

  REM --- Extract ---
  echo Extract Update to !CURRENT_DIR!...
  powershell -NoProfile -Command "Expand-Archive -Force -LiteralPath '!ZIP_PATH!' -DestinationPath '!CURRENT_DIR!'"
  if errorlevel 1 (
    echo Error on extracting!
    exit /b 1
  )

  REM --- Persist installed build number ---
  > "%LOCAL_BUILD_FILE%" echo !SERVER_BUILD!

  echo Update successfully installed.

  REM --- Clean up ---
  rmdir /s /q "%TEMP_DIR%"
) else (
  echo No new version available. You have the latest version already.
)

endlocal

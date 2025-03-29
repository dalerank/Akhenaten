@echo off
set URL=https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_windows/master/windows_build.zip
set ZIPFILE=windows_build.zip

echo Downloading %ZIPFILE% from %URL%...
powershell -Command Invoke-WebRequest -Uri %URL% -OutFile %ZIPFILE%

echo Closing akhenaten.exe if running...
taskkill /F /IM akhenaten.exe 2>NUL

echo Extracting %ZIPFILE%...
powershell -Command "Expand-Archive -Path '%ZIPFILE%' -DestinationPath '.' -Force"

echo Deleting %ZIPFILE%...
del %ZIPFILE%

echo Starting %EXE%...
start "" "%CD%\akhenaten.exe"

echo Done!
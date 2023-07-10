mkdir build
cd build
set "build_type=%1"
set "debug_flag="
if "%1"=="" (
  set "build_type=Debug"
  set "debug_flag=/D"
)

cmake -DCMAKE_BUILD_TYPE=%build_type% ../
start ozymandias.sln %debug_flag% .
cd ..


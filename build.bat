call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" || (
    echo Failed to set MSVC environment
    exit /b 1
)

cl /nologo /DNDEBUG /DPX_PHYSX_STATIC_LIB ^
/I".\physx\include" ^
/Fo".\physx\lib\physx_wrapper.obj" ^
/LD "wrapper\physx_wrapper.cpp" ^
/link /DEF:physx_wrapper.def /LIBPATH:".\physx\lib" ^
PhysX_64.lib PhysXCommon_64.lib PhysXFoundation_64.lib ^
PhysXCooking_64.lib PhysXExtensions_static_64.lib PhysXPvdSDK_static_64.lib ^
/OUT:".\physx\lib\physx_wrapper.dll"

xcopy /Y ".\physx\lib\*.dll" .\


set CGO_ENABLED=1
set CGO_CFLAGS=-I%CD%\physx\include
set CGO_CXXFLAGS=-I%CD%\physx\include
set CGO_LDFLAGS=-L%CD%\physx\lib -lphysx_wrapper -lPhysX_64 -lPhysXCommon_64 -lPhysXFoundation_64 -lstdc++
set CC=gcc
set CXX=g++
go build -v

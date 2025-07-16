# cgo-physx

使用Go语言的CGO调用NVIDIA PhysX物理引擎的示例项目（Windows平台）。

## 环境要求

- Windows 10/11
- Go 1.18+
- Visual Studio 2022 (MSVC工具链)
- Git
- [PhysX 5.1 SDK](https://github.com/NVIDIA-Omniverse/PhysX)

## 快速开始

### 1. 准备PhysX库

```bash
# 克隆PhysX源码
git clone https://github.com/NVIDIA-Omniverse/PhysX.git
cd PhysX
运行 generate_project.bat   ，选择 CPU-only

# 使用Visual Studio 2022编译 
# 打开PhysX/physx/compiler/vc17win64/PhysXSDK.sln
# 选择"Checked"配置，编译解决方案

从 PhysX\bin\win.x86_64.vc143.mt\checked\ 复制以下文件到 physx/lib/：
- PhysX_64.dll
- PhysXCommon_64.dll
- PhysXFoundation_64.dll
- PhysXCooking_64.dll
- 对应的.lib文件

运行 build.bat 生成 main.go 对应的exe 
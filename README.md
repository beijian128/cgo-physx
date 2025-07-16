cgo-physx

使用Go语言通过CGO调用NVIDIA PhysX物理引擎的示例项目（Windows平台）。

环境要求

• 操作系统: Windows 10/11 64位

• Go版本: 1.18或更高

• 开发工具: 

  • Visual Studio 2022 (包含MSVC工具链)

  • Git

• 依赖库: 

  • https://github.com/NVIDIA-Omniverse/PhysX

快速开始

1. 获取PhysX源码

git clone https://github.com/NVIDIA-Omniverse/PhysX.git
cd PhysX


2. 生成项目文件

运行generate_project.bat脚本，选择CPU-only配置。

3. 编译PhysX库

1. 使用Visual Studio 2022打开解决方案文件：

   PhysX/physx/compiler/vc17win64/PhysXSDK.sln
   
2. 选择"Checked"配置
3. 编译整个解决方案

4. 复制库文件

从以下目录复制必要的DLL和LIB文件到项目的physx/lib/目录：

PhysX\bin\win.x86_64.vc143.mt\checked\


需要复制的文件包括：
• PhysX_64.dll

• PhysXCommon_64.dll

• PhysXFoundation_64.dll

• PhysXCooking_64.dll

• 对应的.lib文件

5. 构建并运行示例

build.bat


这将编译并生成main.go对应的可执行文件。

项目结构


cgo-physx/
├── physx/
│   ├── include/    # PhysX头文件
│   └── lib/       # PhysX库文件
├── main.go         # 主程序文件
└── build.bat       # 构建脚本


注意事项

1. 确保使用64位环境进行编译
2. 所有路径中不要包含中文或特殊字符
3. 如果遇到链接错误，请检查库文件路径是否正确

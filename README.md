# SEU-DIP-Labwork

本项目为东南大学2021级计算机科学与技术专业数字图像处理实验。

## ✨ 快速开始

### Requirements

- `Qt >= 6.5`
- `CMake >= 3.20`
- `ninja` or other build system (unverified)
- `MSVC` or other C++ compiler (unverified)
- `OpenCV >= 4.0`

### 构建方法

指定 OpenCV 以及 Qt SDK 位置进行构建即可。

下面是使用 vcpkg 管理 OpenCV，使用 MSVC+Ninja 构建的命令。

```
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg.cmake -DCMAKE_PREFIX_PATH=path/to/qt/sdk -G Ninja -DCMAKE_CXX_COMPILER=cl ..
ninja
```

## 🧪 实验内容

#### 实验一 程序总体框架

- [x] 搭建整体 GUI 框架（ 支持显示多幅图像 ）
- [x] 实现读取 bmp 图像并进行傅里叶变换

#### 第四周周五 直方图

- [x] 实现直方图显示
- [x] 实现直方图均衡化
- [x] 实现 CLAHE 算法

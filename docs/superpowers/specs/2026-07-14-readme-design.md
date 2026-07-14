# README 设计：LineFind OpenCV Algorithms

## 目标

在仓库根目录提供中文 `README.md`，帮助读者理解并构建基于 OpenCV 的交互式直线检测演示程序；内容参考现有交接文档的算法说明深度，但采用 GitHub 项目首页的阅读结构。

## 范围

- 说明 `Linefind_demo` 的用途、交互能力、算法流程和主要参数。
- 说明解决方案、源码、测试图片和已编译 x64 发布包的位置。
- 提供 Visual Studio 2022、C++17 和 OpenCV 4.4.0 的构建前提。
- 如实记录当前限制：`main.cpp` 使用本机绝对图片路径；解决方案还引用未纳入仓库的 `linedectect_master` 项目；发布包未包含 VC++ 运行库。

不修改任何 C++ 源码、解决方案引用、发布二进制或测试图片。

## README 结构

1. 项目简介：卡尺式直线检测的交互式 OpenCV C++ Demo。
2. 功能：打开/切换图像、箭头卡尺和旋转 ROI、参数调节、边缘点与拟合线显示、缩放平移。
3. 算法流程：灰度化、生成卡尺、灰度剖面、梯度候选、点选择、外点剔除、`cv::fitLine` 拟合和 ROI 裁剪。
4. 目录结构：`Linefind_demo/`、`testImage/`、`dist/Linefind_demo-x64/` 和解决方案文件。
5. 编译与运行：环境、OpenCV 链接设置、启动方式，以及测试路径需要调整的事实。
6. 已编译发布版：x64 可执行文件与 `opencv_world440.dll` 的位置；需要系统已安装 Microsoft Visual C++ Redistributable。
7. 已知限制与后续方向：缺失的第二个解决方案项目、绝对路径和可优化的鲁棒性/质量评估。

## 验收标准

- README 为中文，标题与文件路径和仓库实际一致。
- 文档不声称当前项目能在任意电脑直接运行。
- 文档不把未上传的 `linedectect_master` 描述为仓库内容。
- README 通过 Markdown 基本结构检查，并作为唯一新增跟踪文件提交。

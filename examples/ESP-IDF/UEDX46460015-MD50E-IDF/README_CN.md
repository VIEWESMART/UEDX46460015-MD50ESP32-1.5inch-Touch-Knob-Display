# UEDX46460015-MD50ET ESP-IDF 示例工程

本仓库是 **UEDX46460015-MD50ET**（1.5 寸圆形 AMOLED 旋钮屏，ESP32-S3）的开源示例，展示如何用 ESP-IDF 点亮屏幕、触摸、旋钮/按键，并运行 SquareLine 导出的 LVGL UI。

板级驱动已封装为组件仓库中的 BSP：

- BSP：[viewesmart/bsp_knob_15_md50et](https://components.espressif.com/components/viewesmart/bsp_knob_15_md50et)（建议 `^1.0.2`）
- 触摸：[viewesmart/esp_lcd_touch_cst820](https://components.espressif.com/components/viewesmart/esp_lcd_touch_cst820)（由 BSP 自动拉取）

[English](./README.md)

---

## 目录

1. [你能得到什么](#你能得到什么)
2. [硬件准备](#硬件准备)
3. [软件环境准备（新手必看）](#软件环境准备新手必看)
4. [获取本工程](#获取本工程)
5. [用 VS Code 打开并配置](#用-vs-code-打开并配置)
6. [第一次编译](#第一次编译)
7. [烧录与串口监视](#烧录与串口监视)
8. [成功时你会看到什么](#成功时你会看到什么)
9. [工程目录说明](#工程目录说明)
10. [依赖说明](#依赖说明)
11. [示例代码入口](#示例代码入口)
12. [替换 / 修改 SquareLine UI](#替换--修改-squareline-ui)
13. [选择 LVGL 8 或 9](#选择-lvgl-8-或-9)
14. [引脚一览](#引脚一览)
15. [BSP API 摘要](#bsp-api-摘要)
16. [常见问题排查](#常见问题排查)
17. [许可证与相关链接](#许可证与相关链接)

---

## 你能得到什么

跑通本示例后，你可以：

- 在 1.5" 圆形 AMOLED 上显示 LVGL 界面（本仓库自带演示 UI）
- 使用触摸屏点按 UI
- 使用旋钮左右旋转、按键（GPIO0）触发 UI 事件
- 通过 BSP API 调节面板亮度（0~100）

本工程已在 **ESP-IDF v5.5.4**、目标芯片 **esp32s3** 上验证。

---

## 硬件准备

| 项目 | 说明 |
|------|------|
| 模组 | UEDX46460015-MD50ET（文件夹名可能写作 MD50E，指同一款板） |
| MCU | ESP32-S3，**16 MB Flash + Octal PSRAM**（本工程默认按此配置） |
| 屏幕 | 1.5" 圆形 AMOLED，驱动芯片 CO5300，接口 QSPI |
| 触摸 | CST820，I2C |
| 输入 | 旋转编码器 + 按键（GPIO0，通常也是 Boot 键） |
| 数据线 | 能传数据的 USB 线（仅充电线无法下载） |
| 电脑 | Windows / macOS / Linux 均可（下文以 Windows + VS Code 为例） |

显示分辨率约定（很重要，改错会出现绿边/留白）：

| 用途 | 分辨率 |
|------|--------|
| 驱动 / LVGL 显示缓冲 | **472 × 466** |
| SquareLine 工程设计尺寸 | **466 × 466** |
| `esp_lcd_panel_set_gap()` | **不要调用** |

---

## 软件环境准备（新手必看）

推荐使用 **Visual Studio Code + Espressif IDF 扩展**，并通过 **EIM（ESP-IDF Installation Manager / Espressif Installation Manager）** 安装 ESP-IDF 与工具链。这是当前官方推荐方式，比旧的 “Configure ESP-IDF extension” 向导更统一、更稳定。

官方说明可参考：

- [Install ESP-IDF and Tools（VS Code 扩展文档）](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/installation.html)
- [ESP-IDF Installation Manager](https://docs.espressif.com/projects/idf-im-ui/en/latest/)

### 1. 安装 VS Code

1. 打开 [https://code.visualstudio.com/](https://code.visualstudio.com/) 下载并安装。
2. 安装完成后打开 VS Code。

### 2. 安装 Espressif IDF 扩展

1. 左侧点 **扩展（Extensions）**，或按 `Ctrl+Shift+X`（macOS：`Shift+Command+X`）。
2. 搜索 **ESP-IDF** 或 **Espressif IDF**。
3. 安装发布者名为 **Espressif Systems** 的扩展。
4. 安装完成后如弹出配置提示，可先关闭，下一步用 EIM 正式安装。

### 3. 用 EIM 安装 ESP-IDF（>= 5.5）

EIM 会安装 ESP-IDF 框架以及编译/烧录所需工具（编译器、CMake、Ninja、OpenOCD 等）。装好后，VS Code 扩展会自动读取 EIM 生成的清单文件并发现已安装版本。

#### 3.1 从 VS Code 打开 EIM（推荐）

1. 按 `Ctrl+Shift+P`（macOS：`Shift+Command+P`）打开命令面板。
2. 输入并选择：**ESP-IDF: Open ESP-IDF Installation Manager**。
3. 稍等片刻，会看到加载提示，随后启动 EIM。
4. 在桌面环境下，EIM 通常以 **图形界面（GUI）** 打开；按窗口提示一步步操作即可。
5. 选择要安装的 **ESP-IDF 版本**：
   - 本工程要求 **>= 5.5**
   - 建议安装 **v5.5.4**（本仓库验证版本）
6. 按提示选择安装路径（路径尽量短、**不要有空格**、尽量纯英文）。
7. 确认后开始下载与安装。首次安装可能较久，请保持网络畅通；国内网络可优先使用乐鑫下载源（若 EIM / 文档提供 Download 选项）。
8. 安装完成后再回到 VS Code。

#### 3.2 选择当前使用的 ESP-IDF 版本

若你安装了多个版本：

1. 命令面板执行：**ESP-IDF: Select Current ESP-IDF Version**
2. 在列表中选择本工程要用的版本（例如 **5.5.4**）
3. 扩展会把当前工程需要的环境变量配置好

> Windows 上 EIM 清单默认通常在 `C:\Espressif\tools\eim_idf.json`；macOS/Linux 通常在 `$HOME/.espressif/tools/eim_idf.json`。一般无需手改；若扩展找不到安装，可在 VS Code 设置里检查 `idf.eimIdfJsonPath`。

#### 3.3 检查安装是否正常

1. 命令面板执行：**ESP-IDF: Doctor Command**
2. 查看输出，确认没有红色错误
3. 也可看 VS Code 状态栏是否显示已识别的 ESP-IDF 版本

#### 3.4 可选：单独下载 EIM

如果不想从扩展内启动，也可以先安装独立版 EIM，再用它安装 ESP-IDF：

1. 打开 [ESP-IDF Installation Manager 文档 / 下载页](https://docs.espressif.com/projects/idf-im-ui/en/latest/)
2. 按系统选择安装方式（Windows / macOS / Linux；也可用包管理器或直接下载）
3. 运行 EIM，安装 **ESP-IDF >= 5.5**（建议 5.5.4）
4. 回到 VS Code，执行 **ESP-IDF: Select Current ESP-IDF Version** 选中刚装的版本

#### 3.5 远程 / 无界面环境说明

若你在 **SSH、WSL、Dev Containers、Codespaces** 等环境中使用 VS Code，扩展可能无法弹出 EIM 图形界面，而会改走终端向导（例如 `eim wizard`）。按终端提示选择版本并完成安装即可。详见官方安装文档。

### 4. 准备驱动（Windows 常见）

- 多数板子使用板载 USB-UART 或 USB-JTAG。
- 若设备管理器里没有端口（`COMx`），请安装对应 USB 驱动（常见为 Silicon Labs CP210x、WCH CH340、或乐鑫 USB-JTAG 驱动）。
- 安装后重新插拔 USB，确认出现 `COMx`。

---

## 获取本工程

任选一种方式：

**方式 A：Git 克隆（推荐）**

```bash
git clone <本仓库地址>
cd UEDX46460015-MD50E-IDF
```

**方式 B：下载 ZIP**

1. 在 GitHub 页面点击 **Code -> Download ZIP**。
2. 解压到不包含中文空格特殊符号的路径，例如：`D:\work\UEDX46460015-MD50E-IDF`。
3. 用 VS Code 打开解压后的**根目录**（能看到 `main/` 和根目录 `CMakeLists.txt`）。

> 路径尽量短、纯英文，可减少 Windows 下路径过长导致的编译问题。

---

## 用 VS Code 打开并配置

### 1. 打开文件夹

1. VS Code：**文件 -> 打开文件夹...**
2. 选择本工程根目录。
3. 若提示“是否信任”，选择信任。

### 2. 确认状态栏三项

打开后，底部状态栏应能看到类似信息：

1. **ESP-IDF 版本**（如 5.5.4）
2. **目标芯片**：必须是 `esp32s3`
3. **串口**：如 `COM5`（插上板子后选择）

### 3. 设置目标芯片（第一次很重要）

1. `Ctrl+Shift+P`
2. 选择：**ESP-IDF: Set Espressif device target**
3. 选择 **esp32s3**
4. 等待配置完成（会生成/更新 `sdkconfig`）

> 若以前用别的芯片编译过，切换 target 后建议删掉 `build/` 再编译。

### 4. 选择串口

1. `Ctrl+Shift+P`
2. 选择：**ESP-IDF: Select port to use**
3. 选中板子对应的 `COMx`

---

## 第一次编译

### 图形界面（推荐）

1. 点击 VS Code 底部或侧边的 **Build**（🔧图标），或命令面板执行 **ESP-IDF: Build your project**。
2. 第一次编译会做两件耗时的事：
   - 从 [ESP Component Registry](https://components.espressif.com/) 下载依赖到 `managed_components/`
   - 编译 IDF + LVGL + UI 资源（可能 3 分钟左右，取决于电脑）
3. 成功时终端末尾会出现类似：

```text
Project build complete.
```

### 命令行方式

在已 `export` ESP-IDF 环境的终端中：

```bash
cd /path/to/UEDX46460015-MD50E-IDF
idf.py set-target esp32s3
idf.py build
```

### 第一次编译常见现象（正常）

| 现象 | 说明 |
|------|------|
| 提示 Solving dependencies / Processing dependencies | 正在解析并下载组件，请等待 |
| 生成 `managed_components/`、`dependencies.lock` | 正常，**不要手改**这些内容 |
| 下载很慢或超时 | 检查网络；可稍后重试 `idf.py build` |

成功拉取后，你应能在 `managed_components/` 看到例如：

- `viewesmart__bsp_knob_15_md50et`
- `viewesmart__esp_lcd_touch_cst820`
- `espressif__esp_lcd_co5300`
- `espressif__esp_lvgl_adapter`
- `espressif__button` / `espressif__knob`
- `lvgl__lvgl`

---

## 烧录与串口监视

### 烧录前检查

1. USB 已连接，串口已选对。
2. 若烧录时提示连接失败：按住板上 **Boot** 键再点烧录，或进入下载模式后再松手（视硬件而定）。
3. 关闭占用串口的其他软件（串口助手、旧 Monitor 等）。

### 图形界面

1. 点击 **Flash（⚡）** 烧录。
2. 点击 **Monitor（显示器图标）** 打开串口日志。
3. 也可使用组合按钮 **Flash and Monitor（火苗图标）**。

### 命令行

把 `PORT` 换成你的串口，例如 Windows 的 `COM5`，Linux 的 `/dev/ttyUSB0`：

```bash
idf.py -p PORT flash monitor
```

退出监视器：`Ctrl+]`。

---

## 成功时你会看到什么

1. 屏幕点亮，显示本仓库演示 UI（SquareLine 界面）。
2. 串口日志中有 BSP 初始化成功信息（含分辨率、LVGL 版本等）。
3. 触摸可点击；旋钮左右转、按键可触发 UI 中对应逻辑。

若黑屏 / 花屏 / 无触摸，请先看文末 [常见问题排查](#常见问题排查)。

---

## 工程目录说明

```text
UEDX46460015-MD50E-IDF/
├── CMakeLists.txt              # 工程入口 CMake
├── dependencies.lock           # 组件版本锁定（自动生成，勿手改）
├── partitions.csv              # 自定义分区表（factory 约 3MB）
├── sdkconfig                   # 本地当前配置（编译后生成/修改）
├── sdkconfig.defaults          # 默认配置（LVGL、分区表等）
├── sdkconfig.defaults.esp32s3  # ESP32-S3：Flash/PSRAM 等
├── README.md                   # 英文说明
├── README_CN.md                # 中文说明（本文件）
├── main/                       # 应用代码
│   ├── CMakeLists.txt          # 编译 main.c + ui 源文件
│   ├── idf_component.yml       # 声明 BSP / LVGL 等依赖
│   ├── main.c                  # app_main 入口
│   └── ui/                     # SquareLine 导出的 UI
│       ├── ui.c / ui.h
│       ├── screens/
│       ├── images/
│       └── ...
└── managed_components/         # 组件管理器自动下载（勿手改，可删后重建）
    ├── viewesmart__bsp_knob_15_md50et/
    ├── viewesmart__esp_lcd_touch_cst820/
    └── ...
```

说明：

- **不要**把 BSP 再复制一份到 `components/`，除非你明确要改 BSP 源码做本地调试。
- 本示例已通过 `main/idf_component.yml` 从注册表拉取 BSP。

---

## 依赖说明

`main/idf_component.yml` 关键内容大致如下：

```yaml
dependencies:
  idf: ">=5.5"
  viewesmart/bsp_knob_15_md50et: "^1.0.2"
  lvgl/lvgl:
    version: "^8.3.11"   # 与当前演示 UI（LVGL 8）匹配
    public: true
```

| 依赖 | 作用 |
|------|------|
| `viewesmart/bsp_knob_15_md50et` | 板级初始化：LCD / 触摸 / LVGL adapter / 旋钮 / 按键 / 亮度 |
| `lvgl/lvgl` | GUI 库（主版本必须与 UI 导出一致） |
| BSP 传递依赖 | CO5300、CST820、`esp_lvgl_adapter`、`button`、`knob` 等会自动下载 |

`main/CMakeLists.txt` 中通过下面名称链接 managed 组件（双下划线是命名空间规则）：

```cmake
REQUIRES
    viewesmart__bsp_knob_15_md50et
    lvgl
    esp_lvgl_adapter
```

---

## 示例代码入口

核心逻辑在 `main/main.c`：

```c
#include "bsp_knob_15_md50et.h"
#include "ui.h"

void app_main(void)
{
    bsp_knob_15_md50et_handles_t handles = {0};
    ESP_ERROR_CHECK(bsp_knob_15_md50et_init(&handles));

    bsp_knob_15_md50et_register_knob_cb(LVGL_knob_event);
    bsp_knob_15_md50et_register_button_cb(LVGL_button_event);

    if (bsp_knob_15_md50et_lock(-1) == ESP_OK) {
        ui_init();
        bsp_knob_15_md50et_unlock();
    }
}
```

规则：

1. 先 `bsp_knob_15_md50et_init()`。
2. 所有 LVGL API（含 `ui_init()`、改控件）必须夹在 `lock` / `unlock` 之间。
3. 旋钮/按键回调里如果要操作 LVGL，同样先 `lock`。

调节亮度示例：

```c
ESP_ERROR_CHECK(bsp_knob_15_md50et_set_brightness(80));  /* 0~100 */
```

---

## 替换 / 修改 SquareLine UI

1. 打开 SquareLine Studio，新建或打开工程，分辨率设为 **466 × 466**。
2. LVGL 版本选择与本工程一致（当前示例为 **LVGL 8.x**）。
3. 导出到 `main/ui/`（覆盖生成文件时注意保留你自己改过的事件文件，如有）。
4. 本工程 `main/CMakeLists.txt` 已用通配符编译 `ui/**/*.c`，一般无需改 CMake。
5. **不要**为了“居中对齐”去整体平移控件坐标：驱动宽度是 472，且不使用 `set_gap`；SquareLine 继续按 466×466 设计即可。
6. 重新 `build` / `flash`。

若 UI 资源变大导致烧录报分区不足：确认 `sdkconfig` 使用了自定义 `partitions.csv`（本仓库默认 `factory` 为 **3MB**）。

---

## 选择 LVGL 8 或 9

BSP 支持 LVGL 8/9，但**应用 UI 只能选一个主版本**。

在 `main/idf_component.yml`：

```yaml
lvgl/lvgl:
  version: "^8.3.11"   # 当前演示 UI
  # version: "^9"      # 仅当你的 UI 按 LVGL 9 导出时启用
  public: true
```

切换主版本后建议：

1. 删除 `managed_components/lvgl__lvgl`
2. 删除 `dependencies.lock`
3. 删除 `build/`
4. 重新 `idf.py set-target esp32s3`（如需要）并 `idf.py build`
5. 同步替换 `main/ui/` 为对应主版本导出的代码

---

## 引脚一览

定义在 BSP 头文件 `bsp_knob_15_md50et_board.h`（位于 managed 组件 include 目录）：

| 功能 | GPIO |
|------|------|
| LCD CS | 12 |
| LCD PCLK | 10 |
| LCD D0 / D1 / D2 / D3 | 13 / 11 / 14 / 9 |
| LCD RST | 8 |
| 面板供电（须在 LCD init 前为高） | 17 |
| 触摸 SCL / SDA | 3 / 1 |
| 触摸 RST / INT | 2 / 4 |
| 编码器 A / B | 6 / 5 |
| 按键 | 0 |

---

## BSP API 摘要

| API | 说明 |
|-----|------|
| `bsp_knob_15_md50et_init()` | 初始化供电、LCD、触摸、LVGL、旋钮、按键 |
| `bsp_knob_15_md50et_lock` / `unlock` | LVGL 线程安全锁 |
| `bsp_knob_15_md50et_set_brightness(0~100)` | 面板亮度（QSPI 下请用此 API） |
| `bsp_knob_15_md50et_backlight_on` / `off` | GPIO17 面板供电开关 |
| `bsp_knob_15_md50et_register_knob_cb` | 旋钮回调（`KNOB_LEFT` / `KNOB_RIGHT`） |
| `bsp_knob_15_md50et_register_button_cb` | 按键回调（按下/抬起/长按保持） |

更完整的说明见组件文档：

- 注册表：[viewesmart/bsp_knob_15_md50et](https://components.espressif.com/components/viewesmart/bsp_knob_15_md50et)
- 源码：[GitHub bsp_knob_15_md50et](https://github.com/VIEWESMART/Viewe-esp32-components/tree/main/bsp/bsp_knob_15_md50et)

---

## 常见问题排查

### A. 环境 / 编译类

| 现象 | 处理建议 |
|------|----------|
| 打不开 EIM / Installation Manager | 确认已安装最新 **Espressif IDF** 扩展；更新扩展后重开 VS Code；也可先装独立版 [EIM](https://docs.espressif.com/projects/idf-im-ui/en/latest/) |
| EIM 下载很慢或失败 | 换网络 / 代理；优先使用乐鑫下载源；杀毒软件放行 Espressif 安装目录 |
| 扩展找不到已安装的 IDF | 执行 **ESP-IDF: Select Current ESP-IDF Version**；检查 `eim_idf.json` 或设置 `idf.eimIdfJsonPath` |
| 找不到 `idf.py` / 扩展未激活 | 用 EIM 安装 IDF 后执行 **ESP-IDF: Select Current ESP-IDF Version**，再跑 **ESP-IDF: Doctor Command**；用扩展自带的 IDF 终端 |
| `Set target` 后编译错误残留 | 删除 `build/` 再编译 |
| `Version solving failed` / 找不到组件 | 检查网络能否访问 components.espressif.com；确认 `main/idf_component.yml` 中 BSP 版本存在（如 `^1.0.2`） |
| 依赖冲突（button / adapter 版本） | 使用 BSP **>= 1.0.2**；删除 `dependencies.lock` 与 `managed_components/` 后重编 |
| 编译报 app 太大 / 分区不够 | 确认启用自定义分区 `partitions.csv`（3M factory） |
| 第一次特别慢 | 正常；LVGL + 图片资源编译耗时 |

### B. 烧录 / 串口类

| 现象 | 处理建议 |
|------|----------|
| 没有 COM 口 | 换数据线、装 USB 驱动、换 USB 口 |
| `Failed to connect` | 按住 Boot 再烧录；确认波特率/驱动；关闭占用串口的程序 |
| Monitor 乱码 | 确认监视波特率与工程一致（常见 115200） |

### C. 显示 / 触摸 / 输入类

| 现象 | 处理建议 |
|------|----------|
| 黑屏 | 确认是本板固件；GPIO17 已在 BSP 内于 LCD init 前拉高；勿替换掉板级 CO5300 初始化表 |
| 左边留白 / 右边绿线 | 驱动分辨率保持 **472×466**，**不要** `set_gap` |
| 亮度没变化 | 调用 `bsp_knob_15_md50et_set_brightness()`，不要对 QSPI 直接写 `0x51` |
| 触摸无反应 | 查看日志是否 CST820 初始化失败；检查 I2C 接线/模组型号 |
| 旋钮/按键无反应 | 确认已 `register_*_cb`；回调里操作 LVGL 前先 `lock` |

### D. 想“干净重来”

在工程根目录删除后重编（会重新下载组件）：

```text
build/
managed_components/
dependencies.lock
```

然后：

```bash
idf.py set-target esp32s3
idf.py build
```

---

## 许可证与相关链接

- 示例应用代码：见各源文件 SPDX（如 `main/main.c` 为 CC0-1.0）
- BSP / 触摸组件：Apache-2.0（以组件仓库为准）
- 第三方组件：遵循各自许可证

相关链接：

- BSP 组件：[viewesmart/bsp_knob_15_md50et](https://components.espressif.com/components/viewesmart/bsp_knob_15_md50et)
- 触摸组件：[viewesmart/esp_lcd_touch_cst820](https://components.espressif.com/components/viewesmart/esp_lcd_touch_cst820)
- 组件源码单仓：[Viewe-esp32-components](https://github.com/VIEWESMART/Viewe-esp32-components)
- ESP-IDF 编程指南：[https://docs.espressif.com/projects/esp-idf/](https://docs.espressif.com/projects/esp-idf/)
- VS Code 插件安装（含 EIM）：[Install ESP-IDF and Tools](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/installation.html)
- EIM 文档：[ESP-IDF Installation Manager](https://docs.espressif.com/projects/idf-im-ui/en/latest/)
- VS Code 插件总览：[Espressif IDF Extension](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/)

欢迎 Issue / PR。若你是第一次接触 ESP-IDF，建议先完整走通本文“环境准备 -> 编译 -> 烧录”三步，再开始改 UI。

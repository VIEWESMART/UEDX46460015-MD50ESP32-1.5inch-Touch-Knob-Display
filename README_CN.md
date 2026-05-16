<h1 align = "center">UEDX46460015-MD50ESP32 ESP32 1.5寸 AMOLED 触摸旋钮显示屏</h1>
 
 * **English(./README.md)**
   
<p align="center" width="90%">
    <img src="image/Main.png" alt="">
</p>

-   **UEDX46460015-MD50ET**
    ---
    由 **ESP32-S3** 驱动的**智能旋钮显示屏**。  
    配备 1.5 英寸 **466×466** AMOLED 显示屏 (QSPI)、电容触摸、旋转编码器和按键。  
    非常适合物联网控制面板、智能家居设备和工业 HMI。

## 1. 简介

**UEDX46460015-MD50ET** 是一款专为旋钮式人机界面应用设计的紧凑型智能显示模组。  
它集成了 1.5 英寸 AMOLED 显示屏（466×466 像素）、电容式触摸面板、旋转编码器和一个硬件按键。

基于 **ESP32‑S3‑R8**（16 MB Flash，8 MB Octal PSRAM），它提供 Wi‑Fi 和蓝牙 5 (LE) 连接，并支持使用 **Arduino**、**ESP‑IDF** 和 **PlatformIO** 进行开发。

### 1.1 产品特性

* **处理器**:
    * **ESP32-S3**：Xtensa® 双核 32 位 LX7 MCU @ 240 MHz。
    * 集成 2.4 GHz Wi‑Fi (802.11 b/g/n) 和 蓝牙 5 (LE)。
* **存储器**:
    * **16 MB** Quad SPI Flash。
    * **8 MB** Octal SPI PSRAM。
* **显示与触摸**:
    * **屏幕**：1.5 英寸 IPS AMOLED (466×466 分辨率)。
    * **接口**：QSPI。
    * **驱动 IC**：CO5300AF‑42。
    * **触摸**：电容式多点触控 (CST820)，通过 I²C 接口。
* **外设**:
    * **编码器**：旋转编码器 (PHA/PHB)，用于精确旋钮输入。
    * **按键**：硬件按键（与 BOOT 共用）。
    * **连接**：USB‑C（用于编程和调试的 USB/UART），UART 扩展接口 (FPC)。
    * **扩展 FPC**：额外 GPIO、5V、GND、UART0。

### 1.2 应用场景

* 智能家居控制旋钮
* 工业旋钮式 HMI
* 物联网设备拨盘

---

## 2. 硬件描述

### 2.1 模块概述

板卡主要功能模块如下：

| 组件 | 描述 |
| :--- | :--- |
| **ESP32‑S3‑R8** | 主 SoC（16 MB Flash / 8 MB Octal PSRAM）。 |
| **1.5" AMOLED** | 466×466 像素显示屏，由 QSPI 驱动 (CO5300AF‑42)。 |
| **CST820** | 电容式触摸控制器 (I²C)。 |
| **旋转编码器** | 2 相编码器 (PHA/PHB)，用于旋钮旋转检测。 |
| **按键** | BOOT 按键（也用于固件下载）。 |
| **USB‑C** | 编程、调试（通过 USB 的 UART）和供电 (5V)。 |
| **FPC 连接器** | 额外的电源、UART0 和 UART2 信号。 |

### 2.2 GPIO 定义（引脚分配）

#### **显示屏 (QSPI)**
| 显示屏引脚 | ESP32‑S3 引脚 |
| :---: | :---: |
| CS | IO12 |
| PCLK | IO10 |
| DATA0 | IO13 |
| DATA1 | IO11 |
| DATA2 | IO14 |
| DATA3 | IO9 |
| RST | IO8 |
| 背光 | IO17 |

#### **触摸 (CST820)**
| 触摸引脚 | ESP32‑S3 引脚 |
| :---: | :---: |
| SDA | IO0 |
| SCL | IO1 |
| RST | IO3 |
| INT | IO4 |

#### **按键**
| 按键引脚 | ESP32‑S3 引脚 |
| :---: | :---: |
| BOOT | IO0 |

#### **编码器**
| 编码器引脚 | ESP32‑S3 引脚 |
| :---: | :---: |
| PHA | IO6 |
| PHB | IO5 |

#### **USB / UART**
| USB/UART 引脚 | ESP32‑S3 引脚 |
| :---: | :---: |
| USB‑DN | IO19 |
| USB‑DP | IO20 |

#### **FPC 连接器引脚定义**
| FPC 引脚 | 适配器信号 | ESP32‑S3 引脚 |
| :---: | :--- | :--- |
| 1 | 5V | 5V |
| 2 | PB7 | – |
| 3 | GND | GND |
| 4 | RX2 | GPIO40 |
| 5 | TX2 | GPIO39 |
| 6 | RX1 | U0RXD / GPIO44 |
| 7 | TX1 | U0TXD / GPIO43 |
| 8 | NC | CHIP‑EN |
| 9 | D+ (USB‑DP) | GPIO20 |
|10 | D‑ (USB‑DN) | GPIO19 |

### 2.3 机械尺寸

详细尺寸请参阅产品规格书。

---

## 3. 软件

我们为 **Arduino**、**PlatformIO** 和 **ESP‑IDF** 框架提供全面支持，并提供预移植的 **LVGL** 示例。

### 3.1 软件示例

示例可在 [GitHub 仓库](https://github.com/VIEWESMART/ESP32-1.5inch-AMOLED-Knob) （examples 文件夹）中找到。

| 框架 | 示例路径 | 描述 |
| :---: | :--- | :--- |
| **Arduino** | `examples/arduino/gui/lvgl_v8` | **LVGL 基准测试**：LVGL v8 使用示例，可直接在 Arduino IDE 中打开。 |
| **ESP‑IDF** | `examples/esp_idf` | **LVGL 移植**：在 ESP‑IDF 中移植并使用 LVGL 的示例。 |
| **PlatformIO** | `examples/platformio/lvgl_v8_port` | **LVGL v8 移植**：LVGL v8 使用示例。 |

### 3.2 快速入门

#### 3.2.1 准备工作

* **硬件**：UEDX46460015‑MD50ET 开发板，USB‑C 数据线。
* **软件**：VS Code (ESP‑IDF v5.3+) 或 Arduino IDE (v2.0+) 或 VS Code (PlatformIO)。
* **库**：Arduino IDE 和 PlatformIO 需要以下库。

| 库 | 版本 | 描述 |
| :--- | :--- | :--- |
| `ESP32_Display_Panel` | `1.0.3+` | Espressif 提供，驱动屏幕所必需。 |
| `ESP32_IO_Expander` | *Arduino 自动选择* | `ESP32_Display_Panel` 的依赖库。 |
| `esp-lib-utils` | *Arduino 自动选择* | `ESP32_Display_Panel` 的依赖库。 |
| `lvgl` | `8.4.0` | 开源嵌入式图形库。 |

#### 3.2.2 ESP‑IDF 设置

1.  **打开示例**  
    * 从 GitHub 下载仓库（点击绿色 “Code” 按钮并选择 “Download ZIP”，或克隆仓库）。  
    * 使用已安装 ESP‑IDF 扩展的 VS Code 打开示例文件夹（如 `examples/esp_idf`）。

2.  **编译和上传**  
    * 点击 **构建** 图标编译项目。  
    * 通过 USB‑C 连接开发板。  
    * 点击 **上传** 图标烧录固件。

#### 3.2.3 Arduino 设置 ([新手教程](https://github.com/VIEWESMART/VIEWE-Tutorial/blob/main/Arduino%20Tutorial/Arduino%20Getting%20Started%20Tutorial.md))

1.  **安装 Arduino IDE**  
    * 下载并安装 [Arduino IDE](https://www.arduino.cc/en/software) (推荐 v2.0+)。

2.  **安装 ESP32 开发板包**  
    * 打开 Arduino IDE，进入 **文件 > 首选项**。  
    * 在“附加开发板管理器网址”中添加以下 URL：  
      `https://espressif.github.io/arduino-esp32/package_esp32_index.json`  
    * 进入 **工具 > 开发板 > 开发板管理器**，搜索 `esp32`（由 Espressif 提供）并安装版本 **3.0.0+**。

3.  **安装库**  
    * 进入 **项目 > 加载库 > 库管理器**。  
    * 搜索 `ESP32_Display_Panel`（由 Espressif 提供）并安装版本 **1.0.3+**。当提示安装依赖时，点击 **INSTALL ALL** 全部安装。  
    * 安装 `lvgl` (版本 **8.4.0**)。

4.  **打开示例**  
    * 导航到 **文件 > 示例 > ESP32_Display_Panel**。  
    * 选择 **Arduino > gui > lvgl_v8 > simple_port**。

5.  **选择开发板**  
    * 目标板：**ESP32S3 Dev Module**。  
    * 配置以下选项：
        * **Flash Size**：16MB (128Mb)
        * **Partition Scheme**：16M Flash (3MB APP/9.9MB FATFS)
        * **PSRAM**：**OPI PSRAM**（此项至关重要）

6.  **配置支持的板卡**  
    * 在示例中，打开文件 `esp_panel_board_supported_conf.h`。  
    * 将宏 `ESP_PANEL_BOARD_DEFAULT_USE_SUPPORTED` 设置为 `1`。  
    * 找到 `// #define BOARD_VIEWE_UEDX46460015_MD50ET` 这一行，删除 `//` 以取消注释。  
    * 确保没有同时启用其他板卡定义。

7.  **接口特定配置**  
    * 由于板卡使用 **QSPI** 接口，请打开 `lv_conf.h`（或示例中等效的 `lv_conf.h` 文件）并将 `LV_COLOR_16_SWAP` 设置为 `1`。  
    * **不要** 修改 `LVGL_PORT_AVOID_TEARING_MODE` 或 `LVGL_PORT_ROTATION_DEGREE`（这些仅适用于 RGB/MIPI 显示屏）。

8.  **选择端口并上传**  
    * 连接开发板，然后进入 **工具 > 端口** 选择正确的 COM 端口。  
    * 点击 **验证** (✓) 按钮进行编译。  
    * 点击 **上传** (→) 按钮进行烧录。

> [!TIP]
> **配置提示**  
> * 在 `esp_panel_board_supported_conf.h` 中，确保取消注释：`#define BOARD_VIEWE_UEDX46460015_MD50ET`。  
> * 不要同时启用 `ESP_PANEL_BOARD_DEFAULT_USE_SUPPORTED` 和 `ESP_PANEL_BOARD_DEFAULT_USE_CUSTOM`。  
> * 不能同时启用多个板卡定义。

#### 3.2.4 PlatformIO 设置

1.  **打开示例**  
    * 下载仓库，并在已安装 PlatformIO 扩展的 VS Code 中打开 `examples/platformio/lvgl_v8_port` 文件夹。

2.  **选择板卡环境**  
    * 打开 `platformio.ini` 文件。  
    * 将 `default_envs` 行修改为 `BOARD_VIEWE_UEDX46460015_MD50ET`。

3.  **配置示例**  
    * (QSPI 接口) 在 `lv_conf.h` 中，将 `LV_COLOR_16_SWAP` 设置为 `1`。  
    * 保留 `LVGL_PORT_AVOID_TEARING_MODE` 和 `LVGL_PORT_ROTATION_DEGREE` 不变。

4.  **编译并上传**  
    * 点击 **✓** (编译) 按钮。  
    * 连接开发板，然后点击 **→** (上传) 按钮。

### 3.3 固件下载（手动烧录）

如果您需要手动烧录预编译的固件：

1.  打开“Flash Download Tool”（可在 tools 文件夹中找到，或从 Espressif 官网下载）。
2.  选择芯片型号（**ESP32‑S3**）和正确的下载方式。
3.  从 `firmware` 文件夹加载固件文件，并按照固件说明中的偏移地址进行配置。
4.  连接开发板并开始下载。  
    *如果烧录失败，请在给设备上电时按住 **BOOT** 按钮，然后重试。*

<p align="center" width="100%">
    <img src="image/10.png" alt="example">
    <img src="image/11.png" alt="example">
</p>


## 常见问题

* 问：阅读以上教程后，我仍然不知道如何构建编程环境。我该怎么办？
* 答：如果您在阅读上述教程后仍不了解如何搭建环境，可以参考 [VIEWE-FAQ]() 文档说明进行搭建。

<br />

* 问：为什么打开 Arduino IDE 时会提示我更新库文件？我应该更新吗？
* 答：选择不更新库文件。不同版本的库文件可能互不兼容，因此不建议更新库文件。

<br />

* 问：为什么我板子上的 “Uart” 接口没有串口数据输出？是坏的不能用吗？
* 答：默认工程配置使用 USB 接口作为 Uart0 串口输出以进行调试。 “Uart” 接口连接的是 Uart0，因此在未配置的情况下不会输出数据。<br />对于 PlatformIO 用户，请打开工程文件 “platformio.ini”，将 “build_flags = xxx” 中的选项从 “-D ARDUINO_USB_CDC_ON_BOOT=true” 修改为 “-D ARDUINO_USB_CDC_ON_BOOT=false”，以启用外部 “Uart” 接口。<br />对于 Arduino 用户，打开 “工具” 菜单，选择 “USB CDC On Boot: Disabled” 以启用外部 “Uart” 接口。

<br />

* 问：为什么我的板子一直下载程序失败？
* 答：请按住 “BOOT” 按钮再尝试下载程序。

## 原理图
<p align="center" width="100%">
    <img src="schematic/1.5%20MD50E%20SCH.V2.0_00.png" alt="example">
</p>

## 资料
[产品规格书](information/UEDX48480021-MD80E%20V3.3%20SPEC.pdf)

[显示屏数据手册](information/UE021WV-RB40-L002B.pdf)

[按键](information/6x6Silent%20switch.pdf)

[编码器](information/C219783_%E6%97%8B%E8%BD%AC%E7%BC%96%E7%A0%81%E5%99%A8_EC28A1520401_%E8%A7%84%E6%A0%BC%E4%B9%A6_WJ239718.PDF)

# LVGL ported to VIEWE 1.5" Touch Knob

## Overview

The Viewe Touch Knob Display, designed and developed by Viewe Display, features a high-resolution 466x466 AMOLED panel with 1000 cd/m² brightness, a rotary knob with an integrated push button, and capacitive touch input. Powered by an ESP32-S3 (240 MHz) with 8 MB RAM and 16 MB Flash, it supports Wi-Fi, BLE 5, and BLE Mesh. Compatible with Arduino, ESP-IDF, and LVGL, it offers UART and USB interfaces. Ideal for IoT and AIoT projects, the touch-enabled knob display is perfect for creating intuitive control panels, smart home hubs, industrial interfaces, and embedded dashboards.

## Buy

You can purchase Viewe Touch Knob Display from https://viewedisplay.com/product/esp32-1-5-inch-466x466-round-amoled-knob-display-touch-screen-arduino-lvgl/

## Benchmark

The display is driven using QSPI interface. Two display LVGL draw buffers are used (472x60x2) with `LV_DISPLAY_RENDER_MODE_PARTIAL` mode.

Check out Viewe Touch Knob Display in action, running LVGL's benchmark demo:
<a href="https://www.youtube.com/watch?v=uHdSQY_k2Mg"> <img src="assets/preview.png"  width="70%"/> </a>

### Benchmark Summary (9.3.0 )

| Name                      | Avg. CPU  | Avg. FPS  | Avg. time | render time   | flush time    |
| ------------------------- | --------- | --------- | --------- | ------------- | ------------- |
| Empty screen              | 69%       | 27        | 22        | 7             | 15            |
| Moving wallpaper          | 70%       | 28        | 23        | 13            | 10            |
| Single rectangle          | 8%        | 28        | 0         | 0             | 0             |
| Multiple rectangles       | 37%       | 28        | 12        | 8             | 4             |
| Multiple RGB images       | 24%       | 28        | 6         | 5             | 1             |
| Multiple ARGB images      | 45%       | 28        | 14        | 13            | 1             |
| Rotated ARGB images       | 44%       | 28        | 14        | 14            | 0             |
| Multiple labels           | 55%       | 28        | 18        | 15            | 3             |
| Screen sized text         | 96%       | 12        | 79        | 72            | 7             |
| Multiple arcs             | 22%       | 28        | 4         | 4             | 0             |
| Containers                | 22%       | 28        | 8         | 7             | 1             |
| Containers with overlay   | 94%       | 25        | 35        | 29            | 6             |
| Containers with opa       | 29%       | 28        | 12        | 11            | 1             |
| Containers with opa_layer | 42%       | 28        | 17        | 17            | 0             |
| Containers with scrolling | 95%       | 23        | 39        | 33            | 6             |
| Widgets demo              | 99%       | 14        | 54        | 49            | 5             |
| All scenes avg.           | 53%       | 25        | 21        | 18            | 3             |

## Specification

### CPU and Memory
- **MCU:** ESP32-S3 240Mhz
- **RAM:** 512 KB internal, 8MB external PSRAM
- **Flash:** 16MB External Flash
- **GPU:** None

### Display and Touch
- **Resolution:** 466x466
- **Display Size:** 1.5"
- **Interface:** QSPI (CO5300AF-42)
- **Color Depth:** 16-bit
- **Technology:** AMOLED
- **DPI:** 439px/inch
- **Touch Pad:** Capacitive (CST816S)

### Connectivity
- Integrated Rotary Knob
- Integrated Push Button

## Getting started

### Hardware setup
- First connect the FPC from the display to the extension board then connect a Micro USB cable to the extension board.

### Software setup
- Install CH340G drivers for UART chip
- Install the VS Code IDE & PlatformIO extension

### Run the project
- Clone this repository: 
- Open the code folder using VS Code. PlatformIO needs to be installed. ESP-IDF will automatically be installed if not present
- Configure the project. Click on the gear icon (SDK Configuration editor)
- Build the project. Click on the wrench icon (Build Project)
- Run or Debug. Alternatively click on the fire icon (ESP-IDF: Build, Flash & Monitor) to run flash and debug the code

### Debugging
- Debug using ESP Logging Library `ESP_LOGE, ESP_LOGI ...`
- After flashing (ESP-IDF: Build, Flash & Monitor), a terminal will appear showing the logs


## Contribution and Support

If you find any issues with the development board feel free to open an Issue in this repository. For LVGL related issues (features, bugs, etc) please use the main [lvgl repository](https://github.com/lvgl/lvgl).

If you found a bug and found a solution too please send a Pull request. If you are new to Pull requests refer to [Our Guide](https://docs.lvgl.io/master/CONTRIBUTING.html#pull-request) to learn the basics.
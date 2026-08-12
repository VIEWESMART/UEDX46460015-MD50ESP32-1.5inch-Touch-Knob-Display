# UEDX46460015-MD50ET ESP-IDF Example

Open-source ESP-IDF example for the **UEDX46460015-MD50ET** 1.5" round AMOLED knob display (ESP32-S3): bring up LCD, touch, encoder/button, and run a SquareLine LVGL UI.

Board support is published as a registry BSP:

- BSP: [viewesmart/bsp_knob_15_md50et](https://components.espressif.com/components/viewesmart/bsp_knob_15_md50et) (`^1.0.2` recommended)
- Touch: [viewesmart/esp_lcd_touch_cst820](https://components.espressif.com/components/viewesmart/esp_lcd_touch_cst820) (pulled by the BSP)

[中文说明](./README_CN.md)

---

## Contents

1. [What you get](#what-you-get)
2. [Hardware](#hardware)
3. [Software setup (beginners)](#software-setup-beginners)
4. [Get this project](#get-this-project)
5. [Open and configure in VS Code](#open-and-configure-in-vs-code)
6. [First build](#first-build)
7. [Flash and monitor](#flash-and-monitor)
8. [What success looks like](#what-success-looks-like)
9. [Project layout](#project-layout)
10. [Dependencies](#dependencies)
11. [Application entry](#application-entry)
12. [Replace / edit the SquareLine UI](#replace--edit-the-squareline-ui)
13. [Choose LVGL 8 or 9](#choose-lvgl-8-or-9)
14. [Pinout](#pinout)
15. [BSP API summary](#bsp-api-summary)
16. [Troubleshooting](#troubleshooting)
17. [License and links](#license-and-links)

---

## What you get

After running this example you can:

- Show an LVGL UI on the 1.5" round AMOLED (demo UI included)
- Use the touchscreen
- Use the rotary encoder and the GPIO0 button
- Set panel brightness (0~100) through the BSP API

Verified with **ESP-IDF v5.5.4**, target **esp32s3**.

---

## Hardware

| Item | Spec |
|------|------|
| Module | UEDX46460015-MD50ET (folder name may say MD50E; same board family) |
| MCU | ESP32-S3 with **16 MB Flash + Octal PSRAM** (defaults assume this) |
| LCD | 1.5" round AMOLED, CO5300, QSPI |
| Touch | CST820, I2C |
| Input | Rotary encoder + button (GPIO0, often also Boot) |
| Cable | Data-capable USB cable |
| Host OS | Windows / macOS / Linux (steps below use Windows + VS Code) |

Display geometry (important):

| Use | Size |
|------|------|
| Driver / LVGL buffer | **472 x 466** |
| SquareLine design | **466 x 466** |
| `esp_lcd_panel_set_gap()` | **Do not use** |

---

## Software setup (beginners)

Recommended: **Visual Studio Code + Espressif IDF extension**, and install the toolchain with **EIM (ESP-IDF Installation Manager / Espressif Installation Manager)**. This is the current official flow and replaces the older "Configure ESP-IDF extension" wizard.

Official docs:

- [Install ESP-IDF and Tools (VS Code extension)](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/installation.html)
- [ESP-IDF Installation Manager](https://docs.espressif.com/projects/idf-im-ui/en/latest/)

### 1. Install VS Code

Download and install from [https://code.visualstudio.com/](https://code.visualstudio.com/).

### 2. Install the Espressif IDF extension

1. Open Extensions (`Ctrl+Shift+X` on Windows/Linux, `Shift+Command+X` on macOS).
2. Search for **ESP-IDF** or **Espressif IDF**.
3. Install the extension by **Espressif Systems**.
4. If a setup prompt appears, you can dismiss it and continue with EIM below.

### 3. Install ESP-IDF with EIM (>= 5.5)

EIM installs the ESP-IDF framework and required tools (compiler, CMake, Ninja, OpenOCD, etc.). After that, the VS Code extension auto-discovers installs via EIM's manifest file.

#### 3.1 Open EIM from VS Code (recommended)

1. Open the Command Palette (`Ctrl+Shift+P` / `Shift+Command+P`).
2. Run **ESP-IDF: Open ESP-IDF Installation Manager**.
3. Wait for the loading notification; EIM should start.
4. On a desktop machine, EIM usually opens as a **GUI** wizard—follow the on-screen steps.
5. Choose an **ESP-IDF version**:
   - This project needs **>= 5.5**
   - Recommended: **v5.5.4** (verified with this repo)
6. Pick an install path (short path, **no spaces**, ASCII preferred).
7. Confirm and wait for download/install (first run can take a while). In China, prefer Espressif download mirrors when offered.
8. Return to VS Code when finished.

#### 3.2 Select the active ESP-IDF version

If multiple versions are installed:

1. Command Palette -> **ESP-IDF: Select Current ESP-IDF Version**
2. Select the version for this project (for example **5.5.4**)
3. The extension stores the setup for the current workspace

> Default `eim_idf.json` locations: `C:\Espressif\tools\eim_idf.json` on Windows, `$HOME/.espressif/tools/eim_idf.json` on macOS/Linux. Usually no manual edit is needed; if discovery fails, check `idf.eimIdfJsonPath` in VS Code settings.

#### 3.3 Verify the install

1. Run **ESP-IDF: Doctor Command**
2. Fix any red errors before continuing
3. Confirm the status bar shows a valid ESP-IDF version

#### 3.4 Optional: install EIM standalone

You can also install EIM first, then use it to install ESP-IDF:

1. Open the [ESP-IDF Installation Manager docs / download](https://docs.espressif.com/projects/idf-im-ui/en/latest/)
2. Install EIM for your OS
3. Use EIM to install **ESP-IDF >= 5.5** (recommended **5.5.4**)
4. In VS Code, run **ESP-IDF: Select Current ESP-IDF Version** and pick that install

#### 3.5 Remote / headless note

In **SSH, WSL, Dev Containers, Codespaces**, or browser-based VS Code, the extension may run a terminal wizard (for example `eim wizard`) instead of the GUI. Follow the terminal prompts. See the official installation docs for details.

### 4. USB serial driver (Windows)

If no `COMx` port appears, install the USB-UART / USB-JTAG driver for your board (CP210x, CH340, Espressif USB-JTAG, etc.), then replug the cable.

---

## Get this project

**Option A: git clone**

```bash
git clone <this-repo-url>
cd UEDX46460015-MD50E-IDF
```

**Option B: Download ZIP**

1. GitHub -> **Code -> Download ZIP**.
2. Extract to a short ASCII path, e.g. `D:\work\UEDX46460015-MD50E-IDF`.
3. In VS Code, open that root folder (must contain `main/` and root `CMakeLists.txt`).

---

## Open and configure in VS Code

1. **File -> Open Folder...** and select the project root.
2. Trust the workspace if prompted.
3. Check the status bar for: ESP-IDF version, target **esp32s3**, and serial port.
4. Set target: Command Palette -> **ESP-IDF: Set Espressif device target** -> `esp32s3`.
5. Select port: **ESP-IDF: Select port to use**.

If you previously built for another target, delete `build/` before rebuilding.

---

## First build

### UI buttons

Click **Build** (or run **ESP-IDF: Build your project**).

The first build will:

1. Download dependencies into `managed_components/` from the ESP Component Registry
2. Compile IDF + LVGL + UI assets (can take several minutes)

Success ends with:

```text
Project build complete.
```

### CLI

```bash
cd /path/to/UEDX46460015-MD50E-IDF
idf.py set-target esp32s3
idf.py build
```

After a successful resolve you should see folders such as:

- `managed_components/viewesmart__bsp_knob_15_md50et`
- `managed_components/viewesmart__esp_lcd_touch_cst820`
- `managed_components/espressif__esp_lcd_co5300`
- `managed_components/espressif__esp_lvgl_adapter`
- `managed_components/lvgl__lvgl`

Do **not** hand-edit `managed_components/` or `dependencies.lock`.

---

## Flash and monitor

1. Connect USB and select the correct port.
2. If connect fails, hold **Boot** while starting flash (board-dependent).
3. Click **Flash**, then **Monitor** (or Flash and Monitor).

CLI example:

```bash
idf.py -p PORT flash monitor
```

Exit monitor: `Ctrl+]`.

---

## What success looks like

1. The round display shows the demo UI.
2. Serial log shows BSP init success (resolution / LVGL major).
3. Touch, encoder, and button interact with the UI.

If not, see [Troubleshooting](#troubleshooting).

---

## Project layout

```text
UEDX46460015-MD50E-IDF/
├── CMakeLists.txt
├── dependencies.lock           # auto-generated lockfile
├── partitions.csv              # custom table (~3MB factory)
├── sdkconfig / sdkconfig.defaults*
├── README.md / README_CN.md
├── main/
│   ├── CMakeLists.txt
│   ├── idf_component.yml       # pulls BSP + pins LVGL major
│   ├── main.c
│   └── ui/                     # SquareLine export
└── managed_components/         # downloaded deps (do not edit)
```

This example does **not** keep a local copy of the BSP under `components/`. It pulls `viewesmart/bsp_knob_15_md50et` from the registry.

---

## Dependencies

From `main/idf_component.yml`:

```yaml
dependencies:
  idf: ">=5.5"
  viewesmart/bsp_knob_15_md50et: "^1.0.2"
  lvgl/lvgl:
    version: "^8.3.11"
    public: true
```

`main/CMakeLists.txt` links the managed component as:

```cmake
REQUIRES
    viewesmart__bsp_knob_15_md50et
    lvgl
    esp_lvgl_adapter
```

---

## Application entry

See `main/main.c`:

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

Rules:

1. Call `bsp_knob_15_md50et_init()` first.
2. All LVGL calls must be between `lock` / `unlock`.
3. If a knob/button callback touches LVGL, lock there too.

Brightness:

```c
ESP_ERROR_CHECK(bsp_knob_15_md50et_set_brightness(80));  /* 0~100 */
```

---

## Replace / edit the SquareLine UI

1. Create/open a SquareLine project at **466 x 466**.
2. Use the same LVGL major as this repo (demo is **LVGL 8.x**).
3. Export into `main/ui/`.
4. `main/CMakeLists.txt` already compiles `ui/**/*.c`.
5. Do **not** shift widgets to "fix" centering; driver width is 472 and `set_gap` is unused.
6. Rebuild and flash.

If the app no longer fits flash, confirm custom `partitions.csv` (3MB `factory`) is enabled.

---

## Choose LVGL 8 or 9

The BSP accepts LVGL 8/9, but your UI must match one major.

```yaml
lvgl/lvgl:
  version: "^8.3.11"   # current demo
  # version: "^9"      # only if UI is exported for LVGL 9
  public: true
```

After switching majors, delete `managed_components/lvgl__lvgl`, `dependencies.lock`, and `build/`, then rebuild and replace `main/ui/`.

---

## Pinout

From `bsp_knob_15_md50et_board.h`:

| Function | GPIO |
|----------|------|
| LCD CS / PCLK / D0-D3 | 12 / 10 / 13, 11, 14, 9 |
| LCD RST | 8 |
| Panel power (HIGH before LCD init) | 17 |
| Touch SCL / SDA / RST / INT | 3 / 1 / 2 / 4 |
| Encoder A / B | 6 / 5 |
| Button | 0 |

---

## BSP API summary

| API | Description |
|-----|-------------|
| `bsp_knob_15_md50et_init()` | Init power, LCD, touch, LVGL, knob, button |
| `bsp_knob_15_md50et_lock` / `unlock` | LVGL lock |
| `bsp_knob_15_md50et_set_brightness(0~100)` | Panel brightness (QSPI-safe) |
| `bsp_knob_15_md50et_backlight_on` / `off` | GPIO17 panel power |
| `bsp_knob_15_md50et_register_knob_cb` | Knob callback |
| `bsp_knob_15_md50et_register_button_cb` | Button callback |

Full docs:

- Registry: [viewesmart/bsp_knob_15_md50et](https://components.espressif.com/components/viewesmart/bsp_knob_15_md50et)
- Source: [GitHub bsp_knob_15_md50et](https://github.com/VIEWESMART/Viewe-esp32-components/tree/main/bsp/bsp_knob_15_md50et)

---

## Troubleshooting

### Environment / build

| Symptom | What to try |
|---------|-------------|
| Cannot open EIM / Installation Manager | Update the **Espressif IDF** extension and reload VS Code; or install standalone [EIM](https://docs.espressif.com/projects/idf-im-ui/en/latest/) first |
| EIM download slow / failed | Switch network/proxy; prefer Espressif mirrors; allowlist Espressif install folders in antivirus |
| Extension cannot find installed IDF | Run **ESP-IDF: Select Current ESP-IDF Version**; check `eim_idf.json` or `idf.eimIdfJsonPath` |
| `idf.py` / extension not ready | Install IDF via EIM, then **ESP-IDF: Select Current ESP-IDF Version** and **ESP-IDF: Doctor Command**; use the extension IDF terminal |
| Stale config after target change | Delete `build/` and rebuild |
| Component not found / solve failed | Check registry access; confirm BSP version `^1.0.2` exists |
| button / adapter version conflict | Use BSP **>= 1.0.2**; delete `dependencies.lock` + `managed_components/` |
| App partition too small | Enable custom `partitions.csv` (3M factory) |
| First build very slow | Normal for LVGL + image assets |

### Flash / serial

| Symptom | What to try |
|---------|-------------|
| No COM port | Data cable, USB driver, another port |
| Failed to connect | Hold Boot while flashing; close other serial apps |
| Monitor garbage | Match monitor baud rate (often 115200) |

### Display / touch / input

| Symptom | What to try |
|---------|-------------|
| Black screen | Keep board CO5300 init table; GPIO17 is driven high before LCD init inside BSP |
| Left blank / right green line | Keep **472x466**, no `set_gap` |
| Brightness unchanged | Use `bsp_knob_15_md50et_set_brightness()`, do not raw-write `0x51` on QSPI |
| Touch dead | Check CST820 init logs / I2C |
| Knob/button dead | Ensure callbacks registered; lock before LVGL in callbacks |

### Clean rebuild

Delete:

```text
build/
managed_components/
dependencies.lock
```

Then:

```bash
idf.py set-target esp32s3
idf.py build
```

---

## License and links

- Example app code: see SPDX headers in source files (e.g. `main/main.c` is CC0-1.0)
- BSP / touch components: Apache-2.0 (see component repos)
- Other third-party components: their own licenses

Links:

- BSP: [viewesmart/bsp_knob_15_md50et](https://components.espressif.com/components/viewesmart/bsp_knob_15_md50et)
- Touch: [viewesmart/esp_lcd_touch_cst820](https://components.espressif.com/components/viewesmart/esp_lcd_touch_cst820)
- Component monorepo: [Viewe-esp32-components](https://github.com/VIEWESMART/Viewe-esp32-components)
- ESP-IDF docs: [https://docs.espressif.com/projects/esp-idf/](https://docs.espressif.com/projects/esp-idf/)
- VS Code install guide (EIM): [Install ESP-IDF and Tools](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/installation.html)
- EIM docs: [ESP-IDF Installation Manager](https://docs.espressif.com/projects/idf-im-ui/en/latest/)
- VS Code extension overview: [Espressif IDF Extension](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/)

Issues and PRs are welcome. If you are new to ESP-IDF, finish **setup -> build -> flash** once before changing the UI.

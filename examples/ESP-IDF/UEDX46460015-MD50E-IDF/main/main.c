/*
 * SPDX-FileCopyrightText: 2023-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * UEDX46460015-MD50E: CO5300 QSPI + CST820 + esp_lvgl_adapter
 * Board bring-up uses registry component viewesmart/bsp_knob_15_md50et.
 */

#include "esp_log.h"
#include "esp_err.h"
#include "bsp_knob_15_md50et.h"
#include "ui.h"

static const char *TAG = "example";

void app_main(void)
{
    bsp_knob_15_md50et_handles_t handles = {0};
    ESP_ERROR_CHECK(bsp_knob_15_md50et_init(&handles));
    ESP_LOGI(TAG, "disp=%p touch=%p panel=%p", handles.disp, handles.touch, handles.panel);

    bsp_knob_15_md50et_register_knob_cb(LVGL_knob_event);
    bsp_knob_15_md50et_register_button_cb(LVGL_button_event);

    ESP_LOGI(TAG, "Display UI");
    if (bsp_knob_15_md50et_lock(-1) == ESP_OK) {
        ui_init();
        bsp_knob_15_md50et_unlock();
    }
}

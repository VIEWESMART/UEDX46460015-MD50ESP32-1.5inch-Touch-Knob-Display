// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: HF-ESP-10-7-OLED

#ifndef _HF_ESP_10_7_OLED_UI_H
#define _HF_ESP_10_7_OLED_UI_H

#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"
#include "ui.h"

#include "ui_helpers.h"
#include "ui_events.h"



// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
void ui_event_background(lv_event_t * e);
extern lv_obj_t * ui_background;
extern lv_obj_t * ui_Image12;
void ui_event_Button4(lv_event_t * e);
extern lv_obj_t * ui_Button4;
void ui_event_Button6(lv_event_t * e);
extern lv_obj_t * ui_Button6;
// SCREEN: ui_working
void ui_working_screen_init(void);
extern lv_obj_t * ui_working;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Bar2;
void ui_event_Button3(lv_event_t * e);
extern lv_obj_t * ui_Button3;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_Spinner3;
// SCREEN: ui_time
void ui_time_screen_init(void);
extern lv_obj_t * ui_time;
extern lv_obj_t * ui_Roller1;
extern lv_obj_t * ui_Image1;
void ui_event_Button1(lv_event_t * e);
extern lv_obj_t * ui_Button1;
extern lv_obj_t * ui_Image6;
void ui_event_Button7(lv_event_t * e);
extern lv_obj_t * ui_Button7;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_1kaorou_png);    // assets/1kaorou.png
LV_IMG_DECLARE(ui_img_2kaoji_png);    // assets/2kaoji.png
LV_IMG_DECLARE(ui_img_3danta_png);    // assets/3danta.png
LV_IMG_DECLARE(ui_img_4pisa_png);    // assets/4pisa.png
LV_IMG_DECLARE(ui_img_5liupai_png);    // assets/5liupai.png
LV_IMG_DECLARE(ui_img_6shutiao_png);    // assets/6shutiao.png
LV_IMG_DECLARE(ui_img_back111_png);    // assets/back111.png
LV_IMG_DECLARE(ui_img_1611000061);    // assets/时间.png
LV_IMG_DECLARE(ui_img_1594878714);    // assets/开始 (1).png
LV_IMG_DECLARE(ui_img_756072277);    // assets/跳绳时间.png
LV_IMG_DECLARE(ui_img_1609717271);    // assets/返回.png
LV_IMG_DECLARE(ui_img_1307502690);    // assets/分钟.png
LV_IMG_DECLARE(ui_img_2062528660);    // assets/申请成功勾勾_icon.png






void ui_init(void);

void   LVGL_knob_event(void *event);
void   LVGL_button_event(void *event);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

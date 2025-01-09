/**
 * # LVGL Porting Example
 *
 * The example demonstrates how to port LVGL(v8). And for RGB LCD, it can enable the avoid tearing function.
 *
 * ## How to Use
 *
 * To use this example, please firstly install the following dependent libraries:
 *
 * - lvgl (>= v8.3.9, < v9)
 * - ESP32_Display_Panel (> 0.2.1)
 * - ESP32_IO_Expander (>= 0.1.0 && < 0.2.0)
 * - ESP32_Knob (>= 0.1.3)
 * - ESP32_Button (>= 3.1.2)
 *
 * Then follow the steps below to configure:
 *
 * Follow the steps below to configure:
 *
 * 1. For **ESP32_Display_Panel**:
 *
 *     `Note`:Since the latest version is still being updated and has not been released, please temporarily use the test version in this repository: `Libraries`->[`ESP32_Display_Panel`](https://github.com/VIEWESMART/UEDX46460015-MD50ESP32-1.5inch-Touch-Knob-Display/tree/main/Libraries/ESP32_Display_Panel-bugfix-missing_lcd_load_vendor_config).
 *
 *     - Follow the [steps](https://github.com/VIEWESMART/VIEWE-FAQ/tree/main/Arduino-FAQ/English/How_To_Use.md#configuring-drivers) to configure drivers if needed.
 *     - If using a supported development board, follow the [steps](https://github.com/VIEWESMART/VIEWE-FAQ/tree/main/Arduino-FAQ/English/How_To_Use.md#using-supported-development-boards) to configure it.
 *     - If using a custom board, follow the [steps](https://github.com/VIEWESMART/VIEWE-FAQ/tree/main/Arduino-FAQ/English/How_To_Use.md#using-custom-development-boards) to configure it.
 *
 * 2. For **lvgl**:
 *
 *     - Follow the [steps](https://github.com/VIEWESMART/VIEWE-FAQ/blob/main/Arduino-FAQ/English/FAQ.md#how-to-add-an-lvgl-library-and-how-to-configure) to add *lv_conf.h* file and change the configurations.
 *     - Modify the macros in the [lvgl_port_v8.h](./lvgl_port_v8.h) file to configure the LVGL porting parameters.
 *
 * 3. Navigate to the `Tools` menu in the Arduino IDE to choose a ESP board and configure its parameters. For supported
 *    boards, please refter to [Configuring Supported Development Boards](https://github.com/esp-arduino-libs/ESP32_Display_Panel/blob/master/docs/How_To_Use.md#configuring-supported-development-boards)
 * 4. Verify and upload the example to your ESP board.
 *
 * ## Serial Output
 *
 * ```bash
 * ...
 * LVGL porting example start
 * Initialize panel device
 * Initialize LVGL
 * Create UI
 * LVGL porting example end
 * IDLE loop
 * IDLE loop
 * ...
 * ```
 *
 * ## Troubleshooting
 *
 * Please check the [FAQ](https://github.com/VIEWESMART/VIEWE-FAQ/tree/main/Arduino-FAQ/English/FAQ.md) first to see if the same question exists. If not, please create a [Github issue](https://github.com/VIEWESMART/VIEWE-FAQ/issues). We will get back to you as soon as possible.
 *
 */

#include <Arduino.h>
#include <ESP_Panel_Library.h>
#include <lvgl.h>
#include "lvgl_port_v8.h"

/**
/* To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 * You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 */
#include <demos/lv_demos.h>
// #include <examples/lv_examples.h>

/*Initialize UI start*/
/*Initialize UI end*/
#ifdef KNOB
#include <ESP_Knob.h>
#include <Button.h>
#include <ui.h>

ESP_Knob *knob;
void onKnobLeftEventCallback(int count, void *usr_data)
{
    Serial.printf("Detect left event, count is %d\n", count);
    // lvgl_port_lock(-1);
    // LVGL_knob_event((void*)KNOB_LEFT);
    // lvgl_port_unlock();
}

void onKnobRightEventCallback(int count, void *usr_data)
{
    Serial.printf("Detect right event, count is %d\n", count);
    // lvgl_port_lock(-1);
    // LVGL_knob_event((void*)KNOB_RIGHT);
    // lvgl_port_unlock();
}

static void SingleClickCb(void *button_handle, void *usr_data) {
    Serial.println("Button Single Click");
    // lvgl_port_lock(-1);
    // LVGL_button_event((void*)BUTTON_SINGLE_CLICK);
    // lvgl_port_unlock();
}
static void DoubleClickCb(void *button_handle, void *usr_data)
{
    Serial.println("Button Double Click");
}
static void LongPressStartCb(void *button_handle, void *usr_data) {
    Serial.println("Button Long Press Start");
    // lvgl_port_lock(-1);
    // LVGL_button_event((void*)BUTTON_LONG_PRESS_START);
    // lvgl_port_unlock();
}
#endif

void setup()
{
#ifdef KNOB15
    pinMode(17, OUTPUT);
    digitalWrite(17, HIGH);
#endif
    String title = "LVGL porting example";
#ifdef IM
    pinMode(IM1, OUTPUT);
    digitalWrite(IM1, HIGH);
  #ifdef BOARD_VIEWE_ESP_S3_Touch_LCD_35_V2
    pinMode(IM0, OUTPUT);
    digitalWrite(IM0, HIGH);
  #endif
  #ifndef BOARD_VIEWE_ESP_S3_Touch_LCD_35_V2
    pinMode(IM0, OUTPUT);
    digitalWrite(IM0, LOW);
  #endif
#endif

    Serial.begin(115200);
    Serial.println(title + " start");

    Serial.println("Initialize panel device");
    ESP_Panel *panel = new ESP_Panel();
    panel->init();
#if LVGL_PORT_AVOID_TEAR
    // When avoid tearing function is enabled, configure the bus according to the LVGL configuration
    ESP_PanelBus *lcd_bus = panel->getLcd()->getBus();
#if ESP_PANEL_LCD_BUS_TYPE == ESP_PANEL_BUS_TYPE_RGB
    static_cast<ESP_PanelBus_RGB *>(lcd_bus)->configRgbBounceBufferSize(LVGL_PORT_RGB_BOUNCE_BUFFER_SIZE);
    static_cast<ESP_PanelBus_RGB *>(lcd_bus)->configRgbFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
#elif ESP_PANEL_LCD_BUS_TYPE == ESP_PANEL_BUS_TYPE_MIPI_DSI
    static_cast<ESP_PanelBus_DSI *>(lcd_bus)->configDpiFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
#endif
#endif
    panel->begin();

#ifdef KNOB
    Serial.println("Initialize Knob device");
    knob = new ESP_Knob(GPIO_NUM_KNOB_PIN_A, GPIO_NUM_KNOB_PIN_B);
    knob->begin();
    knob->attachLeftEventCallback(onKnobLeftEventCallback);
    knob->attachRightEventCallback(onKnobRightEventCallback);

    Serial.println("Initialize Button device");
    Button *btn = new Button(GPIO_BUTTON_PIN, false);

    btn->attachSingleClickEventCb(&SingleClickCb, NULL);
    btn->attachDoubleClickEventCb(&DoubleClickCb, NULL);
    btn->attachLongPressStartEventCb(&LongPressStartCb, NULL);
#endif

    Serial.println("Initialize LVGL");
    lvgl_port_init(panel->getLcd(), panel->getTouch());

    Serial.println("Create UI");
    /* Lock the mutex due to the LVGL APIs are not thread-safe */
    lvgl_port_lock(-1);

    /**
     * Create a simple label
     *
     */
    // lv_obj_t *label = lv_label_create(lv_scr_act());
    // lv_label_set_text(label, title.c_str());
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  
    /**
     * Try an example. Don't forget to uncomment header.
     * See all the examples online: https://docs.lvgl.io/master/examples.html
     * source codes: https://github.com/lvgl/lvgl/tree/e7f88efa5853128bf871dde335c0ca8da9eb7731/examples
     */
    //  lv_example_btn_1();

    /**
     * Or try out a demo.
     * Don't forget to uncomment header and enable the demos in `lv_conf.h`. E.g. `LV_USE_DEMO_WIDGETS`
     */
    // lv_demo_widgets();
    // lv_demo_benchmark();
    lv_demo_music();
    // lv_demo_stress();
    // ui_init();

    /* Release the mutex */
    lvgl_port_unlock();

    Serial.println(title + " end");
}

void loop()
{
    Serial.println("IDLE loop");
    delay(50);
}

SET(SOURCES screens/ui_Screen1.c
    screens/ui_working.c
    screens/ui_time.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_back480_png.c
    images/ui_img_1kaorou_png.c
    images/ui_img_2kaoji_png.c
    images/ui_img_3danta_png.c
    images/ui_img_4pisa_png.c
    images/ui_img_5liupai_png.c
    images/ui_img_6shutiao_png.c
    images/ui_img_back111_png.c
    images/ui_img_1611000061.c
    images/ui_img_1594878714.c
    images/ui_img_756072277.c
    images/ui_img_1609717271.c
    images/ui_img_1307502690.c
    images/ui_img_2062528660.c)

add_library(ui ${SOURCES})

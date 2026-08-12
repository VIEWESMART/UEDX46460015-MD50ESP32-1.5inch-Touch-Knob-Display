file(GLOB_RECURSE UI_SRCS
    "ui/*.c"
    "ui/screens/*.c"
    "ui/images/*.c"
    "ui/components/*.c"
)

idf_component_register(
    SRCS
        "main.c"
        ${UI_SRCS}
    INCLUDE_DIRS
        "."
        "ui"
    REQUIRES
        viewesmart__bsp_knob_15_md50et
        lvgl
        esp_lvgl_adapter
)

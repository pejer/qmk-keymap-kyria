#include "pejer.h"

uint8_t is_master;

#ifdef OLED_DRIVER_ENABLE
#    define KEYLOGGER_LENGTH 10
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
// clang-format off
#endif

#ifndef UNICODE_ENABLE
#    define UC(x) KC_NO
#endif

/*
 * The `LAYOUT_kyria_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_kyria_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
      KC_ESC,  K01,     K02,     K03,     K04,     K05,                                             K06,     K07,     K08,     K09,     K0A,     KC_LBRC, \
      KC_BSLS, K11, K12,     K13,     K14,     K15,                                             K16,     K17,     K18,     K19,     K1A, KC_QUOT, \
      KC_GRV, CTL_T(K21), K22,  K23,     K24,     K25,     KC_NO,   ADJUST,       ADJUST,   KC_NO,   K26,     K27,     K28,     K29, RCTL_T(K2A), KC_AMPR, \
                                 LALT(LGUI(KC_A)), OS_LALT, KC_LOWER,  KC_PEJ_SPC,  KC_PEJ_BSPC,     KC_PEJ_TAB, KC_ENT,  KC_RAISE, MO(_RAISE), KC_MUTE \
    )
/* Re-pass though to allow templates to be used */
#define LAYOUT_kyria_base_wrapper(...)       LAYOUT_kyria_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_kyria_base_wrapper(
        ___________PEJER_QWERTY_L1_________________, ___________PEJER_QWERTY_R1_________________,
        ___________PEJER_QWERTY_L2_________________, ___________PEJER_QWERTY_R2_________________,
        ___________PEJER_QWERTY_L3_________________, ___________PEJER_QWERTY_R3_________________
    ),
    [_SYMBOL0] = LAYOUT_wrapper(
        KC_ESC,___________PEJER_SYMBOL0_L1________________, ___________PEJER_SYMBOL0_R1________________,KC_PEJ_QUE,
        KC_BSLS,___________PEJER_SYMBOL0_L2________________, ___________PEJER_SYMBOL0_R2________________,KC_QUOT,
        KC_LSFT,___________PEJER_SYMBOL0_L3________________,KC_NO,ADJUST,ADJUST,KC_NO, ___________PEJER_SYMBOL0_R3________________, KC_AMPR,
                                 KC_MUTE, OS_LALT, KC_LOWER,  KC_SPC,  KC_PEJ_BSPC,     KC_PEJ_TAB, KC_ENT,  KC_RAISE, ADJUST, MO(_RAISE) \
    ),
    [_SYMBOL1] = LAYOUT_wrapper(
        KC_ESC,___________PEJER_SYMBOL1_L1________________, ___________PEJER_SYMBOL1_R1________________,KC_MINS,
        KC_BSLS,___________PEJER_SYMBOL1_L2________________, ___________PEJER_SYMBOL1_R2________________,KC_PRINT_TRUTH,
        KC_GRV,___________PEJER_SYMBOL1_L3________________, KC_NO,ADJUST,ADJUST,KC_NO,___________PEJER_SYMBOL1_R3________________,KC_XXXXX,

                                 KC_MUTE, OS_LALT, KC_LOWER,  KC_SPC,  KC_PEJ_BSPC,     KC_PEJ_TAB, KC_ENT,  KC_RAISE,  MO(_RAISE), MO(_RAISE)  \
    ),
    [_NUMBERS] = LAYOUT_wrapper(
        KC_ESC,___________PEJER_NUMBER_L1_________________, ___________PEJER_NUMBER_R1_________________,KC_MINS,
        KC_CTLTB,___________PEJER_NUMBER_L2_________________, ___________PEJER_NUMBER_R2_________________,KC_XXXXX,
        KC_LSFT,___________PEJER_NUMBER_L3_________________,KC_NO,ADJUST,ADJUST,KC_NO, ___________PEJER_NUMBER_R3_________________,KC_XXXXX,

                                 KC_MUTE, OS_LALT, KC_LOWER,  KC_SPC,  KC_PEJ_BSPC,     KC_PEJ_TAB, KC_ENT,  KC_RAISE, KC_0, MO(_RAISE) \
    ),
    [_RAISE] = LAYOUT_wrapper(
        KC_MAKE, ___________PEJER_ADJUST_L1_________________,                                       ___________PEJER_ADJUST_R1_________________, RESET,
        VRSN,    ___________PEJER_ADJUST_L2_________________,                                       ___________PEJER_ADJUST_R2_________________, EEP_RST,
        _______, ___________PEJER_ADJUST_L3_________________, HPT_TOG, HPT_FBK,   MG_NKRO, UC_MOD,  ___________PEJER_ADJUST_R3_________________, TG_MODS,
                                   _______, _______, _______, KC_NUKE, _______,   _______, _______, _______, MO(_RAISE), MO(_RAISE)
    )
};
report_mouse_t mouse_report;
layer_state_t layer_state_set_keymap(layer_state_t state) {
  switch (get_highest_layer(state)) {
      case _RAISE:
          trackball_setrgb(0,48,0);
          break;
      case _SYMBOL0:
          trackball_setrgb(0,48,96);
          break;
      case _SYMBOL1:
          trackball_setrgb(96,48,0);
          break;
      case _NUMBERS:
            trackball_setrgb(96,24,96);
          break;
      default: //  for any other layers, or the default layer
          trackball_setrgb(0,0,0);
          break;
    }
  return state;
}
uint8_t pej_scroll_speed = 8;

// clang-format on
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifndef SPLIT_KEYBOARD
        if (keycode == RESET && !is_master) {
            return false;
        }
#endif
    }
    switch(keycode){
      case KC_BTN1:
        mouse_report = pointing_device_get_report();
         if (record->event.pressed)
         {
             mouse_report.buttons |= MOUSE_BTN1; //this is defined in report.h
         }
         else
         {
              mouse_report.buttons &= ~MOUSE_BTN1;
         }
         pointing_device_set_report(mouse_report);
         pointing_device_send();
       break;
      case KC_BTN2:
        mouse_report = pointing_device_get_report();
         if (record->event.pressed)
         {
             mouse_report.buttons |= MOUSE_BTN2; //this is defined in report.h
         }
         else
         {
              mouse_report.buttons &= ~MOUSE_BTN2;
         }
         pointing_device_set_report(mouse_report);
         pointing_device_send();
      break;
      case KC_WH_U: // simulate mouse wheel up
        mouse_report = pointing_device_get_report();
         if (record->event.pressed)
         {
             mouse_report.v = pej_scroll_speed; //this is defined in report.h
         }
         else
         {
              mouse_report.v = 0;
         }
         pointing_device_set_report(mouse_report);
         pointing_device_send();
       break;
      case KC_WH_D: // simulate mouse wheel up
        mouse_report = pointing_device_get_report();
         if (record->event.pressed)
         {
             mouse_report.v = -pej_scroll_speed; //this is defined in report.h
         }
         else
         {
              mouse_report.v = 0;
         }
         pointing_device_set_report(mouse_report);
         pointing_device_send();
       break;
    }
    return true;
}
void matrix_init_keymap(void) { is_master = (uint8_t)is_keyboard_master(); }

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }


void render_keylogger_status(void) {
    oled_write_P(PSTR("Keylogger: "), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Layout: "), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwerty "), false);
            break;
        case _DVORAK:
            oled_write_ln_P(PSTR("Dvorak"), false);
            break;
        case _WORKMAN:
            oled_write_ln_P(PSTR("Workman"), false);
            break;
        case _NORMAN:
            oled_write_ln_P(PSTR("Norman"), false);
            break;
        case _MALTRON:
            oled_write_ln_P(PSTR("Maltron"), false);
            break;
        case _EUCALYN:
            oled_write_ln_P(PSTR("Eucalyn"), false);
            break;
        case _CARPLAX:
            oled_write_ln_P(PSTR("Carplax"), false);
            break;
        case 11:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case 9:
            oled_write_ln_P(PSTR("Symbol0"), false);
            break;
        case 10:
            oled_write_ln_P(PSTR("Symbol1"), false);
            break;
        default:
            oled_write_ln_P(PSTR("No clue"), false);
            break;
    }
}
void render_layer_state(void) {
    oled_write_ln_P(PSTR("     ACTIVE LAYER"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("NUM"), layer_state_is(_NUMBERS));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("SYMB0"), layer_state_is(_SYMBOL0));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("SYMB1"), layer_state_is(_SYMBOL1));
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR("ADJ"), layer_state_is(_RAISE));

}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock: "), false);
    oled_write_P(PSTR("NUM"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("CAPS"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR("SCL"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods: "), false);
    oled_write_P(PSTR("Sft"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Ctl"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Alt"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("Boot  "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("NKRO"), keymap_config.nkro);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR("GUI"), !keymap_config.no_gui);
    oled_write_P(PSTR("Magic "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("GRV"), keymap_config.swap_grave_esc);
    oled_write_P(PSTR("  "), false);
    oled_write_ln_P(PSTR("CAPS"), keymap_config.swap_control_capslock);
}

void render_user_status(void) {
    oled_write_P(PSTR("USER: "), false);
    oled_write_P(PSTR("Anim"), userspace_config.rgb_matrix_idle_anim);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Layr"), userspace_config.rgb_layer_change);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR("Nuke"), userspace_config.nuke_switch);
}

// clang-format off
void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, false);
}

#    ifndef SPLIT_TRANSPORT_MIRROR
void render_pejer_logo(void) {
  static const char PROGMEM kyria_logo[] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,192,192,192,192,192,192,192,192,192,192,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,192,192,192,240,240,240,240,252,252,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252,252,252,252,240,240,192,192,192,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,252,252,255,255,255,255,255,255,255,255,255,255,255,255,63,63,63,63,15,15,15,15,3,3,3,3,15,15,15,15,63,63,63,63,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,3,3,0,0,0,0,252,252,252,252,255,255,255,255,255,255,255,255,252,252,240,240,0,0,0,0,3,3,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,192,192,192,192,3,3,3,3,3,3,3,3,192,192,240,240,240,240,252,252,252,252,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,15,15,63,63,63,63,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,63,63,15,15,15,15,3,3,0,0,0,0,0,0,0,0,252,252,204,204,204,252,120,0,0,252,252,204,204,204,204,204,0,0,140,12,12,12,12,252,252,0,0,252,252,204,204,204,204,204,0,0,252,252,204,204,204,252,184,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,15,15,15,15,15,15,15,15,15,15,15,15,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,0,0,0,0,0,0,0,15,15,12,12,12,12,12,0,0,3,7,12,12,14,7,3,0,0,15,15,12,12,12,12,12,0,0,15,15,0,0,0,15,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0

};
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}
#    endif
// clang-format on

void render_status_main(void) {
    /* Show Keyboard Layout  */
    //render_pejer_logo();
    render_layer_state();
    render_default_layer_state();
    //render_keylock_status(host_keyboard_leds());
    //render_bootmagic_status();
    //render_user_status();
 }

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_logo();
}

void oled_task_user(void) {
//#    ifndef SPLIT_KEYBOARD
//    else {
//        oled_on();
//    }
//#    endif
//    if (is_master) {
//        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
//    } else {
#    ifdef SPLIT_TRANSPORT_MIRROR
        //render_status_secondary();
//        render_pejer_logo();
#    else
//        render_pejer_logo();
#    endif
//    }
  render_pejer_logo();
}

#endif

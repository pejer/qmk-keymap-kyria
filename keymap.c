#include "pejer.h"

uint8_t is_master;

#ifndef UNICODE_ENABLE
#    define UC(x) KC_NO
#endif

/*
 * Shamefully stolen from Drashna.
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
                                 LALT(LGUI(KC_A)), KC_NUBS, KC_PEJ_ESCAPE,  KC_PEJ_SPC,  KC_PEJ_BSPC,     KC_PEJ_TAB, KC_ENT,   KC_PEJ_AMPR, KC_PPLS, KC_MUTE \
    )

#define LAYOUT_kyria_homerow_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_homerow_wrapper( \
      KC_ESC,  K01,     K02,     K03,     K04,     K05,                                             K06,     K07,     K08,     K09,     K0A,     KC_LBRC, \
      KC_BSLS, LSFT_T(K11), LGUI_T(K12),LALT_T(K13),LCTL_T(K14),K15,                                K16,LCTL_T(K17),LALT_T(K18),LGUI_T(K19),LSFT_T(K1A), KC_QUOT, \
      KC_GRV, CTL_T(K21), K22,  K23,     K24,     K25,     KC_NO,   ADJUST,       ADJUST,   KC_NO,   K26,     K27,     K28,     K29, RCTL_T(K2A), KC_AMPR, \
                                   LALT(LGUI(KC_A)), KC_NUBS, KC_PEJ_ESCAPE,  KC_PEJ_SPC,  KC_PEJ_BSPC,     KC_PEJ_TAB, KC_ENT,  KC_PEJ_AMPR, KC_PPLS, KC_MUTE \
    )


/* 
 * Shamefully stolen from Drashna.
 * Re-pass though to allow templates to be used */
#define LAYOUT_kyria_base_wrapper(...)       LAYOUT_kyria_base(__VA_ARGS__)
#define LAYOUT_kyria_home_wrapper(...)       LAYOUT_kyria_homerow_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_kyria_home_wrapper(
                 ___________PEJER_QWERTY_L1_________________,                                               ___________PEJER_QWERTY_R1_________________,
                 ___________PEJER_QWERTY_L2_________________,                                               ___________PEJER_QWERTY_R2_________________,
                 ___________PEJER_QWERTY_L3_________________,                                               ___________PEJER_QWERTY_R3_________________
    ),
    [_SYMBOL0] = LAYOUT_wrapper(
        KC_ESC,  ___________PEJER_SYMBOL0_L1________________,                                               ___________PEJER_SYMBOL0_R1________________,KC_PEJ_QUE,
        KC_BSLS, ___________PEJER_SYMBOL0_L2________________,                                               ___________PEJER_SYMBOL0_R2________________,KC_QUOT,
        KC_LSFT, ___________PEJER_SYMBOL0_L3________________,KC_NO, ADJUST,               ADJUST,KC_NO,     ___________PEJER_SYMBOL0_R3________________, KC_AMPR,
                                 KC_MUTE, OS_LALT, KC_LOWER,  KC_SPC,  KC_PEJ_BSPC,     KC_PEJ_TAB, KC_ENT,  KC_RAISE, ADJUST, MO(_RAISE) \
    ),
    [_SYMBOL1] = LAYOUT_wrapper(
        KC_ESC,  ___________PEJER_SYMBOL1_L1________________,                                               ___________PEJER_SYMBOL1_R1________________,KC_MINS,
        KC_BSLS, ___________PEJER_SYMBOL1_L2________________,                                               ___________PEJER_SYMBOL1_R2________________,KC_QUOT,
        KC_GRV,  ___________PEJER_SYMBOL1_L3________________, KC_NO,ADJUST,             ADJUST,KC_NO,       ___________PEJER_SYMBOL1_R3________________,KC_XXXXX,
                                 KC_MUTE, OS_LALT, KC_LOWER,  KC_SPC,  KC_PEJ_BSPC,     KC_PEJ_TAB, KC_ENT,  KC_RAISE,  MO(_RAISE), MO(_RAISE)  \
    ),
    [_SYMBOL2] = LAYOUT_wrapper(
        KC_ESC,  ___________PEJER_SYMBOL2_L1________________,                                               ___________PEJER_SYMBOL2_R1________________,KC_MINS,
        KC_BSLS, ___________PEJER_SYMBOL2_L2________________,                                               ___________PEJER_SYMBOL2_R2________________,KC_QUOT,
        KC_GRV,  ___________PEJER_SYMBOL2_L3________________, KC_NO,ADJUST,             ADJUST,KC_NO,       ___________PEJER_SYMBOL2_R3________________,KC_XXXXX,
                                 KC_MUTE, OS_LALT, KC_LOWER,  KC_SPC,  KC_PEJ_BSPC,     KC_PEJ_TAB, KC_ENT,  KC_RAISE,  MO(_RAISE), MO(_RAISE)  \
    ),
    [_NUMBERS] = LAYOUT_wrapper(
        KC_ESC,  ___________PEJER_NUMBER_L1_________________,                                               ___________PEJER_NUMBER_R1_________________,KC_MINS,
        KC_CTLTB,___________PEJER_NUMBER_L2_________________,                                               ___________PEJER_NUMBER_R2_________________,KC_XXXXX,
        KC_LSFT, ___________PEJER_NUMBER_L3_________________,KC_NO,ADJUST,              ADJUST,KC_NO,       ___________PEJER_NUMBER_R3_________________,KC_XXXXX,

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
#ifdef PRIMARY_SPLIT
#ifdef TRACKBALL_ENABLE 
  switch (get_highest_layer(state)) {
      case _RAISE:
          trackball_setrgb(0,64,0);
          break;
      case _SYMBOL0:
          trackball_setrgb(0,64,128);
          break;
      case _SYMBOL1:
          trackball_setrgb(128,64,0);
          break;
      case _NUMBERS:
            trackball_setrgb(128,32,128);
          break;
      default: //  for any other layers, or the default layer
        if (user_config.trackball_led_on && rgblight_is_enabled()) {
          trackball_setrgb(64,64,64);
        } else {
          trackball_setrgb(0,0,0);
        }
      break;
    }
#endif
#endif
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
#ifdef PRIMARY_SPLIT
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
      case KC_ACL0: //acceleration!
        if (record->event.pressed) {
          user_config.trackball_speed_fast = true;
        }
        else
        {
          user_config.trackball_speed_fast = false;
        }
       break;
      case KC_SCROLL:
        if (record->event.pressed) {
          user_config.trackball_scroll = true;
        }
        else
        {
          user_config.trackball_scroll = false;
        }
       break;
#endif
    }
  return true;
}
void matrix_init_keymap(void) { is_master = (uint8_t)is_keyboard_master(); }

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

// clang-format off
void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, false);
}

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
// clang-format on

void oled_task_user(void) {
  render_pejer_logo();
}

#endif

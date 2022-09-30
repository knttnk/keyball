/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in //the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "keymap_extras/keymap_japanese.h"
#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4          , KC_5     ,                            KC_6          , KC_7     , KC_8     , KC_9     , KC_0          , JP_MINS  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R          , KC_T     ,                            KC_Y          , KC_U     , KC_I     , KC_O     , KC_P          , KC_BSPC  ,
    KC_LSFT  , KC_A     , KC_S     , KC_D     , KC_F          , KC_G     ,                            KC_H          , KC_J     , KC_K     , KC_L     , KK_SCRL_SCLN  , KC_ENTER ,
    KC_LCTL  , KC_Z     , KC_X     , KC_C     , KC_V          , KC_B     , KC_BTN3  ,      KC_SPACE , KC_N          , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH       , KC_RSFT  ,
    XXXXXXX  , XXXXXXX  , KC_LWIN  , KC_LALT  , LT(1,JP_MHEN) , KC_BTN1  , KC_BTN2  ,      MO(2)    , LT(3,JP_HENK) , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_RCTRL      , KC_RCTRL
  ),

  [1] = LAYOUT_universal(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX , XXXXXXX  ,                                  XXXXXXX  , XXXXXXX  , JP_MINS  , JP_CIRC  , JP_YEN   , XXXXXXX  ,
    _______  , XXXXXXX  , XXXXXXX  , KC_UP    , XXXXXXX , XXXXXXX  ,                                  XXXXXXX  , XXXXXXX  , XXXXXXX  , JP_AT    , JP_LBRC  , KC_DEL   ,
    _______  , XXXXXXX  , KC_LEFT  , KC_DOWN  , KC_RGHT , XXXXXXX  ,                                  XXXXXXX  , XXXXXXX  , JP_SCLN  , JP_COLN  , JP_RBRC  , _______  ,
    _______  , XXXXXXX  , XXXXXXX  , KC_DOWN  , XXXXXXX , XXXXXXX  , _______  ,            XXXXXXX  , XXXXXXX  , JP_COMM  , JP_DOT   , JP_SLSH  , JP_BSLS  , _______  ,
    XXXXXXX  , XXXXXXX  , _______  , _______  , _______ , XXXXXXX  , XXXXXXX  ,            _______  , _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    XXXXXXX  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                 KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , XXXXXXX  ,
    _______  , KC_F11   , KC_F12   , KC_PGUP  , XXXXXXX  , XXXXXXX  ,                                 XXXXXXX  , XXXXXXX  , KC_VOLU  , XXXXXXX  , XXXXXXX  , _______  ,
    _______  , XXXXXXX  , KC_HOME  , KC_PGDN  , KC_END   , XXXXXXX  ,                                 XXXXXXX  , KC_BRIU  , KC_VOLD  , XXXXXXX  , XXXXXXX  , _______  ,
    _______  , XXXXXXX  , XXXXXXX  , KC_INS   , XXXXXXX  , XXXXXXX  , _______  ,           XXXXXXX  , XXXXXXX  , KC_BRID  , KC_MUTE  , XXXXXXX  , XXXXXXX  , _______  ,
    XXXXXXX  , XXXXXXX  , _______  , _______  , _______  , KC_BTN4  , KC_BTN5  ,           _______  , _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                 XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                 XXXXXXX  , KC_MRWD  , KC_MSTP  , KC_MFFD  , XXXXXXX  , _______  ,
    _______  , XXXXXXX  , KC_SCRL  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                 XXXXXXX  , KC_MPRV  , KC_MPLY  , KC_MNXT  , XXXXXXX  , _______  ,
    _______  , XXXXXXX  , XXXXXXX  ,S(KC_CAPS), XXXXXXX  , XXXXXXX  , _______  ,           XXXXXXX  , KC_NUM   , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  ,
    XXXXXXX  , XXXXXXX  , _______  , _______  , _______  , KC_BTN4  , KC_BTN5  ,           _______  , _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  // Auto enable scroll mode when the highest layer is 3
  keyball_set_scroll_mode(get_highest_layer(state) == 3);
  return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
}
#endif

// 編集
uint32_t last_KK_SCRL_SCLN_pressed;
#define SCRL_TAPPING_TERM 150
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KK_SCRL_SCLN:
      keyball_set_scroll_mode(record->event.pressed);

      if (record->event.pressed) {
        last_KK_SCRL_SCLN_pressed = timer_read32();
      } else {
        if (timer_read32() - last_KK_SCRL_SCLN_pressed < SCRL_TAPPING_TERM) {
          // 長押しされなかったとき
          tap_code(KC_SCLN);
        }
      }
      return false;
    default:
      return true;
  }
}

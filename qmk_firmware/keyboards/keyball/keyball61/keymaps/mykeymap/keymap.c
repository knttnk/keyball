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
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4          , KC_5     ,                            KC_6          , KC_7       , KC_8     , KC_9     , KC_0     , KC_BSPC  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R          , KC_T     ,                            KC_Y          , KC_U       , KC_I     , KC_O     , KC_P     , JP_MINS  ,
    KC_LSFT  , KC_A     , KC_S     , KC_D     , KC_F          , KC_G     ,                            KC_H          , KK_J_SCLN  , KC_K     , KC_L     , KC_SCLN  , KC_ENTER ,
    KC_LCTL  , KC_Z     , KC_X     , KC_C     , KC_V          , KC_B     , KC_BTN3  ,      KC_SPACE , KC_N          , KC_M       , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
    XXXXXXX  , XXXXXXX  , KC_LWIN  , KC_LALT  , LT(1,JP_MHEN) , KC_BTN1  , KC_BTN2  ,      MO(2)    , LT(3,JP_HENK) , XXXXXXX    , XXXXXXX  , XXXXXXX  , KC_RCTRL , KC_RCTRL
  ),

  [1] = LAYOUT_universal(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX , XXXXXXX  ,                                  XXXXXXX  , XXXXXXX  , JP_MINS  , JP_CIRC  , JP_YEN   , KC_DEL   ,
    _______  , XXXXXXX  , XXXXXXX  , KC_PGUP  , XXXXXXX , XXXXXXX  ,                                  XXXXXXX  , XXXXXXX  , XXXXXXX  , JP_AT    , JP_LBRC  , XXXXXXX  ,
    _______  , XXXXXXX  , KC_HOME  , KC_PGDN  , KC_END  , XXXXXXX  ,                                  XXXXXXX  , XXXXXXX  , JP_SCLN  , JP_COLN  , JP_RBRC  , _______  ,
    _______  , XXXXXXX  , XXXXXXX  , KC_INS   , XXXXXXX , XXXXXXX  , _______  ,            XXXXXXX  , XXXXXXX  , JP_COMM  , JP_DOT   , JP_SLSH  , JP_BSLS  , _______  ,
    XXXXXXX  , XXXXXXX  , _______  , _______  , _______ , XXXXXXX  , XXXXXXX  ,            _______  , _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    XXXXXXX  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                 KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_DEL   ,
    _______  , KC_F11   , KC_F12   , KC_UP    , XXXXXXX  , XXXXXXX  ,                                 XXXXXXX  , KC_BRIU  , KC_VOLU  , XXXXXXX  , XXXXXXX  , _______  ,
    _______  , XXXXXXX  , KC_LEFT  , KC_DOWN  , KC_RGHT  , XXXXXXX  ,                                 XXXXXXX  , KC_BRID  , KC_VOLD  , XXXXXXX  , XXXXXXX  , _______  ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  ,           XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_MUTE  , XXXXXXX  , XXXXXXX  , _______  ,
    XXXXXXX  , XXXXXXX  , _______  , _______  , _______  , KC_BTN4  , KC_BTN5  ,           _______  , _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                 XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_DEL   ,
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

uint16_t keypress_count = 0;
#ifdef OLED_ENABLE
// TODO: keyball.c のコピーだが，もっと軽くする方法？
static char to_1x(uint8_t x) {
  x &= 0x0f;
  return x < 10 ? x + '0' : x + 'a' - 10;
}

static const char *format_4d(int8_t d) {
  static char buf[5] = "    ";  // max width (4) + NUL (1)
  char lead = ' ';
  if (d < 0) {
    d = -d;
    lead = '-';
  }
  buf[0] = lead;
  lead = ' ';
  buf[3] = (d % 10) + '0';
  d /= 10;
  if (d == 0) {
    buf[2] = lead;
    lead = ' ';
  } else {
    buf[2] = (d % 10) + '0';
    d /= 10;
  }
  if (d == 0) {
    buf[1] = lead;
    lead = ' ';
  } else {
    buf[1] = (d % 10) + '0';
    d /= 10;
  }
  return buf;
}

// knttnkが追加
bool should_process_keypress(void) {  // slave側でも処理を行うかどうか
  return true;
}
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}
// knttnkが追加終わり

#include "lib/oledkit/oledkit.h"

void oled_write_uint16(uint16_t d) {
  char buf[6] = "    0";  // max width (4) + NUL (1)

  for (uint8_t i = 4; i >= 0; i--) {
    if (d == 0) {
      oled_write(buf, false);
      return;
    } else {
      buf[i] = (d % 10) + '0';
      d /= 10;
    }
  }
}

void oledkit_render_info_user(void) {
  // Yowkeesさん実装87
  // keyball_oled_render_keyinfo();
  // keyball_oled_render_ballinfo();

  // knttnk実装
  int8_t current_layer;
  for (current_layer = 3; current_layer >= 0; current_layer--) {
    if (layer_state_is(current_layer)) {
      break;
    }
  }

  // レイヤー情報
  oled_write_P(PSTR("LYR:"), false);
  oled_write_char(to_1x(current_layer), false);

  // キーマップ
  if (is_keyboard_master()) {
    // きーぼーどの左側
    // キーマップ表示
    switch (current_layer) {
      case 0:
        oled_write_P(PSTR("12345"
                          "qwert"
                          "asd"),
                     false);
        oled_write_P(PSTR("f"), true);
        oled_write_P(PSTR("g"
                          "zxcvb"),
                     false);
        break;
      case 1:
        oled_write_P(PSTR("     "
                          "  U  "
                          " HD"),
                     false);
        oled_write_P(PSTR("E"), true);
        oled_write_P(PSTR(" "
                          "  I  "),
                     false);
        break;
      case 2:
        oled_write_P(PSTR("FnFnF"
                          "Fn^  "
                          " <V"),
                     false);
        oled_write_P(PSTR(">"), true);
        oled_write_P(PSTR(" "
                          "     "),
                     false);
        break;
      case 3:
        oled_write_P(PSTR("     "
                          "     "
                          "ScL"),
                     false);
        oled_write_P(PSTR("c"), true);
        oled_write_P(PSTR("k"
                          "CpLck"),
                     false);
        break;
      default:
        break;
    }
    oled_write_P(PSTR("     "), false);

    // キーとボールの情報
    if (keyball.scroll_mode) {
      oled_write_P(PSTR("h"), true);
      oled_write(format_4d(keyball.last_mouse.h), true);
      oled_write_P(PSTR("v"), true);
      oled_write(format_4d(keyball.last_mouse.v), true);
    } else {
      oled_write_P(PSTR("x"), false);
      oled_write(format_4d(keyball.last_mouse.x), false);
      oled_write_P(PSTR("y"), false);
      oled_write(format_4d(keyball.last_mouse.y), false);
    }

    oled_write_P(PSTR("r"), false);
    oled_write_char(to_1x(keyball.last_pos.row), false);
    oled_write_P(PSTR(" c"), false);
    oled_write_char(to_1x(keyball.last_pos.col), false);

    // カウント
    oled_write_P(PSTR("     "
                      "Cnt: "),
                 false);
    oled_write_uint16(keypress_count);

  } else {
    // きーぼーどの右側
    switch (current_layer) {
      case 0:
        oled_write_P(PSTR("67890"
                          "yuiop"
                          "h"),
                     false);
        oled_write_P(PSTR("j"), true);
        oled_write_P(PSTR("kl;"
                          "nm,./"),
                     false);
        break;
      case 1:
        oled_write_P(PSTR("  -^\\"
                          "   @["
                          " "),
                     false);
        oled_write_P(PSTR(" "), true);
        oled_write_P(PSTR(";:]"
                          " ,./\\"),
                     false);
        break;
      case 2:
        oled_write_P(PSTR("FnFnF"
                          " "),
                     false);
        oled_write_P(PSTR("+"), true);
        oled_write_P(PSTR("+  "
                          " "),
                     false);
        oled_write_P(PSTR("-"), true);
        oled_write_P(PSTR("-  "
                          "  m  "),
                     false);
        break;
      case 3:
        oled_write_P(PSTR("     "
                          "Media"
                          "M"),
                     false);
        oled_write_P(PSTR("e"), true);
        oled_write_P(PSTR("dia"
                          "NmLck"),
                     false);
        break;
      default:
        break;
    }
    oled_write_P(PSTR("     "
                      "Key  "
                      "ball "
                      "61   "),
                 false);
  }
  oled_advance_page(true);
}

bool oled_task_user(void) {
  oledkit_render_info_user();
  return true;
}
#endif

// 編集
uint32_t last_KK_J_SCLN_pressed;
bool scrolling =
    false;  // jが押されており，他のボタンは押されていないのでスクロールが有効かどうか
#define SCRL_TAPPING_TERM 150
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    keypress_count++;
  }

  switch (keycode) {
    case KK_J_SCLN:
      keyball_set_scroll_mode(record->event.pressed);

      if (record->event.pressed) {
        last_KK_J_SCLN_pressed = timer_read32();
        scrolling = true;
      } else {
        if (scrolling) {
          // 他のボタンは押されていないので，スクロールされたかJを押すかの判断が必要
          if (timer_read32() - last_KK_J_SCLN_pressed < SCRL_TAPPING_TERM) {
            // 長押しされなかったとき
            tap_code(KC_J);
          }
        } else {
          // 他のボタンが押されたため，スクロールは無効化されており，jキーを押す処理も施されている状態
        }
        scrolling = false;
      }
      return false;
    default:
      if (scrolling) {
        // Jが押されているが，他のコードが押された場合
        // スクロールを無効化
        scrolling = false;
        keyball_set_scroll_mode(false);
        // 短い間しか押されていなかった場合はJをtap
        if (timer_read32() - last_KK_J_SCLN_pressed < SCRL_TAPPING_TERM) {
          tap_code(KC_J);
        }
        // あとの処理をデフォルトに任せる．
      }
      return true;
  }
}

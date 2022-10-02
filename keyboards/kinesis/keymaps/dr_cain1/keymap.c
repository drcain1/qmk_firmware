/* Copyright 2022 Nicholas Granado <ngranado@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layer_names {
    _DEFAULT,
    _KEYPAD,
};

#define DEFAULT DF(_DEFAULT)
#define KEYPAD  TG(_KEYPAD)
#define HCTLESC CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DEFAULT] = LAYOUT(
        // LHAND
        KC_ESC ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,
        KC_EQL ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,
        KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,
        HCTLESC,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,
        KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,
                KC_GRV ,KC_NUBS,KC_LEFT,KC_RGHT,
        // LTHUMB
                KC_LCTL,KC_LALT,
                        KC_HOME,
        KC_BSPC,KC_DEL ,KC_END ,
        // RHAND
        KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_PSCR,KC_SLCK,KC_PAUS,KEYPAD ,QK_BOOT,
        KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,
        KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,
        KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
        KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,
                KC_DOWN,KC_UP  ,KC_BSLS,KC_RBRC,
        // RTHUMB
        KC_RALT,KC_LGUI,
        KC_PGUP,
        KC_PGDN,KC_ENT ,KC_SPC
    ),

    [_KEYPAD] = LAYOUT (
        // LHAND
        _______,_______,_______,_______,_______,_______,_______,DEFAULT,_______,
        _______,_______,_______,_______,_______,_______,
        _______,_______,KC_MUTE,KC_VOLD,KC_VOLU,_______,
        _______,KC_MSTP,KC_MPRV,KC_MPLY,KC_MNXT,KC_MSEL,
        _______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,
        // LTHUMB
                _______,_______,
                        _______,
        _______,_______,_______,

        // RHAND
        _______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,KC_NLCK,KC_PEQL,KC_PSLS,KC_PAST,_______,
        _______,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,_______,
        _______,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,_______,
        _______,KC_P1,  KC_P2,  KC_P3,  KC_PENT,_______,
                KC_LPRN,KC_RPRN,KC_PDOT,KC_PENT,
        // RTHUMB
        _______,_______,
        _______,
        _______,KC_PENT,KC_P0
    ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
    writePinHigh(LED_NUM_LOCK_PIN);
    writePinHigh(LED_SCROLL_LOCK_PIN);
    writePinHigh(LED_COMPOSE_PIN);
    writePinHigh(LED_CAPS_LOCK_PIN);
    switch (get_highest_layer(state)) {
        case _KEYPAD:
            // Compose Lit
            writePinLow(LED_COMPOSE_PIN);
            break;
    }
  return state;
}

bool led_update_user(led_t led_state) {
    writePin(LED_SCROLL_LOCK_PIN, !led_state.scroll_lock);
    writePin(LED_NUM_LOCK_PIN, !led_state.num_lock);
    writePin(LED_CAPS_LOCK_PIN, !led_state.caps_lock);
  return false;
}


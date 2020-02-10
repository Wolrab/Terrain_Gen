#include "keyboard.h"
#include <iostream>

keyboard::callback_map keyboard::_press_CB_ascii;
keyboard::callback_map keyboard::_release_CB_ascii;

void keyboard::keyboard_init() {
    glutIgnoreKeyRepeat(GLUT_DEVICE_IGNORE_KEY_REPEAT);

    glutKeyboardFunc(_glut_press_CB_ascii);
    glutKeyboardUpFunc(_glut_release_CB_ascii);
}

void keyboard::register_press_listener_ascii(unsigned char key, void (*CB)()) {
    auto reg = _press_CB_ascii.find(key);
    if (reg == _press_CB_ascii.end()) {
        std::forward_list<void(*)()> n_reg {CB};
        _press_CB_ascii.emplace(key, n_reg);
    }
    else {
        reg->second.push_front(CB);
    }
}

void keyboard::register_release_listener_ascii(unsigned char key, void (*CB)()) {
    callback_map::iterator reg = _release_CB_ascii.find(key);
    if (reg == _release_CB_ascii.end()) {
        std::forward_list<void(*)()> n_reg {CB};
        _release_CB_ascii.emplace(key, n_reg);
    }
    else {
        reg->second.push_front(CB);
    }
}

void keyboard::_glut_press_CB_ascii(unsigned char key, int x, int y) {
    callback_map::const_iterator reg = _press_CB_ascii.find(key);
    if (reg != _press_CB_ascii.end()) {
        for (auto CB = reg->second.begin(); CB != reg->second.end(); CB++) {
            (*CB)();
        }
    }
    else {
        // Error
    }
}

void keyboard::_glut_release_CB_ascii(unsigned char key, int x, int y) {
    callback_map::const_iterator reg = _release_CB_ascii.find(key);
    if (reg != _release_CB_ascii.end()) {
        for (auto CB = reg->second.begin(); CB != reg->second.end(); CB++) {
            (*CB)();
        }
    }
    else {
        // Error
    }
}

#include "free_camera.h"

bool ack::_is_fwd, ack::_is_back, ack::_is_left, ack::_is_right;
int ack::_mouse_x_prev, ack::_mouse_x, ack::_mouse_y_prev, ack::_mouse_y;

void ack::foward_on()  { ack::_is_fwd = true; }
void ack::foward_off() { ack::_is_fwd = false;  }
void ack::back_on()    { ack::_is_back = true;  }
void ack::back_off()   { ack::_is_back = false;  }
void ack::left_on()    { ack::_is_left = true;  }
void ack::left_off()   { ack::_is_left = false;  }
void ack::right_on()   { ack::_is_right = true; }
void ack::right_off()  { ack::_is_right = false; }

ack::FreeCamera::FreeCamera(float ar) {
    keyboard::register_press_listener_ascii(_forward, ack::foward_on);
    keyboard::register_press_listener_ascii(_back, ack::back_on);
    keyboard::register_press_listener_ascii(_left, ack::left_on);
    keyboard::register_press_listener_ascii(_right, ack::right_on);
    keyboard::register_release_listener_ascii(_forward, ack::foward_off);
    keyboard::register_release_listener_ascii(_back, ack::back_off);
    keyboard::register_release_listener_ascii(_left, ack::left_off);
    keyboard::register_release_listener_ascii(_right, ack::right_off);

    // Mouse

    ack::_is_fwd = ack::_is_back = ack::_is_left = ack::_is_right = false;
    ack::_mouse_x_prev = ack::_mouse_x = ack::_mouse_y_prev = ack::_mouse_y = 0;

    _perspective_mat = glm::perspective(45.f, ar, 0.1f, 100.f);

    _position = glm::vec3(0.f, 0.f, 0.f);
    _direction = glm::vec3(0.f, 0.f, 1.f);
    _up = glm::vec3(0.f, 1.f, 0.f);
    _view_mat = glm::lookAt(_position, _direction, _up);
}

void ack::FreeCamera::update(float dt) {
    float diff = dt * move_ups;
    if (_is_fwd) {
        _position  += glm::vec3(0.f, 0.f, diff);
        _direction += glm::vec3(0.f, 0.f, diff);
    }
    else if (_is_back) {
        _position  += glm::vec3(0.f, 0.f, -diff);
        _direction += glm::vec3(0.f, 0.f, -diff);
    }
    if (_is_left) {
        _position  += glm::vec3(diff, 0.f, 0.f);
        _direction += glm::vec3(diff, 0.f, 0.f);
    }
    else if (_is_right) {
        _position  += glm::vec3(-diff, 0.f, 0.f);
        _direction += glm::vec3(-diff, 0.f, 0.f);
    }

    _view_mat = glm::lookAt(_position, _direction, _up);
}


void ack::FreeCamera::view_reset() {
    _view_mat = glm::mat4x4(1.f);
}

void ack::FreeCamera::view_translate(const glm::vec3& pos) {
    // Useless
}

void ack::FreeCamera::view_rotate(float rads, const glm::vec3& axis) {
    // Useless
}

const glm::mat4x4& ack::FreeCamera::get_view_mat() {
    return _view_mat;
}

const glm::mat4x4& ack::FreeCamera::get_perspective_mat() {
    return _perspective_mat;
}

const glm::mat4x4& ack::FreeCamera::get_perspective_view_mat() {
    _perspective_view_mat = _perspective_mat * _view_mat;
    return _perspective_view_mat;
}
#ifndef _FREE_CAMERA_H
#define _FREE_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "keyboard.h"

// TODO: THIS IS REALLY BAD OH MY LORD
namespace ack {
    extern bool _is_fwd, _is_back, _is_left, _is_right;
    extern int _mouse_x_prev, _mouse_x, _mouse_y_prev, _mouse_y;

    void foward_on();
    void foward_off();
    void back_on();
    void back_off();
    void left_on();
    void left_off();
    void right_on();
    void right_off();

    class FreeCamera {
    public:
        FreeCamera(float ar);

        void update(float dt);

        // Not necessary?
        void view_reset();
        void view_translate(const glm::vec3& pos);
        void view_rotate(float rads, const glm::vec3& axis);

        const glm::mat4x4& get_view_mat();
        const glm::mat4x4& get_perspective_mat();
        const glm::mat4x4& get_perspective_view_mat();

    private:
        const float move_ups = 1.f;
        char _forward = 'w', _back = 's', _left = 'a', _right = 'd';

        glm::vec3 _position;
        glm::vec3 _direction;
        glm::vec3 _up;

        glm::mat4x4 _view_mat;
        glm::mat4x4 _perspective_mat;
        glm::mat4x4 _perspective_view_mat;

        double pitch();
    };
}

#endif /* _FREE_CAMERA_H */
#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <unordered_map>
#include <forward_list>

namespace keyboard {
    typedef std::unordered_map<unsigned char, std::forward_list<void (*)()> > callback_map;
    extern callback_map _press_CB_ascii;
    extern callback_map _release_CB_ascii;
    
    void _glut_press_CB_ascii(unsigned char key, int x, int y);
    void _glut_release_CB_ascii(unsigned char key, int x, int y);

    void keyboard_init();
    void register_press_listener_ascii(unsigned char code, void (*CB)());
    void register_release_listener_ascii(unsigned char code, void (*CB)());
}

#endif /* __KEYBOARD_H */
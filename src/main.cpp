// OpenGL
#include <GL/glew.h>
#include <GL/freeglut.h>

// GLM
#include <glm/vec4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

// stdlib
#include <string>
#include <vector>
#include <iostream>

// c
#include <math.h>
#include <time.h>

// local
#include "shader.h"
#include "cube.h"
#include "keyboard.h"
#include "free_camera.h"

// Must be uninitialized or else everything will crash
Cube* cube;
ack::FreeCamera *camera;
Shader *shaderProgram;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const float AR = float(WINDOW_WIDTH)/WINDOW_HEIGHT;

std::string VS_FNAME = "src/basic.vs";
std::string FS_FNAME = "src/basic.fs";

/** 
 * Callback functions
 */
void glutRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->use();

    // TODO: Optimize handing in pre-multiplied matricies
    if (shaderProgram->set_mat4x4f("PV", &(camera->get_perspective_view_mat()))) {
        abort();
    }
    if (shaderProgram->set_mat4x4f("WM", &(cube->get_world_model_mat()))) {
        abort();
    }

    shaderProgram->validate();
    
    cube->draw();

    glutSwapBuffers();
}

/**
 * Should only do "at most, one frame of work"
 */
void glutIdle() {
    
    static const float RADS_PER_SEC = 1.f;
    static clock_t t1 = clock();
    
    clock_t t2 = clock();
    float dt = float(t2 - t1)/CLOCKS_PER_SEC;
    cube->model_rotate(dt * RADS_PER_SEC, glm::normalize(glm::vec3(1.f, 1.f, 0.f)));
    camera->update(dt);
    t1 = t2;
    
    glutPostRedisplay();
}

/** 
 * Initialization functions
 */
void registerCallbacks() {
    glutDisplayFunc(glutRender);
    glutIdleFunc(glutIdle);
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

bool initGlew() {
    bool err = false;

    GLenum glew_err = glewInit();
    if (glew_err != GLEW_OK) {
        std::cerr << "glew error: glewInit: " << glewGetErrorString(glew_err) << std::endl;
        err = true;
    }
    return err;
}

bool initGlut(int *argc, char **argv) {
    bool err = false;

    // init glut
    glutInit(argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    // create window
    int window_id = glutCreateWindow("biggly graphics");
    if (!window_id) {
        std::cerr << "glut error: Could not create window and associated \
            openGL context.\nExiting" << std::endl;
        err = true;
    }
    return err;
}

void quit_normal() {
    // cleanup

    exit(0);
}

int main(int argc, char **argv) {
    if (initGlut(&argc, argv)) {
        return -1;
    }
    else if (initGlew()) {
        return -1;
    }
    else {
        initGL();
        shaderProgram = new Shader(VS_FNAME, FS_FNAME);
        if (shaderProgram->invalid()) {
            return -1;
        }
        else {
            // INITIALIZE KEYBOARD
            keyboard::keyboard_init();
            keyboard::register_press_listener_ascii(27, quit_normal);
            // END INITIALIZE KEYBOARD

            cube = new Cube();
            cube->model_scale(glm::vec3(0.5f, 0.5f, 0.5f));

            camera = new ack::FreeCamera(AR);

            registerCallbacks();
            glutMainLoop();
        }
    }
    return 0;
}
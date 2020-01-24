/**
 * A heavily commented main
 * Next Step: Tutorial 2
 */ 

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

/** 
 * Callback functions
 */
void glutRender() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void glutIdle() {
    // Do idle
}

/** 
 * Initialization functions
 *   TODO: Use exceptions
 */
void registerCallbacks() {
    glutDisplayFunc(glutRender);
    glutIdleFunc(glutIdle);
}

int initResources() {
    return 0;
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int initGlew() {
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "glew error: glewInit: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    return 0;
}

int initGlut(int *argc, char **argv) {
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
        return -1;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (initGlut(&argc, argv)) {
        return -1;
    }
    else if (initGlew()) {
        return -1;
    }
    else if (initResources()) {
        return -1;
    }
    else {
        initGL();
        registerCallbacks();
        glutMainLoop();
    }

    return 0;
}
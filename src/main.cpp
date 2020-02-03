// OpenGL
#include <GL/glew.h>
#include <GL/freeglut.h>

// GLM
#include <glm/vec4.hpp>
#include <glm/ext/matrix_transform.hpp>

// stdlib
#include <string>
#include <iostream>

// c
#include <math.h>
#include <assert.h> // TODO: Use actuall c++ assertions

// local
#include "shader.h"

using namespace std;

GLuint VBO;
Shader *shaderProgram;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

string VS_FNAME = "src/basic.vs";
string FS_FNAME = "src/basic.fs";

/** 
 * Callback functions
 */
void glutRender() {
    // If the depth buffer is not cleared, the second rendered frame
    //   eats shit and dies.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->validate();
    shaderProgram->use();

    // Our buffer still at 0 somehow
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
    
    glutSwapBuffers();
}

/**
 * Should only do "at most, one frame of work"
 */
void glutIdle() {
    static float scale = 0.0f;
    scale += 0.001f;
    shaderProgram->set_float("scale", sinf(scale));

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

void initResources() {
    // My stuff
    glm::vec4 v[3];
    v[0] = glm::vec4{0.0f, 1.0f, 0.0f, 1.0f};
    v[1] = glm::vec4{1.0f, -1.0f, 0.0f, 1.0f};
    v[2] = glm::vec4{-1.0f, -1.0f, 0.0f, 1.0f};

    // Stick it in da state machine!!!
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // If buffer contents would be changed, GL_DYNAMIC_DRAW should be used instead
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
}

/*
bool compileShader(const GLchar *src, GLint src_len, GLenum type, GLuint& obj) {
    bool err = false;

    obj = glCreateShader(type);

    const GLchar *c_src[1];
    c_src[0] = src;
    glShaderSource(obj, 1, c_src, &src_len);
    glCompileShader(obj);

    GLint success;
    glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar log[4096];
        glGetShaderInfoLog(obj, sizeof(log), NULL, log);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", type, log);

        err = true;
    }
    return err;
}

bool createShaderProgram() {
    bool err = false;

    shaderProgram = glCreateProgram();
    GLuint vs, fs;
    string vs_src, fs_src;

    if (getShaderSource(VS_FNAME, vs_src)) {
        err = true;
    }
    else if (compileShader(vs_src.c_str(), vs_src.length(), GL_VERTEX_SHADER, vs)) {
        err = true;
    }
    else {
        glAttachShader(shaderProgram, vs);

        if (getShaderSource(FS_FNAME, fs_src)) {
            err = true;
        }
        else if (compileShader(fs_src.c_str(), fs_src.length(), GL_FRAGMENT_SHADER, fs)) {
            err = true;
        }
        else {
            glAttachShader(shaderProgram, fs);
        }
    }

    // Compilation successfull
    if (!err) {
        glLinkProgram(shaderProgram);
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar log[4096];
            glGetProgramInfoLog(shaderProgram, sizeof(log), NULL, log);
            fprintf(stderr, "Error linking program: '%s'\n", log);

            err = true;
        }
        else {
            // Once program gets complicated, possibly need before every draw call
            glValidateProgram(shaderProgram);
            glUseProgram(shaderProgram);

            // Get locations from program
            scaleLoc = glGetUniformLocation(shaderProgram, "scale");
            assert(scaleLoc != -1);
        }
    }

    return err;
}
*/
bool initGlew() {
    bool err = false;

    GLenum glew_err = glewInit();
    if (glew_err != GLEW_OK) {
        cerr << "glew error: glewInit: " << glewGetErrorString(glew_err) << endl;
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
        cerr << "glut error: Could not create window and associated \
            openGL context.\nExiting" << endl;
        err = true;
    }
    return err;
}

int main(int argc, char **argv) {
    if (initGlut(&argc, argv)) {
        return -1;
    }
    else if (initGlew()) {
        return -1;
    }
    else {
        shaderProgram = new Shader(VS_FNAME, FS_FNAME);
        if (shaderProgram->invalid()) {
            exit(1);
        }
        initResources();
        initGL();
        registerCallbacks();
        glutMainLoop();
    }
    return 0;
}
#include "cube.h"

// Initialize static class members

GLuint *Cube::vbo = nullptr;
GLuint *Cube::ibo = nullptr;

// Points chosen bottom to top, left to right, front to back
// IF U CONSIDER 1.0Z TO BE THE FRONT, LIKE SOME KIND OF DINGUS
const float Cube::vertices[] = {
    -1.f, -1.f,  1.f,    1.f,  0.f,  0.f, // 1R 0
    -1.f, -1.f,  1.f,    0.f,  1.f,  0.f, // 1G 1
    -1.f, -1.f,  1.f,    0.f,  0.f,  1.f, // 1B 2

    -1.f, -1.f, -1.f,    1.f,  0.f,  0.f, // 2R 3
    -1.f, -1.f, -1.f,    0.f,  1.f,  0.f, // 2G 4
    -1.f, -1.f, -1.f,    0.f,  0.f,  1.f, // 2B 5
    
     1.f, -1.f,  1.f,    1.f,  0.f,  0.f, // 3R 6
     1.f, -1.f,  1.f,    0.f,  1.f,  0.f, // 3G 7
     1.f, -1.f,  1.f,    0.f,  0.f,  1.f, // 3B 8

     1.f, -1.f, -1.f,    1.f,  0.f,  0.f, // 4R 9
     1.f, -1.f, -1.f,    0.f,  1.f,  0.f, // 4G 10
     1.f, -1.f, -1.f,    0.f,  0.f,  1.f, // 4B 11

    -1.f,  1.f,  1.f,    1.f,  0.f,  0.f, // 5R 12
    -1.f,  1.f,  1.f,    0.f,  1.f,  0.f, // 5G 13
    -1.f,  1.f,  1.f,    0.f,  0.f,  1.f, // 5B 14

    -1.f,  1.f, -1.f,    1.f,  0.f,  0.f, // 6R 15
    -1.f,  1.f, -1.f,    0.f,  1.f,  0.f, // 6G 16
    -1.f,  1.f, -1.f,    0.f,  0.f,  1.f, // 6B 17

     1.f,  1.f,  1.f,    1.f,  0.f,  0.f, // 7R 18
     1.f,  1.f,  1.f,    0.f,  1.f,  0.f, // 7G 19
     1.f,  1.f,  1.f,    0.f,  0.f,  1.f, // 7B 20

     1.f,  1.f, -1.f,    1.f,  0.f,  0.f, // 8R 21
     1.f,  1.f, -1.f,    0.f,  1.f,  0.f, // 8G 22
     1.f,  1.f, -1.f,    0.f,  0.f,  1.f  // 8B 23
};

const unsigned short Cube::indices[] = {
     0,  3,  9, // Bottom
     0,  6,  9, 
     1,  4, 16, // Left
     1, 13, 16,
     2,  8, 20, // Front
     2, 14, 20, 
    21, 12, 15, // Top
    21, 12, 18, 
    22,  7, 10, // Right
    22,  7, 19, 
    23,  5, 11, // Back
    23,  5, 17
};

Cube::Cube() {
    if (vbo == nullptr && ibo == nullptr) {
        vbo = new GLuint;
        ibo = new GLuint;

        glGenBuffers(1, vbo);
        glBindBuffer(GL_ARRAY_BUFFER, *vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
    else if (vbo == nullptr || ibo == nullptr) {
        abort(); // Fucking abandon ship fuck that
    }
    model_mat = glm::mat4x4(1.f);
    world_mat = glm::mat4x4(1.f);
}

Cube::~Cube() {
    // I'd need to use smart pointers n shit to release vbo/ibo
}

void Cube::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Cube::model_reset() {
    model_mat = glm::mat4x4(1.f);
}

void Cube::model_scale(const glm::vec3& scale) {
    model_mat = glm::scale(model_mat, scale);
}

void Cube::model_translate(const glm::vec3& pos) {
    model_mat = glm::translate(model_mat, pos);
}

void Cube::model_rotate(float rads, const glm::vec3& axis) {
    model_mat = glm::rotate(model_mat, rads, axis);
}

void Cube::world_reset() {
    world_mat = glm::mat4x4(1.f);
}

void Cube::world_translate(const glm::vec3& pos) {
    world_mat = glm::translate(world_mat, pos);
}

void Cube::world_rotate(float rads, const glm::vec3& axis) {
    world_mat = glm::rotate(world_mat, rads, axis);
}

const glm::mat4x4& Cube::get_model_mat() {
    return model_mat;
}

const glm::mat4x4& Cube::get_world_mat() {
    return world_mat;
}
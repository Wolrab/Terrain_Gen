// No inheretance because I don't know what I'm doing yet
// The model is a immutable singleton I type all by hand
// This is all shaping up to be very epic indeed
#ifndef __CUBE_H
#define __CUBE_H

#include <GL/glew.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Cube {
public:
    Cube();
    ~Cube();

    void draw();

    void model_reset();
    void model_scale(const glm::vec3& scale);
    void model_translate(const glm::vec3& pos);
    void model_rotate(float rads, const glm::vec3& axis);

    void world_reset();
    void world_translate(const glm::vec3& pos);
    void world_rotate(float rads, const glm::vec3& axis);
    
    const glm::mat4x4& get_model_mat(); // SUS
    const glm::mat4x4& get_world_mat(); // SUS

private:
    static GLuint *vbo;
    static GLuint *ibo;

    const static float vertices[];
    const static unsigned short indices[];

    glm::mat4x4 model_mat;
    glm::mat4x4 world_mat;
};

#endif /* __CUBE_H */
#ifndef __SHADER_H
#define __SHADER_H

#include <GL/glew.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <unordered_map>

class Shader {
public:
    Shader(const std::string& vs_fname, const std::string& fs_fname);
    ~Shader();
    bool invalid();
    
    // Validate and use the shader program
    void validate();
    void use();
    
    // Sets any uniforms within the shader program
    int set_float(const std::string& uniform, const float f);
    int set_vec3f(const std::string& uniform, const glm::vec3 *v);
    int set_vec4f(const std::string& uniform, const glm::vec4 *v);
    int set_mat3x3f(const std::string& uniform, const glm::mat3x3 *m);
    int set_mat4x4f(const std::string& uniform, const glm::mat4x4 *m);
    
private:
    GLuint _pID = -1;
    bool _invalid = false;
    std::unordered_map<std::string, GLint> *_map_uniforms = nullptr;

    int _compile_object(const GLuint obj, const std::string& src);
    int _add_uniform(const std::string& uniform);
};

#endif /* __SHADER_H */
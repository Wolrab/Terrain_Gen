#include "shader.h"

Shader::Shader(const std::string& vs_fname, const std::string& fs_fname) {
    std::string vs_src, fs_src;
    std::ifstream vs_file, fs_file;

    vs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vs_file.open(vs_fname.c_str());
        fs_file.open(fs_fname.c_str());

        std::stringstream vs_buf, fs_buf;

        vs_buf << vs_file.rdbuf();
        fs_buf << fs_file.rdbuf();
        
        vs_file.close();
        fs_file.close();

        vs_src = vs_buf.str();
        fs_src = fs_buf.str();
    }
    catch (std::ifstream::failure e) {
        _invalid = true;
        
        std::cerr << "Shader: Shader Source Retrieval Failed: " << e.what() << std::endl;
        return;
    }

    GLchar err_log[1024];

    GLuint vs_obj = glCreateShader(GL_VERTEX_SHADER);
    if (_compile_object(vs_obj, vs_src)) {
        _invalid = true;

        glGetShaderInfoLog(vs_obj, sizeof(err_log), 0, err_log);
        std::cerr << "Shader: vertex shader unable to compile: " << err_log << std::endl;
        return;
    }

    GLuint fs_obj = glCreateShader(GL_FRAGMENT_SHADER);
    if (_compile_object(fs_obj, fs_src)) {
        _invalid = true;

        glGetShaderInfoLog(fs_obj, sizeof(err_log), 0, err_log);
        std::cerr << "Shader: fragment shader unable to compile: " << err_log << std::endl;
        return;
    }

    GLuint pID = glCreateProgram();
    glAttachShader(pID, vs_obj);
    glAttachShader(pID, fs_obj);
    glLinkProgram(pID);

    GLint success;
    glGetProgramiv(pID, GL_LINK_STATUS, &success);
    if (!success) {
        _invalid = true;

        glGetProgramInfoLog(pID, sizeof(err_log), 0, err_log);
        std::cerr << "Shader: shader program unable to link: " << err_log << std::endl;
        return;
    }

    glDeleteShader(vs_obj);
    glDeleteShader(fs_obj);

    _pID = pID;
    _map_uniforms = new std::unordered_map<std::string, GLint>();
}

Shader::~Shader() {
    delete _map_uniforms;
}

bool Shader::invalid() {
    return _invalid;
}

void Shader::validate() {
    glValidateProgram(_pID);
}

void Shader::use() {
    glUseProgram(_pID);
}

int Shader::set_float(const std::string& uniform, const float f) {
    int err = 0;

    if (_map_uniforms->count(uniform) == 0) {
        err = _add_uniform(uniform);
    }
    if (!err) {
        std::unordered_map<std::string, GLint>::const_iterator uniform_pair = _map_uniforms->find(uniform);
        glUniform1f(uniform_pair->second, f);
    }
    return err;
}

int Shader::set_vec3f(const std::string& uniform, const glm::vec3 *v) {
    int err = 0;

    if (_map_uniforms->count(uniform) == 0) {
        err = _add_uniform(uniform);
    }
    if (!err) {
        std::unordered_map<std::string, GLint>::const_iterator uniform_pair = _map_uniforms->find(uniform);
        glUniform3fv(uniform_pair->second, 1, (GLfloat*)v);
    }
    return err;
}

int Shader::set_vec4f(const std::string& uniform, const glm::vec4 *v) {
    int err = 0;

    if (_map_uniforms->count(uniform) == 0) {
        err = _add_uniform(uniform);
    }
    if (!err) {
        std::unordered_map<std::string, GLint>::const_iterator uniform_pair = _map_uniforms->find(uniform);
        glUniform4fv(uniform_pair->second, 1, (GLfloat*)v);
    }
    return err;
}

int Shader::set_mat3x3f(const std::string& uniform, const glm::mat3x3 *m) {
    int err = 0;

    if (_map_uniforms->count(uniform) == 0) {
        err = _add_uniform(uniform);
    }
    if (!err) {
        std::unordered_map<std::string, GLint>::const_iterator uniform_pair = _map_uniforms->find(uniform);
        glUniformMatrix3fv(uniform_pair->second, 1, GL_FALSE, (GLfloat*)m);
    }
    return err;
}

int Shader::set_mat4x4f(const std::string& uniform, const glm::mat4x4 *m) {
    int err = 0;

    if (_map_uniforms->count(uniform) == 0) {
        err = _add_uniform(uniform);
    }
    if (!err) {
        std::unordered_map<std::string, GLint>::const_iterator uniform_pair = _map_uniforms->find(uniform);
        glUniformMatrix4fv(uniform_pair->second, 1, GL_FALSE, (GLfloat*)m);
    }
    return err;
}

int Shader::_compile_object(const GLuint obj, const std::string& src) {
    const GLchar* src_c = src.c_str();
    const GLint src_len = src.length();
    glShaderSource(obj, 1, &src_c, &src_len);
    glCompileShader(obj);

    GLint success;
    glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
    return !success;
}

int Shader::_add_uniform(const std::string& uniform) {
    int err = 0;

    GLint uniform_loc = glGetUniformLocation(_pID, uniform.c_str());
    if (uniform_loc == -1) {
        err = -1;
    }
    else {
        _map_uniforms->emplace(uniform, uniform_loc);
    }
    return err;
}
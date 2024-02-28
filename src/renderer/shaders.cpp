#include "shaders.h"

bool ShaderProgram::createShader(const string& source, const GLenum shaderType, GLuint &shaderId) {
    shaderId = glCreateShader(shaderType);
    const char* code = source.c_str();
    glShaderSource(shaderId, 1, &code, nullptr);
    glCompileShader(shaderId);

    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar buf[1024];
        glGetShaderInfoLog(shaderId, 1024, nullptr, buf);
        cerr << "Error in ShaderProgram::createShader:\n" << buf << '\n';
        return false;
    }

    return true;
}

ShaderProgram::ShaderProgram(const string& vertexShader, const string& fragmentShader) {
    GLuint vertexShaderId = 0;
    if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderId)) {
        cerr << "Error in ShaderProgram::ShaderProgram -> VERTEX SHADER." << '\n';
        return;
    }

    GLuint fragmentShaderId = 0;
    if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderId)) {
        cerr << "Error in ShaderProgram::ShaderProgram -> VERTEX SHADER." << '\n';
        glDeleteShader(vertexShaderId);
        return;
    }

    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    GLint success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar buf[1024];
        glGetProgramInfoLog(programId, 1024, nullptr, buf);
        cerr << "Error in ShaderProgram::createShader:\n" << buf << '\n';
        return;
    }

    isCompiled_f = true;
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programId);
}

void ShaderProgram::use() {
    glUseProgram(programId);
}

void ShaderProgram::setInt(const string& name, int val) {
    GLuint id = glGetUniformLocation(programId, name.c_str());
    glUniform1i(id, val);
}

void ShaderProgram::setMatrix4(const string& name, mat4 matrix4) {
    GLuint id = glGetUniformLocation(programId, name.c_str());
    glUniformMatrix4fv(id, 1, GL_FALSE, value_ptr(matrix4));
}
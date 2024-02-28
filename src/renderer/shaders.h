#pragma once
#include <string>
#include <iostream>
#include <GLAD/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.inl>

using namespace std;
using namespace glm;

class ShaderProgram {
public:
	ShaderProgram(const string& vertexShader, const string& fragmentShader);
	~ShaderProgram();
	bool isCompiled() const { return isCompiled_f; };
	void use();
	void setInt(const string& name, int val);
	void setMatrix4(const string& name, mat4 matrix4);

private:
	bool createShader(const string& source, const GLenum shaderType, GLuint &shaderId);
	bool isCompiled_f = false;
	GLuint programId = 0;
};

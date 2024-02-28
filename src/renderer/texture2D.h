#pragma once
#include <iostream>
#include <glad/glad.h>

using namespace std;

class Texture2D {
private:
	int width = 0;
	int height = 0;
	GLenum format = GL_RGBA;
	GLuint textureId = 0;

public:
	Texture2D(int width, int height, unsigned char* pixels, unsigned int channels = 4, GLenum filter = GL_NEAREST, GLenum wrapMode = GL_CLAMP_TO_EDGE);
	~Texture2D();
	void bind();
};
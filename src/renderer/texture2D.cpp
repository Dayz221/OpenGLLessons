#include "texture2D.h"

Texture2D::Texture2D(int width, int height, unsigned char* pixels, unsigned int channels, GLenum filter, GLenum wrapMode) {
	this->width = width;
	this->height = height;

	switch (channels) {
		case 3: format = GL_RGB; break;
		default: format = GL_RGBA; break;
	}

	glGenTextures(1, &textureId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &textureId);
}

void Texture2D::bind() {
	glBindTexture(GL_TEXTURE_2D, textureId);
}
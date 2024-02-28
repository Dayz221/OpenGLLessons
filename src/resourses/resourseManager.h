#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "../renderer/shaders.h"
#include "../renderer/texture2D.h"

using namespace std;

class ResourseManager {
private:
	string fullPath;
	map<string, ShaderProgram*> shadersMap {};
	map<string, Texture2D*> texturesMap {};

public:
	ResourseManager(const string& resourse_dir_path);

	string readTxt(const string& file_path);

	void loadShaderProg(const string& vertexShaderPath, const string& fragmentShaderPath, const string& shaderProgName = "default");
	void loadTexture2D(const string& name, const string& path);

	ShaderProgram* getShaderProg(const string& shaderProgName = "default");
	Texture2D* getTexture2D(const string& textureName);
};
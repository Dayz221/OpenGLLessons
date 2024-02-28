#include "resourseManager.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG

#include "stb_image.h"


ResourseManager::ResourseManager(const string& resourse_dir_path) {
	this->fullPath = resourse_dir_path.substr(0, resourse_dir_path.find_last_of("/\\"));
}


string ResourseManager::readTxt(const string& file_path) {
	ifstream istream((fullPath + '\\' + file_path).c_str());
	if (!istream.is_open()) {
		cerr << fullPath << endl;
		cerr << "Error in FileReader::readTxt" << '\n';
		return "";
	}

	stringstream buf;
	buf << istream.rdbuf();
	return buf.str();
}

void ResourseManager::loadShaderProg(const string& vertexShaderPath, const string& fragmentShaderPath, const string& shaderProgName) {
	const string vertexShader = this->readTxt(vertexShaderPath);
	const string fragmentShader = this->readTxt(fragmentShaderPath);

	ShaderProgram* shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
	if (!shaderProgram->isCompiled()) {
		cerr << "Error in compiling shader program in ResourseManager::loadShaderProg." << '\n';
		return;
	}

	shadersMap.emplace(shaderProgName, shaderProgram);
}

void ResourseManager::loadTexture2D(const string& name, const string& path) {
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(string(fullPath + "\\" + path).c_str(), &width, &height, &channels, 0);

	if (!pixels) {
		cerr << "Error on load texture in FileReader::loadTexture\n";
		return;
	}
	else {
		cout << "Continue load texture: \"" << path << "\"; width: " << width << "; height: " << height << '\n';
	}

	Texture2D* texture = new Texture2D(width, height, pixels, channels, GL_LINEAR, GL_CLAMP_TO_EDGE);

	texturesMap.emplace(name, texture);
	stbi_image_free(pixels);
}

ShaderProgram* ResourseManager::getShaderProg(const string& shaderProgName) {
	return shadersMap[shaderProgName];
}

Texture2D* ResourseManager::getTexture2D(const string& textureName) {
	return texturesMap[textureName];
}
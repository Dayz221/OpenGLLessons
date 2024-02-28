#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/vec2.hpp>

using namespace std;
using namespace glm;

class Window {
private:
	GLuint width = 0;
	GLuint height = 0;
	float lastTime = 0;
	float delta = 0;
	string caption;
	GLFWwindow* window;

	friend void defaultResizeCallback(GLFWwindow* window, int width, int height);
	friend void defaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	void keyCallback(int key, int scancode, int action, int mode);

public:
	Window(GLuint width, GLuint height, string caption = "The window powered by Dayz221");

	int printError(string err);

	int getWidth();
	int getHeight();
	float getAspect();
	vec2 getSize();
	string& getCaption();
	GLFWwindow* getWindow();
	bool isClose();
	int getFps();

	void setSize(int width, int height);
	void setSize(vec2 size);
	void setCaption(string caption);
	void attachResizeCallback(GLFWwindowsizefun func);
	void attachKeyCallback(GLFWkeyfun func);
	void update();

	void closeWindow();
	void terminate();
};

void defaultResizeCallback(GLFWwindow* window, int width, int height);
void defaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
static Window* curWindow;
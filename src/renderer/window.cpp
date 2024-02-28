#include "window.h"

int Window::printError(string err) {
    cerr << err << "\n";
    return EXIT_FAILURE;
}

Window::Window(GLuint width, GLuint height, string caption) : width(width), height(height), caption(caption) {
    if (!glfwInit()) {
        printError("[!] Can't init GLFW.");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, caption.c_str(), nullptr, nullptr);
    if (!window) {
        printError("[!] Can't create window.");
        terminate();
        return;
    }

    curWindow = this;

    glfwSetWindowSizeCallback(window, defaultResizeCallback);
    glfwSetKeyCallback(window, defaultKeyCallback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        printError("[!] Can't load openGL.");
        return;
    }
}

void Window::setSize(int width, int height) {
    this->width = width;
    this->height = height;
    glViewport(0, 0, width, height);
    glfwSetWindowSize(window, width, height);
}

void Window::setSize(vec2 size) {
    setSize(size.x, size.y);
}

void Window::setCaption(string caption) {
    this->caption = caption;
    glfwSetWindowTitle(window, caption.c_str());
}

void Window::attachResizeCallback(GLFWwindowsizefun func) {
    glfwSetWindowSizeCallback(window, func);
}

void Window::attachKeyCallback(GLFWkeyfun func) {
    glfwSetKeyCallback(window, func);
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
    delta = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();
}

void Window::closeWindow() {
    glfwSetWindowShouldClose(window, true);
}

void Window::terminate() {
    glfwTerminate();
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

vec2 Window::getSize() {
    return vec2(width, height);
}

float Window::getAspect() {
    return (float)width / height;
}

string& Window::getCaption() {
    return caption;
}

GLFWwindow* Window::getWindow() {
    return window;
}

bool Window::isClose() {
    return glfwWindowShouldClose(window);
}

int Window::getFps() {
    return (1.0f / delta);
}

void Window::keyCallback(int key, int scancode, int action, int mode) {
    //cout << "Key event: " << key << " " << scancode << " " << action << " " << mode << '\n';
    if (action == GLFW_PRESS && glfwGetKeyName(key, scancode))
        cout << "Pressed key: " << glfwGetKeyName(key, scancode) << '\n';
}


void defaultResizeCallback(GLFWwindow* window, int width, int height) {
    curWindow->setSize(width, height);
}

void defaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    curWindow->keyCallback(key, scancode, action, mode);
}
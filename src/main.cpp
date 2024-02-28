#include <iostream>

#include "renderer/window.h"
#include "resourses/resourseManager.h"

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

using namespace std;
using namespace glm;

GLfloat vertexes[] = {
    //  x      y      z      r      g      b      u      v
       0.0f,  50.f,  0.0f,  0.0f,  0.0f,  0.0f,  0.5f,  1.0f,
       50.f, -50.f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
       -50.f, -50.f, 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
};

void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, true);
    }
}

Window window(640, 480, "My Window");
int main(int argc, char** argv) {
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "Version: " << glGetString(GL_VERSION) << endl;

    glClearColor(0.2, 0.6f, 0.4f, 1); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    ResourseManager resourceManager(argv[0]);
    resourceManager.loadShaderProg("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl");
    resourceManager.loadTexture2D("tex1", "res\\textures\\texture.png");
    resourceManager.loadTexture2D("tex2", "res\\textures\\texture2.png");

    ShaderProgram* defaultShaderProgram = resourceManager.getShaderProg();

    GLuint vertexes_vbo = 0;
    glGenBuffers(1, &vertexes_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertexes_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Передать в шейдер данные о позиции, цвете и текстуре
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexes_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexes_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexes_vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // 

    defaultShaderProgram->use();
    resourceManager.getTexture2D("tex2")->bind();
    defaultShaderProgram->setInt("tex", 0);

    float theta = 0;

    mat4 modelMatrix = mat4(1.0f);
    modelMatrix = translate(modelMatrix, vec3(0, 20, -100));
    mat4 projectMatrix = mat4(1.0f);

    while (!window.isClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        theta += 0.02;
        window.setCaption("FPS: " + to_string(window.getFps()));

        projectMatrix = perspective<float>(90, window.getAspect(), 0.01f, 100);
        //projectMatrix = perspectiveFov<float>(90, window.getWidth(), window.getHeight(), 0, 500);
        defaultShaderProgram->setMatrix4("projMat", projectMatrix);

        modelMatrix = mat4(1.0f);
        modelMatrix = translate(modelMatrix, vec3(0, 0, -60+sin(theta)*10));
        defaultShaderProgram->setMatrix4("modelMat", modelMatrix);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

        window.update();
    }

    window.terminate();
    return 0;
}
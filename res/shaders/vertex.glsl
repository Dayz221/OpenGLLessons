#version 460 core

layout(location = 0) in vec3 vpos;
layout(location = 1) in vec3 vcolor;
layout(location = 2) in vec2 texPos;

out vec3 color;
out vec2 texCoord;

uniform mat4 modelMat;
uniform mat4 projMat;

void main() {
   color = vcolor;
   texCoord = texPos;
   gl_Position = projMat * modelMat * vec4(vpos, 1.0);
}
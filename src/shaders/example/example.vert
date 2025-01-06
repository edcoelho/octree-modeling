#version 330 core

layout(location=0) in vec3 position;
in vec4 color;

out vec4 vertex_color;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main() {

    gl_Position = projection_mat * view_mat * model_mat * vec4(position, 1.0);
    vertex_color = color;

}
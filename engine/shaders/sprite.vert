#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_tex;

out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(in_pos, 1.0);
  tex_coords = vec2(in_tex.x, in_tex.y);
}
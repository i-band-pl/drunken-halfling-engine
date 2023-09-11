#include "shader.h"

u32 dh_shader_load(const char* vertex_path, const char* fragment_path) {
  // vertex Shader
  u32 vertexShader = dh_shader_create_vertex(vertex_path);

  // fragment Shader
  u32 fragmentShader = dh_shader_create_fragment(fragment_path);

  // shader Program
  int success;
  char infoLog[512];
  u32 shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("error while initializing the shader program %s \n", infoLog);
  }

  // use shader program and delete unnesseary data
  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

u32 dh_shader_create_fragment(const char* fragmentShaderPath) {
  char path[512];
  strcpy(path, SHADER_PATH);
  strcat(path, fragmentShaderPath);
  const char* fragmentShaderData = dh_reader_read_data(path);
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderData, NULL);
  glCompileShader(fragmentShader);

  int success;
  char infoLog[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("error while comipling fragment shader: %s \n", infoLog);
  }

  return fragmentShader;
}

u32 dh_shader_create_vertex(const char* vertexShaderPath) {
  char path[512];
  strcpy(path, SHADER_PATH);
  strcat(path, vertexShaderPath);
  const char* vertexShaderData = dh_reader_read_data(path);
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderData, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("error while comipling vertex shader: %s \n", infoLog);
  }

  return vertexShader;
}

void dh_shader_use(shader* shader) {
  glUseProgram(shader->id);
}
void dh_shader_set_bool(shader* shader, const char* name, int value) {
  glUniform1i(glGetUniformLocation(shader->id, name), value);
}
void dh_shader_set_int(shader* shader, const char* name, int value) {
  glUniform1i(glGetUniformLocation(shader->id, name), value);
}
void dh_shader_set_float(shader* shader, const char* name, float value) {
  glUniform1f(glGetUniformLocation(shader->id, name), value);
}
void dh_shader_set_vec2(shader* shader, const char* name, vec2 value) {
  glUniform2f(glGetUniformLocation(shader->id, name), value[0], value[1]);
}
void dh_shader_set_vec3(shader* shader, const char* name, vec3 value) {
  glUniform3f(glGetUniformLocation(shader->id, name), value[0], value[1], value[2]);
}
void dh_shader_set_vec4(shader* shader, const char* name, vec4 value) {
  glUniform4f(glGetUniformLocation(shader->id, name), value[0], value[1], value[2], value[3]);
}
void dh_shader_set_mat2(shader* shader, const char* name, mat2 value) {
  glUniformMatrix2fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (float*)value);
}
void dh_shader_set_mat3(shader* shader, const char* name, mat3 value) {
  glUniformMatrix3fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (float*)value);
}
void dh_shader_set_mat4(shader* shader, const char* name, mat4 value) {
  glUniformMatrix4fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (float*)value);
}
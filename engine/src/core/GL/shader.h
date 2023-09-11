#pragma once

#include <stdlib.h>
#include <string.h>

#include "CGLM/cglm.h"
#include "core/reader.h"
#include "defines.h"
#include "glad.h"

#define SHADER_PATH "./shaders/"

typedef struct shader {
  u32 id;
} shader;

DHAPI u32 dh_shader_load(const char* vertex_path, const char* fragment_path);

DHAPI void dh_shader_use(shader* shader);
DHAPI void dh_shader_set_bool(shader* shader, const char* name, int value);
DHAPI void dh_shader_set_int(shader* shader, const char* name, int value);
DHAPI void dh_shader_set_float(shader* shader, const char* name, float value);
DHAPI void dh_shader_set_vec2(shader* shader, const char* name, vec2 value);
DHAPI void dh_shader_set_vec3(shader* shader, const char* name, vec3 value);
DHAPI void dh_shader_set_vec4(shader* shader, const char* name, vec4 value);
DHAPI void dh_shader_set_mat2(shader* shader, const char* name, mat2 value);
DHAPI void dh_shader_set_mat3(shader* shader, const char* name, mat3 value);
DHAPI void dh_shader_set_mat4(shader* shader, const char* name, mat4 value);

u32 dh_shader_create_vertex(const char* vertexShaderPath);
u32 dh_shader_create_fragment(const char* fragmentShaderPath);

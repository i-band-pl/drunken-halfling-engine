#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "CGLM/cglm.h"
#include "defines.h"
#include "glad.h"
#include "vertex.h"

typedef struct sprite {
  u32 vao;
  u32 ibo;
  u32 vbo;
  i32 vertices_count;
  size_t buffer_size;
  vertex* vertices;
  vec3 color;
  vec3 scale;
} sprite;

DHAPI void dh_sprite_init(sprite* sprite);
DHAPI void dh_sprite_render(sprite* sprite);
DHAPI void dh_sprite_bind(sprite* sprite);

#pragma once

#include <defines.h>

typedef struct entity {
  i32 uuid;
} entity;

typedef struct transform {
  i32 owner_uuid;
  f32 x;
  f32 y;
  f32 z;
} transform;

typedef struct sprite_renderer {
  i32 owner_uuid;
} sprite_renderer;
#pragma once
#include "core/GL/shader.h"
#include "core/GL/texture.h"
#include "core/camera.h"
#include "core/sprite.h"

typedef struct actor {
  texture* texture;
  shader* shader;
  sprite* sprite;
  vec3 position;
} Actor;

DHAPI void actor_init(Actor* actor);
DHAPI void actor_update(mat4* projection, Actor** actor, Camera* camera);
DHAPI void actor_destroy(Actor* actor);
DHAPI void actor_texture_load(Actor* actor, const b8* file_name);
DHAPI void actor_shader_load(Actor* actor, const b8* vertex_name, const b8* fragment_name);

DHAPI void actor_translate(f32 delta, Actor** actor, vec3 pos, f32 speed);
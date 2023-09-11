#pragma once
#include <GL/shader.h>
#include <GL/texture.h>
#include <application.h>
#include <core/camera.h>
#include <core/sprite.h>

typedef struct game_object {
  texture* texture;
  shader* shader;
  sprite* sprite;
  vec3 position;
} game_object;

void game_object_init(game_object* game_object);
void game_object_update(application_state* app, game_object* game_object, camera* camera);
void game_object_destroy(game_object* game_object);
void game_object_texture_load(game_object* game_object, const b8* file_name);
void game_object_shader_load(game_object* game_object, const b8* vertex_name, const b8* fragment_name);
#include "game_object.h"

void game_object_init(game_object* game_object) {
  game_object->shader = malloc(sizeof(shader));
  game_object->texture = malloc(sizeof(texture));
  game_object->sprite = malloc(sizeof(sprite));
}

void game_object_update(application_state* app, game_object* game_object, camera* camera) {
  dh_sprite_bind(NULL);

  dh_texture_use(game_object->texture);
  dh_shader_use(game_object->shader);

  mat4 view = GLM_MAT4_IDENTITY_INIT;
  mat4 model = GLM_MAT4_IDENTITY_INIT;

  dh_camera_get_view_matrix(camera, game_object->shader, &view);
  dh_sprite_bind(game_object->sprite);
  glm_translate(model, game_object->position);
  dh_shader_set_mat4(game_object->shader, "model", model);
  dh_shader_set_mat4(game_object->shader, "view", view);
  dh_shader_set_mat4(game_object->shader, "projection", app->projection);
  dh_shader_set_vec3(game_object->shader, "sprite_color", game_object->sprite->color);
  dh_sprite_render(game_object->sprite);
}

void game_object_destroy(game_object* game_object) {
  free(game_object->texture);
  free(game_object->shader);
  free(game_object->sprite);
}

void game_object_texture_load(game_object* game_object, const b8* file_name) {
  strcpy_s(game_object->texture->filename, sizeof(game_object->texture->filename), file_name);
  dh_texture_load(game_object->texture);
}

void game_object_shader_load(game_object* game_object, const b8* vertex_name, const b8* fragment_name) {
  game_object->shader->id = dh_shader_load(vertex_name, fragment_name);
}
#include "actor.h"

void actor_init(Actor* actor) {
  actor->shader = malloc(sizeof(shader));
  actor->texture = malloc(sizeof(texture));
  actor->sprite = malloc(sizeof(sprite));

  actor_shader_load(actor, "sprite.vert", "sprite.frag");
  dh_sprite_init(actor->sprite);
}

void actor_update(mat4* projection, Actor** actor, Camera* camera) {
  dh_sprite_bind(NULL);

  dh_texture_use((*actor)->texture);
  dh_shader_use((*actor)->shader);

  mat4 view = GLM_MAT4_IDENTITY_INIT;
  mat4 model = GLM_MAT4_IDENTITY_INIT;

  dh_camera_get_view_matrix(camera, (*actor)->shader, &view);
  dh_sprite_bind((*actor)->sprite);
  glm_translate(model, (*actor)->position);
  dh_shader_set_mat4((*actor)->shader, "model", model);
  dh_shader_set_mat4((*actor)->shader, "view", view);
  dh_shader_set_mat4((*actor)->shader, "projection", *projection);
  dh_shader_set_vec3((*actor)->shader, "sprite_color", (*actor)->sprite->color);
  dh_sprite_render((*actor)->sprite);
}

void actor_destroy(Actor* actor) {
  free(actor->texture);
  free(actor->shader);
  free(actor->sprite);
}

void actor_texture_load(Actor* actor, const b8* file_name) {
  strcpy_s(actor->texture->filename, sizeof(actor->texture->filename), file_name);
  dh_texture_load(actor->texture);
}

void actor_shader_load(Actor* actor, const b8* vertex_name, const b8* fragment_name) {
  actor->shader->id = dh_shader_load(vertex_name, fragment_name);
}

void actor_translate(f32 delta, Actor** actor, vec3 pos, f32 speed) {
  (*actor)->position[0] += pos[0] * delta * speed;
  (*actor)->position[1] += pos[1] * delta * speed;
  (*actor)->position[2] += pos[2] * delta * speed;
}
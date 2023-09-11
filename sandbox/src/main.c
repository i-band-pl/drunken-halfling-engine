#include <GL/shader.h>
#include <GL/texture.h>
#include <application.h>
#include <camera.h>
#include <input.h>
#include <sprite.h>
#include <test.h>

#include "entities/game_object.h"

typedef struct player {
  game_object* game_object;
} player;
player p;
camera cam;

void start() {
  application_state* app = dh_get_app();

  dh_camera_init(&cam);
  dh_camera_translate_pos(&cam, (vec3){0.0f, 0.0f, 3.0f});
  dh_camera_translate_front(&cam, (vec3){0.0f, 0.0f, -1.0f});
  dh_camera_translate_up(&cam, (vec3){0.0f, 1.0f, 0.0f});

  dh_projection_update();

  p.game_object = malloc(sizeof(game_object));
  game_object_init(p.game_object);
  game_object_shader_load(p.game_object, "sprite.vert", "sprite.frag");
  game_object_texture_load(p.game_object, "gigachad.png");
  dh_sprite_init(p.game_object->sprite);

  p.game_object->position[0] = 0.0f;
  p.game_object->position[1] = 0.0f;
  p.game_object->position[2] = 0.0f;
}

void render(application_state* app) {
  game_object_update(app, p.game_object, &cam);
}

void update() {
  application_state* app = dh_get_app();

  render(app);

  if (dh_get_key_down(app, GLFW_KEY_W)) {
    printf("PRESS W \n");
  }
}

int main() {
  dh_application_create(start);
  dh_application_run(update);
  return 0;
}
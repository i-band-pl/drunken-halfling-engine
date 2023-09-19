#include <application.h>
#include <camera.h>
#include <input.h>

#include "ui/editor_ui.h"

camera cam;

void start() {
  application_state* app = dh_get_app();

  dh_camera_init(&cam);
  dh_camera_translate_pos(&cam, (vec3){0.0f, 0.0f, 3.0f});
  dh_camera_translate_front(&cam, (vec3){0.0f, 0.0f, -1.0f});
  dh_camera_translate_up(&cam, (vec3){0.0f, 1.0f, 0.0f});

  dh_projection_update();
}

void update() {
}

void render_gui() {
  application_state* app = dh_get_app();

  dh_editor_update_ui(app);
}

int main() {
  dh_application_create("halfling editor", start);
  dh_application_run(update, render_gui);
  return 0;
}
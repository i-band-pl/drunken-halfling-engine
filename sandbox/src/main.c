#include <GL/shader.h>
#include <GL/texture.h>
#include <application.h>
#include <camera.h>
#include <input.h>
#include <nk_defines.h>
#include <string.h>
#include <test.h>

#include "entities/game_object.h"

typedef struct player {
  game_object* game_object;
} player;
player p;
camera cam;
f32 speed = 5.0f;

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

void render_gui() {
  struct nk_context* ctx = dh_get_nuklear_context();
  struct nk_colorf bg = dh_get_nuklear_bg();

  if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
               NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                   NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
    enum { EASY,
           HARD };
    static int op = EASY;
    static int property = 20;
    nk_layout_row_static(ctx, 30, 80, 1);

    char fps[5];
    sprintf(fps, "%d", dh_get_frames_per_second());
    nk_text(ctx, "framerate:", 10, NK_TEXT_CENTERED);
    nk_text(ctx, fps, 5, NK_TEXT_LEFT);

    if (nk_button_label(ctx, "button"))
      fprintf(stdout, "button pressed\n");

    nk_layout_row_dynamic(ctx, 30, 2);
    if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
    if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

    nk_layout_row_dynamic(ctx, 25, 1);
    nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

    nk_layout_row_dynamic(ctx, 20, 1);
    nk_label(ctx, "background:", NK_TEXT_LEFT);
    nk_layout_row_dynamic(ctx, 25, 1);
    if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
      nk_layout_row_dynamic(ctx, 120, 1);
      bg = nk_color_picker(ctx, bg, NK_RGBA);
      nk_layout_row_dynamic(ctx, 25, 1);
      bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
      bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
      bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
      bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
      nk_combo_end(ctx);
    }
  }
  nk_end(ctx);
}

void update() {
  application_state* app = dh_get_app();

  render(app);

  if (dh_get_key_down(app, GLFW_KEY_W)) {
    game_object_translate(app->delta_time, p.game_object, (vec3){0, 1, 0}, speed);
  }
  if (dh_get_key_down(app, GLFW_KEY_S)) {
    game_object_translate(app->delta_time, p.game_object, (vec3){0, -1, 0}, speed);
  }
  if (dh_get_key_down(app, GLFW_KEY_A)) {
    game_object_translate(app->delta_time, p.game_object, (vec3){-1, 0.0, 0}, speed);
  }
  if (dh_get_key_down(app, GLFW_KEY_D)) {
    game_object_translate(app->delta_time, p.game_object, (vec3){1, 0.0, 0}, speed);
  }
}

int main() {
  dh_application_create(start);
  dh_application_run(update, render_gui);
  return 0;
}
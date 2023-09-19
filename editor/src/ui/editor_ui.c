#include "editor_ui.h"

#include <nk_defines.h>

static struct nk_context* ctx;

f32 calculate_percentage(i32 original_size, i32 percentage) {
  return (original_size * percentage) / 100;
}

void dh_editor_update_ui(application_state* app) {
  struct nk_context* ctx = dh_get_nuklear_context();
  f32 percent_width = calculate_percentage(app->width, 20);
  f32 content_width = calculate_percentage(app->width, 60);
  f32 content_height = calculate_percentage(app->height, 30);

  if (nk_begin(ctx, "Hierarchy", nk_rect(0, 0, percent_width, app->height),
               NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
    if (nk_button_label(ctx, "button"))
      fprintf(stdout, "button pressed\n");
  }
  nk_end(ctx);

  if (nk_begin(ctx, "Inspector", nk_rect((f32)app->width - (f32)percent_width, 0, percent_width, app->height),
               NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
    if (nk_button_label(ctx, "button"))
      fprintf(stdout, "button pressed\n");
  }
  nk_end(ctx);

  if (nk_begin(ctx, "Resources", nk_rect(percent_width, (f32)app->height - (f32)content_height, content_width, content_height),
               NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
  }
  nk_end(ctx);

  if (nk_begin(ctx, "Toolbar", nk_rect(percent_width, 0, content_width, 30),
               NK_WINDOW_BORDER)) {
  }
  nk_end(ctx);
}
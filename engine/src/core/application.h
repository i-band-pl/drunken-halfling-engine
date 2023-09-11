#pragma once

#include <stdio.h>

#include "CGLM/cglm.h"
#include "defines.h"
#include "window.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

typedef void (*applcation_invoke)(void);

typedef struct application_state {
  GLFWwindow* platform_window;
  mat4* projection;
  i32 height;
  i32 width;
  f32 delta_time;
} application_state;

DHAPI void dh_application_create(applcation_invoke invoker);
u32 dh_application_init();
DHAPI u32 dh_application_run(applcation_invoke render_invoker, applcation_invoke gui_invoker);

DHAPI void dh_projection_update();
DHAPI void dh_projection_get(mat4* proj);

void dh_application_framebuffer_callback(GLFWwindow* window, int width, int height);

DHAPI application_state* dh_get_app();
DHAPI struct nk_context* dh_get_nuklear_context();
DHAPI struct nk_colorf dh_get_nuklear_bg();
DHAPI i32 dh_get_frames_per_second();

DHAPI u32 dh_test();

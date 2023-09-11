#pragma once

#include <stdio.h>

#include "CGLM/cglm.h"
#include "defines.h"
#include "window.h"

typedef void (*applcation_invoke)(void);

typedef struct application_state {
  GLFWwindow* platform_window;
  mat4* projection;
  i32 height;
  i32 width;
} application_state;

DHAPI void dh_application_create(applcation_invoke invoker);
u32 dh_application_init();
DHAPI application_state* dh_get_app();
DHAPI u32 dh_application_run(applcation_invoke invoker);

DHAPI void dh_projection_update();
DHAPI void dh_projection_get(mat4* proj);

void dh_application_framebuffer_callback(GLFWwindow* window, int width, int height);

DHAPI u32 dh_test();
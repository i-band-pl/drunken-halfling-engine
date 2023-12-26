#pragma once

#include <stdio.h>

#include "CGLM/cglm.h"
#include "core/state_machine.h"
#include "defines.h"
#include "window.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

typedef void (*applcation_invoke)(void);

typedef struct {
  GLFWwindow* platformWindow;
  const char* applicationName;
  mat4* projection;
  i32 height;
  i32 width;
  f32 deltaTime;
  StateMachine stateMachine;

  bool isDebug;
} Application;

DHAPI void dh_application_create(const char* app_name, applcation_invoke invoker);
u32 dh_application_init();
DHAPI u32 dh_application_run(applcation_invoke render_invoker, applcation_invoke gui_invoker);

DHAPI void dh_projection_update();
DHAPI void dh_projection_get(mat4* proj);

void dh_application_framebuffer_callback(GLFWwindow* window, int width, int height);

DHAPI Application* dh_get_app();
DHAPI struct nk_context* dh_get_nuklear_context();
DHAPI struct nk_colorf dh_get_nuklear_bg();
DHAPI i32 dh_get_frames_per_second();

DHAPI u32 dh_test();

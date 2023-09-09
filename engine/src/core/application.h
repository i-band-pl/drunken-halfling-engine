#pragma once

#include <stdio.h>

#include "defines.h"
#include "window.h"

typedef void (*applcation_invoke)(void);

typedef struct application_state {
  GLFWwindow* platform_window;
} application_state;

DHAPI void dh_application_create();
u32 dh_application_init();
DHAPI application_state* dh_get_app();
DHAPI u32 dh_application_run(applcation_invoke invoker);
DHAPI u32 dh_test();
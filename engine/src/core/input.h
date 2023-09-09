#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "application.h"
#include "defines.h"

DHAPI u32 dh_get_key_down(application_state* app_state, int key);
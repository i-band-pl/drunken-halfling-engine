#include "input.h"

u32 dh_get_key_down(application_state* app_state, int key) {
  if (glfwGetKey(app_state->platform_window, key) == GLFW_PRESS) {
    return TRUE;
  }
  return FALSE;
}
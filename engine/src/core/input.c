#include "input.h"

u32 dh_get_key_down(Application* app, int key) {
  if (glfwGetKey(app->platformWindow, key) == GLFW_PRESS) {
    return TRUE;
  }
  return FALSE;
}
#include <application.h>
#include <input.h>
#include <test.h>

void update() {
  application_state* app = dh_get_app();

  if (dh_get_key_down(app, GLFW_KEY_W)) {
    printf("PRESS W \n");
  }
}

int main() {
  dh_application_create();
  dh_application_run(update);
  return 0;
}
#include "application.h"

static application_state app_state;

void dh_application_create() {
  dh_application_init();
  // dh_application_run();
}

u32 dh_application_init() {
  dh_create_window(&app_state.platform_window);
  return 0;
}

u32 dh_application_run(applcation_invoke invoker) {
  printf("RUN \n");
  while (!glfwWindowShouldClose(app_state.platform_window)) {
    // printf("UPDATE \n");
    process_input(app_state.platform_window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(app_state.platform_window);
    glfwPollEvents();

    invoker();
  }

  glfwTerminate();

  return 0;
}

application_state* dh_get_app() {
  return &app_state;
}
#include "application.h"

static application_state app_state;

void dh_application_create(applcation_invoke invoker) {
  dh_application_init();

  invoker();
}

u32 dh_application_init() {
  printf("main init start \n");
  dh_create_window(&app_state.platform_window);
  glfwGetFramebufferSize(app_state.platform_window, &app_state.width, &app_state.height);
  app_state.projection = malloc(sizeof(mat4));
  dh_projection_update();
  printf("main init end \n");
  return 0;
}

u32 dh_application_run(applcation_invoke invoker) {
  while (!glfwWindowShouldClose(app_state.platform_window)) {
    process_input(app_state.platform_window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    invoker();

    glfwSwapBuffers(app_state.platform_window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}

application_state* dh_get_app() {
  return &app_state;
}

void dh_application_framebuffer_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  app_state.height = height;
  app_state.width = width;
  dh_projection_update();
}

void dh_projection_update() {
  glm_perspective(45.0f, (float)app_state.width / (float)app_state.height, 0.1f, 100.0f, *app_state.projection);
}

void dh_projection_get(mat4* proj) {
  proj = app_state.projection;
}
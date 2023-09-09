#include "window.h"

u32 dh_create_window(application_state* app_state) {
  if (!glfwInit()) {
    printf("Failed to Init GLFW \n");
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  app_state->platform_window = glfwCreateWindow(1200, 700, "windowName", NULL, NULL);

  if (app_state->platform_window == NULL) {
    printf("Failed to create GLFW window \n");
    glfwTerminate();
    return -1;
  } else {
    printf("Created GLFW window \n");
  }
  glfwMakeContextCurrent(app_state->platform_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return -1;
  }

  glViewport(0, 0, 1200, 700);

  glfwSetFramebufferSizeCallback(app_state->platform_window, framebuffer_size_callback);

  return 0;
}

void process_input(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    printf("closing \n");
    glfwSetWindowShouldClose(window, TRUE);
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  printf("callback updated \n");
  glViewport(0, 0, width, height);
}
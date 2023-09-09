#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "application.h"
#include "defines.h"

typedef struct window_t {
  GLFWwindow* handle;
} window_t;

u32 dh_create_window();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

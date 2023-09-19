#include "application.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL4_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl4.h"

static application_state app_state;
typedef struct nuklear_data {
  struct nk_context* ctx;
  struct nk_font_atlas* atlas;
  struct nk_colorf bg;
  struct nk_image img;
} nuklear_data;
static nuklear_data nk_data;
f32 last_frame = 0.0f;
i32 frame_count = 0;
f32 last_frame_time = 0.0f;
i32 frame_rate = 0;

void dh_application_create(const char* app_name, applcation_invoke invoker) {
  app_state.application_name = app_name;
  app_state.delta_time = 0.0f;
  dh_application_init();
  last_frame_time = (f32)glfwGetTime();
  invoker();
}

u32 dh_application_init() {
  printf("main init start \n");
  dh_create_window(&app_state.platform_window);
  glfwGetFramebufferSize(app_state.platform_window, &app_state.width, &app_state.height);
  app_state.projection = malloc(sizeof(mat4));
  dh_projection_update();
  nk_data.ctx = nk_glfw3_init(app_state.platform_window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
  // set_style(ctx, THEME_BLACK);
  nk_glfw3_font_stash_begin(&nk_data.atlas);
  nk_glfw3_font_stash_end();
  {
    int tex_index = 0;
    enum { tex_width = 256,
           tex_height = 256 };
    char pixels[tex_width * tex_height * 4];
    memset(pixels, 128, sizeof(pixels));
    tex_index = nk_glfw3_create_texture(pixels, tex_width, tex_height);
    nk_data.img = nk_image_id(tex_index);
  }
  nk_data.bg.r = 0.10f, nk_data.bg.g = 0.18f, nk_data.bg.b = 0.24f, nk_data.bg.a = 1.0f;
  printf("main init end \n");
  return 0;
}

u32 dh_application_run(applcation_invoke render_invoker, applcation_invoke gui_invoker) {
  b8 buff[100];

  glfwMaximizeWindow(app_state.platform_window);

  while (!glfwWindowShouldClose(app_state.platform_window)) {
    f32 current_frame = (f32)glfwGetTime();
    app_state.delta_time = current_frame - last_frame;
    last_frame = current_frame;

    glfwPollEvents();
    nk_glfw3_new_frame();
    gui_invoker();

    process_input(app_state.platform_window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    render_invoker();

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
    glfwSwapBuffers(app_state.platform_window);

    frame_count++;
    if (current_frame - last_frame_time >= 1.0f) {
      frame_rate = frame_count;
      frame_count = 0;
      last_frame_time = current_frame;

      sprintf(buff, "[OpenGL] %s - %d FPS", app_state.application_name, frame_rate);
      glfwSetWindowTitle(app_state.platform_window, buff);
    }
  }

  nk_glfw3_shutdown();
  glfwTerminate();

  return 0;
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

application_state* dh_get_app() {
  return &app_state;
}

struct nk_context* dh_get_nuklear_context() {
  return nk_data.ctx;
}

struct nk_colorf dh_get_nuklear_bg() {
  return nk_data.bg;
}

i32 dh_get_frames_per_second() {
  return frame_rate;
}
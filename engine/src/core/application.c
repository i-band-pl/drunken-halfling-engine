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

static Application app;
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

u32 nuklear_init() {
  nk_data.ctx = nk_glfw3_init(app.platformWindow, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
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
  return 0;
}

void dh_application_create(const char* app_name, applcation_invoke invoker) {
  app.applicationName = app_name;
  app.deltaTime = 0.0f;
  dh_application_init();
  last_frame_time = (f32)glfwGetTime();
  app.isDebug = true;
  invoker();
}

void debug_ui() {
  if (!app.isDebug) return;

  if (nk_begin(
          nk_data.ctx,
          "Debug Window",
          nk_rect(app.width - 400, app.height - 200, 400, 200),
          NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
    nk_text(nk_data.ctx, "Hello World", 11, NK_TEXT_LEFT);
  }
  nk_end(nk_data.ctx);
}

u32 dh_application_init() {
  dh_create_window(&app.platformWindow);
  glfwGetFramebufferSize(app.platformWindow, &app.width, &app.height);

  app.projection = malloc(sizeof(mat4));
  state_machine_init(&app.stateMachine);

  dh_projection_update();

  nuklear_init();
  return 0;
}

void app_update() {
  u32 i = 0;
  for (i = 0; i < app.stateMachine.actorsSize; i++) {
    actor_update(app.projection, &app.stateMachine.actors[i], app.stateMachine.mainCamera);
    // printf("%f %f \n", app.stateMachine.actors[i].position[0], app.stateMachine.actors[i].position[1]);
    // printf("update [%d] [%d] [%d]", i, app.stateMachine.actorsSize, app.stateMachine.actors[i].texture->height);
  }
}

u32 dh_application_run(applcation_invoke render_invoker, applcation_invoke gui_invoker) {
  b8 buff[100];

  glfwMaximizeWindow(app.platformWindow);

  while (!glfwWindowShouldClose(app.platformWindow)) {
    f32 current_frame = (f32)glfwGetTime();
    app.deltaTime = current_frame - last_frame;
    last_frame = current_frame;

    glfwPollEvents();
    nk_glfw3_new_frame();
    gui_invoker();
    debug_ui();

    process_input(app.platformWindow);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    app_update();
    render_invoker();

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
    glfwSwapBuffers(app.platformWindow);

    frame_count++;
    if (current_frame - last_frame_time >= 1.0f) {
      frame_rate = frame_count;
      frame_count = 0;
      last_frame_time = current_frame;

      sprintf(buff, "[OpenGL] %s - %d FPS", app.applicationName, frame_rate);
      glfwSetWindowTitle(app.platformWindow, buff);
    }
  }

  nk_glfw3_shutdown();
  glfwTerminate();

  return 0;
}

void dh_application_framebuffer_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  app.height = height;
  app.width = width;
  dh_projection_update();
}

void dh_projection_update() {
  glm_perspective(45.0f, (float)app.width / (float)app.height, 0.1f, 100.0f, *app.projection);
}

void dh_projection_get(mat4* proj) {
  proj = app.projection;
}

Application* dh_get_app() {
  return &app;
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
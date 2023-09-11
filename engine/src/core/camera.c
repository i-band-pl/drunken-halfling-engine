#include "camera.h"

void dh_camera_init(camera* camera) {
  camera->camera_position[0] = 0.0f;
  camera->camera_position[1] = 0.0f;
  camera->camera_position[2] = 0.0f;
  camera->camera_front[0] = 0.0f;
  camera->camera_front[1] = 0.0f;
  camera->camera_front[2] = 0.0f;
  camera->camera_up[0] = 0.0f;
  camera->camera_up[1] = 0.0f;
  camera->camera_up[2] = 0.0f;

  camera->last_x = 800.0f / 2.0f;
  camera->last_y = 600.0f / 2.0f;
  camera->yaw = -90.0f;
  camera->pitch = 0.0f;
  camera->fov = 45.0f;
}

void dh_camera_translate_pos(camera* camera, vec3 dest) {
  camera->camera_position[0] += dest[0];
  camera->camera_position[1] += dest[1];
  camera->camera_position[2] += dest[2];
}

void dh_camera_translate_pos_by_speed(camera* camera, vec3 dest, float speed) {
  camera->camera_position[0] += (dest[0] * speed);
  camera->camera_position[1] += (dest[1] * speed);
  camera->camera_position[2] += (dest[2] * speed);
}

void dh_camera_translate_normalized(camera* camera, float speed) {
  vec3 direction = GLM_VEC3_ZERO_INIT;
  glm_vec3_cross(camera->camera_front, camera->camera_up, direction);
  glm_vec3_normalize(direction);
  camera->camera_position[0] += (direction[0] * speed);
  camera->camera_position[1] += (direction[1] * speed);
  camera->camera_position[2] += (direction[2] * speed);
}

void dh_camera_translate_front(camera* camera, vec3 dest) {
  camera->camera_front[0] += dest[0];
  camera->camera_front[1] += dest[1];
  camera->camera_front[2] += dest[2];
}

void dh_camera_translate_up(camera* camera, vec3 dest) {
  camera->camera_up[0] += dest[0];
  camera->camera_up[1] += dest[1];
  camera->camera_up[2] += dest[2];
}

void dh_camera_multiply_pos(camera* camera, float value) {
  camera->camera_position[0] *= value;
  camera->camera_position[1] *= value;
  camera->camera_position[2] *= value;
}

void dh_camera_multiply_vec3_float_pos(camera* camera, vec3 vector, float value) {
  camera->camera_position[0] = vector[0] * value;
  camera->camera_position[1] = vector[1] * value;
  camera->camera_position[2] = vector[2] * value;
}

void dh_camera_get_view_matrix(camera* camera, shader* shader, mat4* view) {
  glm_mat4_identity(*view);
  glm_vec3_add(camera->camera_position, camera->camera_front, camera->camera_front_offset);
  glm_lookat(camera->camera_position, camera->camera_front_offset, camera->camera_up, *view);
}
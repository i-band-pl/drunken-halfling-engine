#pragma once

#include "CGLM/cglm.h"
#include "CGLM/struct.h"
#include "GL/shader.h"
#include "defines.h"
#include "glad.h"

typedef struct {
  vec3 camera_position;
  vec3 camera_front;
  vec3 camera_up;
  vec3 camera_front_offset;
  f32 yaw;
  f32 pitch;
  f32 last_x;
  f32 last_y;
  f32 fov;
} Camera;

DHAPI void dh_camera_init(Camera* camera);
DHAPI void dh_camera_translate_pos(Camera* camera, vec3 dest);
DHAPI void dh_camera_translate_pos_by_speed(Camera* camera, vec3 dest, float speed);
DHAPI void dh_camera_translate_normalized(Camera* camera, float speed);
DHAPI void dh_camera_translate_front(Camera* camera, vec3 dest);
DHAPI void dh_camera_translate_up(Camera* camera, vec3 dest);
DHAPI void dh_camera_multiply_pos(Camera* camera, float value);
DHAPI void dh_camera_multiply_vec3_float_pos(Camera* camera, vec3 vector, float value);
DHAPI void dh_camera_get_view_matrix(Camera* camera, shader* shader, mat4* view);

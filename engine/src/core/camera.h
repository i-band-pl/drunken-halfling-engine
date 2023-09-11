#pragma once

#include "CGLM/cglm.h"
#include "CGLM/struct.h"
#include "GL/shader.h"
#include "defines.h"
#include "glad.h"

typedef struct camera {
  vec3 camera_position;
  vec3 camera_front;
  vec3 camera_up;
  vec3 camera_front_offset;
  f32 yaw;
  f32 pitch;
  f32 last_x;
  f32 last_y;
  f32 fov;
} camera;

DHAPI void dh_camera_init(camera* camera);
DHAPI void dh_camera_translate_pos(camera* camera, vec3 dest);
DHAPI void dh_camera_translate_pos_by_speed(camera* camera, vec3 dest, float speed);
DHAPI void dh_camera_translate_normalized(camera* camera, float speed);
DHAPI void dh_camera_translate_front(camera* camera, vec3 dest);
DHAPI void dh_camera_translate_up(camera* camera, vec3 dest);
DHAPI void dh_camera_multiply_pos(camera* camera, float value);
DHAPI void dh_camera_multiply_vec3_float_pos(camera* camera, vec3 vector, float value);
DHAPI void dh_camera_get_view_matrix(camera* camera, shader* shader, mat4* view);

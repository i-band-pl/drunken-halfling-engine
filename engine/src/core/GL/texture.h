#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "glad.h"

#define TEXTURES_PATH "./textures/"

typedef struct texture {
  i32 width;
  i32 height;
  i32 channels_count;
  b8 filename[512];
  u32 id;
  // u8* texture_data;
} texture;

DHAPI void dh_texture_load(texture* texture);
DHAPI void dh_texture_use(texture* texture);
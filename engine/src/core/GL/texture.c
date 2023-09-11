#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"
void dh_texture_load(texture* texture) {
  glGenTextures(1, &texture->id);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  b8 path[512];
  strcpy(path, TEXTURES_PATH);
  strcat(path, texture->filename);

  stbi_set_flip_vertically_on_load(TRUE);
  unsigned char* texture_data = stbi_load(path, &texture->width, &texture->height, &texture->channels_count, 0);
  if (texture_data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    printf("failed to load texture \n");
  }
  stbi_image_free(texture_data);
  // texture->texture_data = texture_data;
}

void dh_texture_use(texture* texture) {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->id);
}
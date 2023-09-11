#include "sprite.h"

void dh_sprite_init(sprite* sprite) {
  sprite->vertices_count = 6;
  sprite->buffer_size = sizeof(vertex) * sprite->vertices_count;
  sprite->vertices = malloc(sprite->buffer_size);

  sprite->vertices[0].position[0] = 0.0f;
  sprite->vertices[0].position[1] = 1.0f;
  sprite->vertices[0].position[2] = 0.0f;
  sprite->vertices[0].texture_coords[0] = 0.0f;
  sprite->vertices[0].texture_coords[1] = 1.0f;

  sprite->vertices[1].position[0] = 1.0f;
  sprite->vertices[1].position[1] = 0.0f;
  sprite->vertices[1].position[2] = 0.0f;
  sprite->vertices[1].texture_coords[0] = 1.0f;
  sprite->vertices[1].texture_coords[1] = 0.0f;

  sprite->vertices[2].position[0] = 0.0f;
  sprite->vertices[2].position[1] = 0.0f;
  sprite->vertices[2].position[2] = 0.0f;
  sprite->vertices[2].texture_coords[0] = 0.0f;
  sprite->vertices[2].texture_coords[1] = 0.0f;

  sprite->vertices[3].position[0] = 0.0f;
  sprite->vertices[3].position[1] = 1.0f;
  sprite->vertices[3].position[2] = 0.0f;
  sprite->vertices[3].texture_coords[0] = 0.0f;
  sprite->vertices[3].texture_coords[1] = 1.0f;

  sprite->vertices[4].position[0] = 1.0f;
  sprite->vertices[4].position[1] = 1.0f;
  sprite->vertices[4].position[2] = 0.0f;
  sprite->vertices[4].texture_coords[0] = 1.0f;
  sprite->vertices[4].texture_coords[1] = 1.0f;

  sprite->vertices[5].position[0] = 1.0f;
  sprite->vertices[5].position[1] = 0.0f;
  sprite->vertices[5].position[2] = 0.0f;
  sprite->vertices[5].texture_coords[0] = 1.0f;
  sprite->vertices[5].texture_coords[1] = 0.0f;

  sprite->color[0] = 1.0f;
  sprite->color[1] = 1.0f;
  sprite->color[2] = 1.0f;

  sprite->scale[0] = 1.0f;
  sprite->scale[1] = 1.0f;
  sprite->scale[2] = 1.0f;

  glGenVertexArrays(1, &sprite->vao);
  glBindVertexArray(sprite->vao);

  glGenBuffers(1, &sprite->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, sprite->vbo);
  glBufferData(GL_ARRAY_BUFFER, sprite->buffer_size, &sprite->vertices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texture_coords));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void dh_sprite_bind(sprite* sprite) {
  if (sprite == NULL) {
    glBindVertexArray(0);
  } else {
    glBindVertexArray(sprite->vao);
  }
}

void dh_sprite_render(sprite* sprite) {
  glDrawArrays(GL_TRIANGLES, 0, sprite->vertices_count);
  glBindVertexArray(0);
}
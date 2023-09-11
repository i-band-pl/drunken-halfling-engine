#include "reader.h"

#include <stdio.h>
#include <stdlib.h>

b8* dh_reader_read_data(b8* path) {
  b8* buffer = NULL;
  int stringSize, readSize;
  FILE* file = fopen(path, "r");

  if (file) {
    fseek(file, 0, SEEK_END);
    stringSize = ftell(file);
    rewind(file);
    buffer = (char*)malloc(sizeof(char) * (stringSize + 1));
    readSize = fread(buffer, sizeof(char), stringSize, file);
    buffer[stringSize] = '\0';

    if (stringSize != readSize) {
      free(buffer);
      buffer = NULL;
    }

    fclose(file);
  }

  return buffer;
}
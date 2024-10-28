#ifndef TEXTURE_H
#define TEXTURE_H

#include "vector.h"

// Texture structure with width, height, and color data
typedef struct {
    int width;
    int height;
    Vector3 *data;  // Array storing color data in RGB format
} Texture;

// Functions for texture management
Texture load_texture(const char *filename);
Vector3 get_texture_color(Texture *texture, float u, float v);
void free_texture(Texture *texture);

#endif // TEXTURE_H

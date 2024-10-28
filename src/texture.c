#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 
#include <math.h>

// Load a texture from a PPM file
Texture load_texture(const char *filename) {
    Texture texture;
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open texture file %s\n", filename);
        texture.width = texture.height = 0;
        texture.data = NULL;
        return texture;
    }

    // Read PPM header
    char format[3];
    fscanf(file, "%2s", format);
    if (format[0] != 'P' || format[1] != '3') {
        fprintf(stderr, "Error: Unsupported PPM format in file %s\n", filename);
        fclose(file);
        texture.width = texture.height = 0;
        texture.data = NULL;
        return texture;
    }

    // Read image dimensions and maximum color value
    int max_color;
    fscanf(file, "%d %d %d", &texture.width, &texture.height, &max_color);

    // Allocate memory for the texture data
    texture.data = malloc(sizeof(Vector3) * texture.width * texture.height);
    if (!texture.data) {
        fprintf(stderr, "Error: Unable to allocate memory for texture %s\n", filename);
        fclose(file);
        texture.width = texture.height = 0;
        return texture;
    }

    // Read pixel data
    for (int i = 0; i < texture.width * texture.height; i++) {
        int r, g, b;
        fscanf(file, "%d %d %d", &r, &g, &b);
        texture.data[i] = (Vector3){
            r / (float)max_color,
            g / (float)max_color,
            b / (float)max_color
        };
    }

    fclose(file);
    printf("Loaded texture from %s\n", filename);
    return texture;
}

// Sample the color from a texture using UV coordinates
Vector3 get_texture_color(Texture *texture, float u, float v) {
    if (!texture->data) {
        return (Vector3){1.0f, 1.0f, 1.0f};  // Return white if no texture data
    }

    // Clamp UV coordinates to [0, 1] range
    u = fmod(u, 1.0f);
    v = fmod(v, 1.0f);
    if (u < 0) u += 1.0f;
    if (v < 0) v += 1.0f;

    // Convert UV to pixel coordinates
    int x = (int)(u * texture->width);
    int y = (int)((1.0f - v) * texture->height);  // Flip v for correct orientation

    // Ensure coordinates are within bounds
    x = x % texture->width;
    y = y % texture->height;

    return texture->data[y * texture->width + x];
}

// Free the memory used by the texture
void free_texture(Texture *texture) {
    if (texture->data) {
        free(texture->data);
        texture->data = NULL;
    }
    texture->width = texture->height = 0;
}

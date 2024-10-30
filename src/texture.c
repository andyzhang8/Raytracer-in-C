#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION  // This line is needed to define the implementation
#include "stb_image.h"            // Include stb_image.h after the definition
#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Load a texture from a JPG file
Texture load_texture(const char *filename) {
    Texture texture;
    int channels;

    // Use stb_image to load JPG data
    texture.data = (Vector3 *)stbi_load(filename, &texture.width, &texture.height, &channels, 3);
    if (!texture.data) {
        fprintf(stderr, "Error: Unable to load texture file %s\n", filename);
        texture.width = texture.height = 0;
        return texture;
    }

    // Print success message
    printf("Loaded texture from %s (Width: %d, Height: %d, Channels: %d)\n", filename, texture.width, texture.height, channels);

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

    // Retrieve the RGB values and normalize to [0, 1]
    unsigned char *pixel = (unsigned char *)texture->data + (y * texture->width + x) * 3;
    return (Vector3){
        pixel[0] / 255.0f,
        pixel[1] / 255.0f,
        pixel[2] / 255.0f
    };
}

// Free the memory used by the texture
void free_texture(Texture *texture) {
    if (texture->data) {
        stbi_image_free(texture->data);
        texture->data = NULL;
    }
    texture->width = texture->height = 0;
}

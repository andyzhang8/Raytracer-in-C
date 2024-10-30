#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "texture.h"

// Material structure containing properties for shading and light interaction
typedef struct {
    Vector3 color;
    float diffuse;
    float specular;
    float reflectivity;
    float refractivity;
    float ior;
    float shininess;         // Re-add shininess for specular reflection
    int has_texture;         // Field to indicate if material has a texture
    Texture *texture;        // Pointer to texture data
    int tex_width, tex_height, tex_channels; // Texture dimensions
} Material;

// Functions for creating and managing materials
Material create_material(Vector3 color, float reflectivity, float refractivity, float ior, float shininess);
void set_texture(Material *material, Texture *texture);

#endif // MATERIAL_H

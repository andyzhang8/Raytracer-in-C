#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "texture.h"

// Material structure containing properties for shading and light interaction
typedef struct {
    Vector3 color;       // Base color of the material
    float diffuse;       // Diffuse reflection coefficient (controls the diffuse shading intensity)
    float specular;      // Specular reflection coefficient (controls the specular highlight intensity)
    float reflectivity;  // Reflectivity factor (0 to 1), where 1 is a perfect mirror
    float refractivity;  // Refractivity factor (0 to 1), where 1 is fully transparent
    float ior;           // Index of Refraction (IOR) for transparent materials (e.g., glass, water)
    float shininess;     // Shininess factor for specular highlights (higher values = sharper reflections)
    Texture *texture;    // Pointer to a texture, if the material has one
} Material;

// Functions for creating and managing materials
Material create_material(Vector3 color, float reflectivity, float refractivity, float ior, float shininess);
void set_texture(Material *material, Texture *texture);

#endif // MATERIAL_H

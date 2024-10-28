#include "material.h"
#include <stdlib.h>

// Create a new material with specified properties
Material create_material(Vector3 color, float reflectivity, float refractivity, float ior, float shininess) {
    Material material;
    material.color = color;
    material.diffuse = 0.8f;      // Default diffuse value
    material.specular = 0.5f;     // Default specular value
    material.reflectivity = reflectivity;
    material.refractivity = refractivity;
    material.ior = ior;
    material.shininess = shininess;
    material.texture = NULL;      // No texture assigned by default
    return material;
}

// Set a texture for the material
void set_texture(Material *material, Texture *texture) {
    material->texture = texture;
}

#include "material.h"
#include <stdlib.h>
#include <stdio.h> // For fprintf and stderr

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
    material.has_texture = 0;
    material.tex_width = material.tex_height = material.tex_channels = 0;
    return material;
}

// Load a texture into the material
int material_load_texture(Material *material, const char *file_path) {
    material->texture = malloc(sizeof(Texture));
    if (!material->texture) {
        fprintf(stderr, "Error: Unable to allocate memory for texture\n");
        return 0;
    }

    // Load texture data from file
    *(material->texture) = load_texture(file_path);
    material->has_texture = (material->texture->data != NULL);
    if (material->has_texture) {
        material->tex_width = material->texture->width;
        material->tex_height = material->texture->height;
        material->tex_channels = 3; // Assume RGB for now
    } else {
        free(material->texture);
        material->texture = NULL;
    }
    return material->has_texture;
}

// Free material's texture if it exists
void free_material(Material *material) {
    if (material->has_texture && material->texture) {
        free_texture(material->texture);
        free(material->texture);
        material->texture = NULL;
        material->has_texture = 0;
    }
}

// Set a texture for the material
void set_texture(Material *material, Texture *texture) {
    material->texture = texture;
    material->has_texture = (texture != NULL);
    if (material->texture) {
        material->tex_width = texture->width;
        material->tex_height = texture->height;
    }
}

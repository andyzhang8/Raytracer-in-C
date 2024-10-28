#ifndef LIGHTING_H
#define LIGHTING_H

#include "types.h"   // Consolidated types
#include "vector.h"
#include "material.h"

typedef struct {
    Vector3 color;
    float intensity;
} AmbientLight;

typedef struct {
    Vector3 position;
    Vector3 color;
    float intensity;
} PointLight;

typedef struct {
    Vector3 direction;
    Vector3 color;
    float intensity;
} DirectionalLight;

// Use `struct Scene` explicitly in function declarations
Vector3 calculate_ambient_light(AmbientLight ambient, Material *material);
Vector3 calculate_point_light(PointLight point_light, Vector3 hit_point, Vector3 normal, Vector3 view_dir, Material *material, struct Scene *scene);
Vector3 calculate_directional_light(DirectionalLight dir_light, Vector3 hit_point, Vector3 normal, Vector3 view_dir, Material *material, struct Scene *scene);
Vector3 calculate_lighting(struct Scene *scene, struct HitInfo *hit, Ray view_ray);

#endif // LIGHTING_H

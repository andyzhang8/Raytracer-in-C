#include "object.h"  // Ensure struct HitInfo is recognized
#include "scene.h"   // Ensure struct Scene visibility
#include "lighting.h"
#include "raytracer.h"
#include "utils.h"
#define _USE_MATH_DEFINES 
#include <math.h>  // For atan2, asin, and M_PI

// Forward declaration for get_uv_coordinates
void get_uv_coordinates(struct HitInfo hit, float *u, float *v);

// Trace a ray into the scene and return the color at the intersection point
Vector3 trace_ray(struct Scene *scene, Ray ray, int depth) {
    if (depth <= 0) {
        return (Vector3){0, 0, 0};  // Return black if max recursion depth reached
    }

    // Find the nearest object intersection
    struct HitInfo hit;
    if (!find_nearest_object(scene, ray, &hit)) {
        return scene->background_color;  // Background color if no intersection
    }

    // Calculate the color at the hit point
    return calculate_color(scene, hit, ray, depth);
}

// Calculate lighting, reflections, and refractions at the hit point
Vector3 calculate_color(struct Scene *scene, struct HitInfo hit, Ray view_ray, int depth) {
    Material material = hit.object->material;
    Vector3 color = {0, 0, 0};

    // Apply texture mapping if the material has a texture
    if (material.texture) {
        float u, v;
        get_uv_coordinates(hit, &u, &v);  // Calculate UV coordinates based on hit location
        color = get_texture_color(material.texture, u, v);
    } else {
        color = material.color;
    }

    // Calculate lighting based on ambient, point, and directional lights
    Vector3 lighting = calculate_lighting(scene, &hit, view_ray);
    color = vector_mult(color, lighting);  // Apply lighting to base color

    // Reflection handling
    if (material.reflectivity > 0) {
        Vector3 reflect_dir = reflect(view_ray.direction, hit.normal);
        Ray reflect_ray = {hit.point, reflect_dir};
        Vector3 reflection_color = trace_ray(scene, reflect_ray, depth - 1);
        color = vector_add(color, vector_scale(reflection_color, material.reflectivity));
    }

    // Refraction handling
    if (material.refractivity > 0) {
        Vector3 refract_dir = refract(view_ray.direction, hit.normal, material.ior);
        Ray refract_ray = {hit.point, refract_dir};
        Vector3 refraction_color = trace_ray(scene, refract_ray, depth - 1);
        color = vector_add(color, vector_scale(refraction_color, material.refractivity));
    }

    return color;
}

// Get UV coordinates for texture mapping
void get_uv_coordinates(struct HitInfo hit, float *u, float *v) {
    // Example UV mapping for a sphere
    Vector3 hit_point = vector_sub(hit.point, hit.object->center);
    *u = 0.5 + (atan2(hit_point.z, hit_point.x) / (2 * M_PI));
    *v = 0.5 - (asin(hit_point.y / hit.object->radius) / M_PI);
}

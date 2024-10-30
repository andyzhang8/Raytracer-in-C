#include "object.h"
#include "scene.h"
#include "lighting.h"
#include "raytracer.h"
#include "utils.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h> // For rand() in glossy reflection

#define MAX_SAMPLES 32       // Increase number of samples for glossy reflections to smoothen
#define MAX_DEPTH 15        // Increase max recursion depth for more light bounces
#define BIAS 1e-2           // Small bias to avoid self-intersection


// Forward declaration for get_uv_coordinates
void get_uv_coordinates(struct HitInfo hit, float *u, float *v);

// Helper function to add slight random jitter to a vector (for glossy reflections)
Vector3 add_jitter(Vector3 direction, float jitter_amount) {
    return vector_normalize((Vector3){
        direction.x + random_float() * jitter_amount,
        direction.y + random_float() * jitter_amount,
        direction.z + random_float() * jitter_amount
    });
}

// Traces a ray into the scene and returns the color at the intersection point
Vector3 trace_ray(struct Scene *scene, Ray ray, int depth) {
    if (depth <= 0) {
        return (Vector3){0, 0, 0};
    }

    struct HitInfo hit;
    if (!find_nearest_object(scene, ray, &hit)) {
        return scene->background_color;
    }

    return calculate_color(scene, hit, ray, depth);
}

// Calculates color at the hit point, considering textures, lighting, and reflections
Vector3 calculate_color(struct Scene *scene, struct HitInfo hit, Ray view_ray, int depth) {
    Material *material = NULL;

    // Determine material based on object type
    if (hit.object_type == OBJECT_SPHERE) {
        Sphere *sphere = (Sphere *)hit.object;
        material = &sphere->material;
    } else if (hit.object_type == OBJECT_PLANE) {
        Plane *plane = (Plane *)hit.object;
        material = &plane->material;
    }

    // Check if material is valid
    if (material == NULL) {
        fprintf(stderr, "Error: Material is NULL in calculate_color.\n");
        return (Vector3){0, 0, 0};
    }

    Vector3 color = {0, 0, 0};

    // Apply texture mapping if the material has a texture
    if (material->has_texture) {
        float u, v;
        get_uv_coordinates(hit, &u, &v);
        color = get_texture_color(material->texture, u, v);  // Retrieve texture color based on UV
    } else {
        color = material->color;  // Default to base color if no texture
    }

    // Calculate lighting based on ambient, point, and directional lights
    Vector3 lighting = calculate_lighting(scene, &hit, view_ray);
    color = vector_mult(color, lighting);

    // Reflection handling with glossy reflection (using jitter)
    if (material->reflectivity > 0) {
        Vector3 reflect_dir = reflect(view_ray.direction, hit.normal);
        Vector3 reflection_color = {0, 0, 0};
        float jitter_amount = 0.05f;  // Adjust for more/less glossiness

        // Offset the reflection origin to avoid self-intersection
        Vector3 reflect_origin = vector_add(hit.point, vector_scale(hit.normal, BIAS));

        // Average multiple samples for glossy reflections
        for (int i = 0; i < MAX_SAMPLES; i++) {
            Vector3 jittered_reflect_dir = add_jitter(reflect_dir, jitter_amount);
            Ray reflect_ray = {reflect_origin, jittered_reflect_dir};
            reflection_color = vector_add(reflection_color, trace_ray(scene, reflect_ray, depth - 1));
        }
        reflection_color = vector_scale(reflection_color, 1.0f / MAX_SAMPLES);  // Average the samples
        color = vector_add(color, vector_scale(reflection_color, material->reflectivity));
    }

    // Refraction handling with bias
    if (material->refractivity > 0) {
        Vector3 refract_dir = refract(view_ray.direction, hit.normal, material->ior);

        // Offset the refraction origin to avoid self-intersection
        Vector3 refract_origin = vector_add(hit.point, vector_scale(hit.normal, -BIAS));
        
        Ray refract_ray = {refract_origin, refract_dir};
        Vector3 refraction_color = trace_ray(scene, refract_ray, depth - 1);
        color = vector_add(color, vector_scale(refraction_color, material->refractivity));
    }

    return color;
}

// Calculates UV coordinates for texture mapping
void get_uv_coordinates(struct HitInfo hit, float *u, float *v) {
    if (hit.object == NULL) {
        fprintf(stderr, "Error: hit.object is NULL in get_uv_coordinates.\n");
        *u = *v = 0.0f;
        return;
    }

    if (hit.object_type == OBJECT_SPHERE) {
        Sphere *sphere = (Sphere *)hit.object;
        Vector3 hit_point = vector_sub(hit.point, sphere->center);
        *u = 0.5 + (atan2(hit_point.z, hit_point.x) / (2 * M_PI));
        *v = 0.5 - (asin(hit_point.y / sphere->radius) / M_PI);
    } else if (hit.object_type == OBJECT_PLANE) {
        *u = fmodf(hit.point.x, 1.0f);  // Simple planar mapping with wrap-around
        *v = fmodf(hit.point.z, 1.0f);  // Simple planar mapping with wrap-around
    }
}

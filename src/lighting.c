#include "lighting.h"
#include "vector.h"
#include "scene.h"       // Ensure struct Scene visibility
#include "object.h"      // For find_nearest_object
#include "raytracer.h"
#define _USE_MATH_DEFINES 
#include <math.h>        // For fmax, pow, and INFINITY
#include <stddef.h>

// Constants for light attenuation
#define CONSTANT_ATTENUATION 1.0f
#define LINEAR_ATTENUATION 0.09f
#define QUADRATIC_ATTENUATION 0.032f
#define SHADOW_BIAS 1e-4f // Small bias to avoid shadow acné

// Forward declaration for is_in_shadow
int is_in_shadow(struct Scene *scene, Ray shadow_ray, float max_distance);

// Ambient light calculation
Vector3 calculate_ambient_light(AmbientLight ambient, Material *material) {
    return vector_scale(material->color, ambient.intensity);
}

// Point light calculation with attenuation
Vector3 calculate_point_light(PointLight point_light, Vector3 hit_point, Vector3 normal, Vector3 view_dir, Material *material, struct Scene *scene) {
    Vector3 light_dir = vector_normalize(vector_sub(point_light.position, hit_point));
    float distance = vector_length(vector_sub(point_light.position, hit_point));
    
    // Calculate attenuation based on the inverse-square law
    float attenuation = 1.0f / (CONSTANT_ATTENUATION + LINEAR_ATTENUATION * distance + QUADRATIC_ATTENUATION * distance * distance);

    // Offset hit_point along the normal to avoid shadow acné
    Vector3 shadow_origin = vector_add(hit_point, vector_scale(normal, SHADOW_BIAS));
    Ray shadow_ray = {shadow_origin, light_dir};

    // Shadow check
    if (is_in_shadow(scene, shadow_ray, distance)) {
        return (Vector3){0, 0, 0};
    }

    // Lambertian diffuse shading
    float diff = fmax(0.0f, vector_dot(normal, light_dir));
    Vector3 diffuse = vector_scale(vector_mult(material->color, point_light.color), material->diffuse * diff * point_light.intensity * attenuation);

    // Phong specular shading
    Vector3 reflect_dir = reflect(vector_scale(light_dir, -1), normal);
    float spec = pow(fmax(vector_dot(view_dir, reflect_dir), 0.0f), material->shininess);
    Vector3 specular = vector_scale(point_light.color, material->specular * spec * point_light.intensity * attenuation);

    // Combine diffuse and specular components
    return vector_add(diffuse, specular);
}

// Directional light calculation without attenuation
Vector3 calculate_directional_light(DirectionalLight dir_light, Vector3 hit_point, Vector3 normal, Vector3 view_dir, Material *material, struct Scene *scene) {
    Vector3 light_dir = vector_normalize(vector_scale(dir_light.direction, -1));

    // Offset hit_point along the normal to avoid shadow acné
    Vector3 shadow_origin = vector_add(hit_point, vector_scale(normal, SHADOW_BIAS));
    Ray shadow_ray = {shadow_origin, light_dir};

    // Shadow check
    if (is_in_shadow(scene, shadow_ray, INFINITY)) {
        return (Vector3){0, 0, 0};
    }

    // Lambertian diffuse shading
    float diff = fmax(0.0f, vector_dot(normal, light_dir));
    Vector3 diffuse = vector_scale(vector_mult(material->color, dir_light.color), material->diffuse * diff * dir_light.intensity);

    // Phong specular shading
    Vector3 reflect_dir = reflect(vector_scale(light_dir, -1), normal);
    float spec = pow(fmax(vector_dot(view_dir, reflect_dir), 0.0f), material->shininess);
    Vector3 specular = vector_scale(dir_light.color, material->specular * spec * dir_light.intensity);

    // Combine diffuse and specular components
    return vector_add(diffuse, specular);
}

// Check if a point is in shadow
int is_in_shadow(struct Scene *scene, Ray shadow_ray, float max_distance) {
    struct HitInfo shadow_hit;
    if (find_nearest_object(scene, shadow_ray, &shadow_hit) && shadow_hit.t < max_distance) {
        return 1;
    }
    return 0;
}

// Main lighting calculation function
Vector3 calculate_lighting(struct Scene *scene, struct HitInfo *hit, Ray view_ray) {
    Vector3 color = {0, 0, 0};
    Material *material = NULL;

    // Determine the material based on the type of the hit object
    if (hit->object_type == OBJECT_SPHERE) {
        Sphere *sphere = (Sphere *)hit->object;
        material = &sphere->material;
    } else if (hit->object_type == OBJECT_PLANE) {
        Plane *plane = (Plane *)hit->object;
        material = &plane->material;
    }

    // Ambient light calculation
    if (material != NULL) {
        color = vector_add(color, calculate_ambient_light(scene->ambient_light, material));
    }

    // Point lights calculation with attenuation
    for (int i = 0; i < scene->point_light_count; i++) {
        color = vector_add(color, calculate_point_light(scene->point_lights[i], hit->point, hit->normal, vector_scale(view_ray.direction, -1), material, scene));
    }

    // Directional lights calculation without attenuation
    for (int i = 0; i < scene->directional_light_count; i++) {
        color = vector_add(color, calculate_directional_light(scene->directional_lights[i], hit->point, hit->normal, vector_scale(view_ray.direction, -1), material, scene));
    }

    return color;
}

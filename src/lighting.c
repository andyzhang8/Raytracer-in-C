#include "lighting.h"
#include "vector.h"
#include "scene.h"       // Ensure struct Scene visibility
#include "object.h"      // For find_nearest_object
#include "raytracer.h"
#include <math.h>        // For fmax, pow, and INFINITY

// Forward declaration for is_in_shadow
int is_in_shadow(struct Scene *scene, Ray shadow_ray, float max_distance);

// Ambient light calculation
Vector3 calculate_ambient_light(AmbientLight ambient, Material *material) {
    return vector_scale(material->color, ambient.intensity);
}

// Point light calculation
Vector3 calculate_point_light(PointLight point_light, Vector3 hit_point, Vector3 normal, Vector3 view_dir, Material *material, struct Scene *scene) {
    Vector3 light_dir = vector_normalize(vector_sub(point_light.position, hit_point));
    float distance = vector_length(vector_sub(point_light.position, hit_point));

    // Shadow check
    Ray shadow_ray = {hit_point, light_dir};
    if (is_in_shadow(scene, shadow_ray, distance)) {
        return (Vector3){0, 0, 0};
    }

    // Diffuse shading
    float diff = fmax(0.0f, vector_dot(normal, light_dir));
    Vector3 diffuse = vector_scale(material->color, material->diffuse * diff * point_light.intensity);

    // Specular shading
    Vector3 reflect_dir = reflect(vector_scale(light_dir, -1), normal);
    float spec = pow(fmax(vector_dot(view_dir, reflect_dir), 0.0f), material->shininess);
    Vector3 specular = vector_scale(point_light.color, material->specular * spec * point_light.intensity);

    return vector_add(diffuse, specular);
}

// Directional light calculation
Vector3 calculate_directional_light(DirectionalLight dir_light, Vector3 hit_point, Vector3 normal, Vector3 view_dir, Material *material, struct Scene *scene) {
    Vector3 light_dir = vector_normalize(vector_scale(dir_light.direction, -1));

    // Shadow check
    Ray shadow_ray = {hit_point, light_dir};
    if (is_in_shadow(scene, shadow_ray, INFINITY)) {
        return (Vector3){0, 0, 0};
    }

    // Diffuse shading
    float diff = fmax(0.0f, vector_dot(normal, light_dir));
    Vector3 diffuse = vector_scale(material->color, material->diffuse * diff * dir_light.intensity);

    // Specular shading
    Vector3 reflect_dir = reflect(vector_scale(light_dir, -1), normal);
    float spec = pow(fmax(vector_dot(view_dir, reflect_dir), 0.0f), material->shininess);
    Vector3 specular = vector_scale(dir_light.color, material->specular * spec * dir_light.intensity);

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

// Calculate overall lighting
Vector3 calculate_lighting(struct Scene *scene, struct HitInfo *hit, Ray view_ray) {
    Vector3 color = {0, 0, 0};
    color = vector_add(color, calculate_ambient_light(scene->ambient_light, &hit->object->material));

    for (int i = 0; i < scene->point_light_count; i++) {
        color = vector_add(color, calculate_point_light(scene->point_lights[i], hit->point, hit->normal, vector_scale(view_ray.direction, -1), &hit->object->material, scene));
    }

    for (int i = 0; i < scene->directional_light_count; i++) {
        color = vector_add(color, calculate_directional_light(scene->directional_lights[i], hit->point, hit->normal, vector_scale(view_ray.direction, -1), &hit->object->material, scene));
    }

    return color;
} 
#include "object.h"
#include "scene.h"   // Ensure struct Scene is visible
#include "vector.h"
#include "ray.h"
#include <math.h>     // For sqrtf

// Sphere intersection function
int intersect_ray_sphere(Ray ray, Sphere sphere, float *t) {
    Vector3 oc = vector_sub(ray.origin, sphere.center);
    float a = vector_dot(ray.direction, ray.direction);
    float b = 2.0f * vector_dot(oc, ray.direction);
    float c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return 0;  // No intersection
    } else {
        float sqrt_discriminant = sqrtf(discriminant);
        float t0 = (-b - sqrt_discriminant) / (2.0f * a);
        float t1 = (-b + sqrt_discriminant) / (2.0f * a);

        // Choose the smallest positive t
        if (t0 > 0 && t1 > 0) {
            *t = (t0 < t1) ? t0 : t1;
        } else if (t0 > 0) {
            *t = t0;
        } else if (t1 > 0) {
            *t = t1;
        } else {
            return 0;  // Both intersections are behind the ray
        }
        return 1;  // Intersection found
    }
}


// Find the nearest object function
int find_nearest_object(struct Scene *scene, Ray ray, struct HitInfo *hit) {
    int found = 0;
    float closest_t = INFINITY;

    for (int i = 0; i < scene->objects.sphere_count; i++) {
        float t;

        // Check if the ray intersects this sphere
        if (intersect_ray_sphere(ray, scene->objects.spheres[i], &t)) {
            if (t < closest_t) {
                closest_t = t;
                hit->t = t;
                hit->point = vector_add(ray.origin, vector_scale(ray.direction, t));
                hit->normal = vector_normalize(vector_sub(hit->point, scene->objects.spheres[i].center));
                hit->object = &scene->objects.spheres[i];  // Assign directly from the scene
                found = 1;
            }
        }
    }

    return found;  // Return 1 if any intersection was found, otherwise 0
}
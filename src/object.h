// object.h
#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"  // Ensure all type dependencies are defined, including Sphere, Plane, and HitInfo
#include "vector.h"
#include "ray.h"

// Function declarations for object operations
int intersect_ray_sphere(Ray ray, Sphere sphere, float *t);
int intersect_ray_plane(Ray ray, Plane plane, float *t);  // Add this function to handle plane intersection
int find_nearest_object(struct Scene *scene, Ray ray, struct HitInfo *hit);

#endif // OBJECT_H

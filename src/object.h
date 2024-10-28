// object.h
#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"  // Ensure all type dependencies are defined
#include "vector.h"
#include "ray.h"

// Function declarations for object operations
int intersect_ray_sphere(Ray ray, Sphere sphere, float *t);
int find_nearest_object(struct Scene *scene, Ray ray, struct HitInfo *hit);

#endif // OBJECT_H

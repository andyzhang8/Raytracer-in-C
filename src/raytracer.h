#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "types.h"   // Include types.h for HitInfo
#include "vector.h"
#include "ray.h"

struct Scene;  // Forward declaration for Scene

// Function declarations for ray tracing
Vector3 trace_ray(struct Scene *scene, Ray ray, int depth);
Vector3 calculate_color(struct Scene *scene, HitInfo hit, Ray view_ray, int depth);

#endif // RAYTRACER_H

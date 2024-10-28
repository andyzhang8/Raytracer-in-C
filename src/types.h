#ifndef TYPES_H
#define TYPES_H

#include "vector.h"
#include "material.h"
#include "ray.h"  // Include Ray definition

// Forward declarations for shared structures to break circular dependencies
struct Scene;
struct HitInfo;
struct SceneObjects;

// Basic types commonly used across the project
typedef struct {
    Vector3 center;
    float radius;
    Material material;
} Sphere;

typedef struct {
    Sphere *spheres;
    int sphere_count;
} SceneObjects;

typedef struct HitInfo {  // Updated to struct HitInfo
    Vector3 point;
    Vector3 normal;
    float t;
    Sphere *object;
} HitInfo;

#endif // TYPES_H

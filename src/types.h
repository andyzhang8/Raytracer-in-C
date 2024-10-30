#ifndef TYPES_H
#define TYPES_H

#include "vector.h"
#include "material.h"
#include "ray.h"

// Forward declarations
struct Scene;
struct HitInfo;
struct SceneObjects;

// Object type identifiers
#define OBJECT_SPHERE 1
#define OBJECT_PLANE 2

// Basic types
typedef struct {
    Vector3 center;
    float radius;
    Material material;
} Sphere;

typedef struct {
    Vector3 point;    // A point on the plane
    Vector3 normal;   // Normal vector to the plane
    Material material;
} Plane;

typedef struct {
    Sphere *spheres;
    int sphere_count;
    Plane *planes;
    int plane_count;
} SceneObjects;

typedef struct HitInfo {
    Vector3 point;
    Vector3 normal;
    float t;
    int object_type;  // Type of object hit (SPHERE or PLANE)
    void *object;     // Pointer to the specific object (Sphere or Plane)
} HitInfo;

#endif // TYPES_H

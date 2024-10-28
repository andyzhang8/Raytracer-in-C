#ifndef RAY_H
#define RAY_H

#include "vector.h"  // For Vector3

// Ray structure with an origin and direction
typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

#endif // RAY_H

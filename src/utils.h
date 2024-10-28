#ifndef UTILS_H
#define UTILS_H

#include "vector.h"

// Clamp a float value between min and max
float clamp(float value, float min, float max);

// Linearly interpolate between two values
float lerp(float a, float b, float t);

// Convert degrees to radians
float degrees_to_radians(float degrees);

// Generate a random float between 0 and 1
float random_float();


#endif // UTILS_H
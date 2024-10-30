#include "utils.h"
#include <stdlib.h>
#include "vector.h"
#define _USE_MATH_DEFINES 
#include <math.h>

// Clamp a float value between min and max
float clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}


// Linearly interpolate between two values
float lerp(float a, float b, float t) {
    return a * (1.0f - t) + b * t;
}

// Convert degrees to radians
float degrees_to_radians(float degrees) {
    return degrees * (M_PI / 180.0f);
}


float random_float() {
    return (float)rand() / RAND_MAX * 2.0f - 1.0f;
}


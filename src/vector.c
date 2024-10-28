#include "vector.h"
#include <math.h>

// Vector addition
Vector3 vector_add(Vector3 a, Vector3 b) {
    return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

// Vector subtraction
Vector3 vector_sub(Vector3 a, Vector3 b) {
    return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

// Scale a vector by a scalar
Vector3 vector_scale(Vector3 a, float scalar) {
    return (Vector3){a.x * scalar, a.y * scalar, a.z * scalar};
}

// Component-wise multiplication of two vectors
Vector3 vector_mult(Vector3 a, Vector3 b) {
    return (Vector3){a.x * b.x, a.y * b.y, a.z * b.z};
}

// Dot product of two vectors
float vector_dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product of two vectors
Vector3 vector_cross(Vector3 a, Vector3 b) {
    return (Vector3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// Calculate the length (magnitude) of a vector
float vector_length(Vector3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Normalize a vector (make it unit length)
Vector3 vector_normalize(Vector3 v) {
    float length = vector_length(v);
    return vector_scale(v, 1.0f / length);
}

// Reflect a vector around a normal
Vector3 reflect(Vector3 direction, Vector3 normal) {
    return vector_sub(direction, vector_scale(normal, 2 * vector_dot(direction, normal)));
}

// Refract a vector using Snell's law
Vector3 refract(Vector3 direction, Vector3 normal, float ior) {
    float cosi = fmaxf(-1.0f, fminf(1.0f, vector_dot(direction, normal)));
    float etai = 1.0f, etat = ior;
    Vector3 n = normal;
    
    if (cosi < 0) {
        cosi = -cosi;
    } else {
        float temp = etai;
        etai = etat;
        etat = temp;
        n = vector_scale(normal, -1);
    }
    
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? (Vector3){0, 0, 0} : vector_add(vector_scale(direction, eta), vector_scale(n, eta * cosi - sqrtf(k)));
}

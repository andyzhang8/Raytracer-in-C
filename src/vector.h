// vector.h
#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x, y, z;
} Vector3;

// Vector function declarations
Vector3 vector_add(Vector3 a, Vector3 b);
Vector3 vector_sub(Vector3 a, Vector3 b);
Vector3 vector_scale(Vector3 a, float scalar);
Vector3 vector_mult(Vector3 a, Vector3 b);
float vector_dot(Vector3 a, Vector3 b);
Vector3 vector_cross(Vector3 a, Vector3 b);
float vector_length(Vector3 v);
Vector3 vector_normalize(Vector3 v);
Vector3 reflect(Vector3 direction, Vector3 normal);
Vector3 refract(Vector3 direction, Vector3 normal, float ior);

#endif // VECTOR_H

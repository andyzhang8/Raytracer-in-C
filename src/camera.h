#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"  // Include ray.h to access Ray type

typedef struct {
    Vector3 position;        // Camera position
    Vector3 direction;       // Camera look-at direction
    Vector3 up;              // Up vector for orientation
    float fov;               // Field of view (in degrees)
    float aspect_ratio;      // Aspect ratio (width / height)
    Vector3 right;           // Right vector derived from direction and up
} Camera;

// Initialize the camera with position, direction, up vector, FOV, and aspect ratio
Camera init_camera(Vector3 position, Vector3 look_at, Vector3 up, float fov, float aspect_ratio);

// Generate a ray from the camera through the pixel (x, y) on the image plane
Ray generate_camera_ray(Camera camera, int x, int y, int width, int height);

#endif // CAMERA_H

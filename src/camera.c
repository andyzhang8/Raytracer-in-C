#include "camera.h"
#include "vector.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h> // For debugging


// Initialize the camera with position, direction, up vector, field of view, and aspect ratio
Camera init_camera(Vector3 position, Vector3 look_at, Vector3 up, float fov, float aspect_ratio) {
    Camera camera;
    camera.position = position;
    camera.direction = vector_normalize(vector_sub(look_at, position));
    camera.up = vector_normalize(up);
    camera.fov = fov;
    camera.aspect_ratio = aspect_ratio;

    // Calculate the right vector using cross product of direction and up
    camera.right = vector_normalize(vector_cross(camera.direction, camera.up));

    // Recalculate the true up vector to ensure orthogonality
    camera.up = vector_cross(camera.right, camera.direction);

    // Debugging output to verify camera orientation
    printf("Camera Position: (%f, %f, %f)\n", camera.position.x, camera.position.y, camera.position.z);
    printf("Camera Direction: (%f, %f, %f)\n", camera.direction.x, camera.direction.y, camera.direction.z);
    printf("Camera Up: (%f, %f, %f)\n", camera.up.x, camera.up.y, camera.up.z);
    printf("Camera Right: (%f, %f, %f)\n", camera.right.x, camera.right.y, camera.right.z);

    return camera;
}

// Generate a ray from the camera through the pixel (x, y) on the image plane
Ray generate_camera_ray(Camera camera, int x, int y, int width, int height) {
    // Calculate the field of view scaling factors
    float fov_scale = tan(camera.fov * 0.5 * (M_PI / 180.0));  // Convert FOV to radians
    float image_aspect_ratio = camera.aspect_ratio;

    // Calculate the normalized device coordinates (NDC) for the pixel
    float px = (2 * ((x + 0.5) / (float)width) - 1) * image_aspect_ratio * fov_scale;
    float py = (1 - 2 * ((y + 0.5) / (float)height)) * fov_scale;

    // Calculate the ray direction
    Vector3 ray_direction = vector_normalize(vector_add(vector_add(
        vector_scale(camera.right, px), 
        vector_scale(camera.up, py)), 
        camera.direction));

    // Create the ray with the camera's position as the origin and calculated direction
    Ray ray = { camera.position, ray_direction };

    // Debugging output to verify generated ray direction for center pixel
    if (x == width / 2 && y == height / 2) {  // Center ray
        printf("Center Ray Direction: (%f, %f, %f)\n", ray_direction.x, ray_direction.y, ray_direction.z);
    }

    return ray;
}

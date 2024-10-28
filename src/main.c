#include <stddef.h>  // For NULL
#include "render.h"
#include "scene.h"   // Include scene.h for struct Scene, load_scene, and cleanup_scene

int main(int argc, char *argv[]) {
    struct Scene scene = load_scene(NULL);  // Load default scene (or pass a filename to load from file)
    Camera camera = init_camera(
        (Vector3){0, 0, 0},    // Position the camera at the origin
        (Vector3){0, 0, -5},   // Look-at target at the sphere's center
        (Vector3){0, 1, 0},    // Up vector
        60.0f,                 // Field of view
        16.0f / 9.0f           // Aspect ratio
    );

    int width = 800;
    int height = 450;
    render(scene, camera, width, height, 0);  // Render the scene

    cleanup_scene(&scene);  // Free resources
    return 0;
}
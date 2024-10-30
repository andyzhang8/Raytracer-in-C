#include <stddef.h>  // For NULL
#include "render.h"
#include "scene.h"   // Include scene.h for struct Scene, load_scene, and cleanup_scene
#include "texture.h" // Include texture to load texture files
#include <stdio.h>   // For debugging output

void debug_scene(struct Scene *scene) {
    if (scene->objects.spheres == NULL) {
        fprintf(stderr, "Error: No spheres in scene.\n");
    } else {
        fprintf(stdout, "Spheres in scene: %d\n", scene->objects.sphere_count);
    }

    if (scene->objects.planes == NULL && scene->objects.plane_count > 0) {
        fprintf(stderr, "Error: Planes allocated but count is zero.\n");
    } else if (scene->objects.planes != NULL) {
        fprintf(stdout, "Planes in scene: %d\n", scene->objects.plane_count);
    }

    if (scene->point_lights == NULL && scene->point_light_count > 0) {
        fprintf(stderr, "Error: Point lights allocated but count is zero.\n");
    } else if (scene->point_lights != NULL) {
        fprintf(stdout, "Point lights in scene: %d\n", scene->point_light_count);
    }

    if (scene->directional_lights == NULL && scene->directional_light_count > 0) {
        fprintf(stderr, "Error: Directional lights allocated but count is zero.\n");
    } else if (scene->directional_lights != NULL) {
        fprintf(stdout, "Directional lights in scene: %d\n", scene->directional_light_count);
    }
}

int main(int argc, char *argv[]) {
    struct Scene scene = load_scene(NULL);  // Load default scene (or pass a filename to load from file)

    // Load texture
    Texture texture = load_texture("./assets/test_texture2.jpg");
    if (texture.data == NULL) {
        fprintf(stderr, "Error: Failed to load texture.\n");
        cleanup_scene(&scene);
        return 1;
    }
    
    // Assign texture to the sphere material
    if (scene.objects.sphere_count > 0) {
        set_texture(&scene.objects.spheres[0].material, &texture);
    } else {
        fprintf(stderr, "Error: No sphere found to assign texture.\n");
    }

    // Debug scene allocation and initialization
    debug_scene(&scene);

    Camera camera = init_camera(
        (Vector3){0, 0.5, 1},    // Positioned a bit above and in front of the sphere
        (Vector3){0, 0, -5},   // Looking directly at the sphere's center
        (Vector3){0, 1, 0},    // Up vector
        60.0f,                 // Field of view
        16.0f / 9.0f           // Aspect ratio
    );

    int width = 800;
    int height = 450;
    render(scene, camera, width, height, 0);  // Render the scene

    // Free resources
    free_texture(&texture);  // Free texture data
    cleanup_scene(&scene);
    return 0;
}

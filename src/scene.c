#include "scene.h"
#include "material.h"
#include <stdlib.h>  // For malloc

// Load a scene from a file
// Load a scene from a file
struct Scene load_scene(const char *filename) {
    struct Scene scene;
    scene.background_color = (Vector3){0.1f, 0.1f, 0.1f};  // Dark gray background

    // Initialize objects
    scene.objects.sphere_count = 1;
    scene.objects.spheres = malloc(sizeof(Sphere) * scene.objects.sphere_count);
    scene.objects.spheres[0] = (Sphere){
        .center = (Vector3){0.0f, 0.0f, -5.0f},
        .radius = 1.0f,
        .material = create_material((Vector3){0.7f, 0.1f, 0.1f}, 0.5f, 0.5f, 1.5f, 30.0f)
    };

    // Move point light to the left of the sphere
    scene.point_light_count = 1;
    scene.point_lights = malloc(sizeof(PointLight) * scene.point_light_count);
    scene.point_lights[0] = (PointLight){
        .position = (Vector3){-5.0f, 1.0f, -3.0f},  // Adjusted to the left of the sphere
        .color = (Vector3){1.0f, 1.0f, 1.0f},
        .intensity = 1.0f
    };

    // Initialize directional lights (if needed)
    scene.directional_light_count = 1;
    scene.directional_lights = malloc(sizeof(DirectionalLight) * scene.directional_light_count);
    scene.directional_lights[0] = (DirectionalLight){
        .direction = (Vector3){-1.0f, -1.0f, -1.0f},
        .color = (Vector3){1.0f, 1.0f, 1.0f},
        .intensity = 0.5f
    };

    // Ambient light
    scene.ambient_light = (AmbientLight){
        .color = (Vector3){0.2f, 0.2f, 0.2f},
        .intensity = 0.2f
    };

    return scene;
}


// Cleanup function for the scene
void cleanup_scene(struct Scene *scene) {
    free(scene->objects.spheres);
    free(scene->point_lights);
    if (scene->directional_lights) {
        free(scene->directional_lights);
    }
}

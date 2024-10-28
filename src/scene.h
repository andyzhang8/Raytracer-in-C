#ifndef SCENE_H
#define SCENE_H

#include "types.h"    // For SceneObjects and shared types
#include "lighting.h" // For lighting definitions
#include "vector.h"

struct Scene {
    SceneObjects objects;
    PointLight *point_lights;
    int point_light_count;
    DirectionalLight *directional_lights;
    int directional_light_count;
    AmbientLight ambient_light;
    Vector3 background_color;
};

// Function declarations with `struct Scene`
struct Scene load_scene(const char *filename);
void cleanup_scene(struct Scene *scene);

#endif // SCENE_H

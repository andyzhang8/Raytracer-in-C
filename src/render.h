#ifndef RENDER_H
#define RENDER_H

#include "vector.h"
#include "camera.h"
#include "scene.h"  // Ensure scene.h is included for struct Scene
#define MAX_RECURSION_DEPTH 5  // Example depth limit


void render(struct Scene scene, Camera camera, int width, int height, int optimize);

#endif // RENDER_H

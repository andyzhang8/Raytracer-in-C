#include "render.h"
#include "utils.h"  // Include for clamp function
#include "raytracer.h"
#include "scene.h"
#include "postprocessing.h"
#include "camera.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_RECURSION_DEPTH 5

struct Scene;  // Forward declaration of Scene
void save_image(Vector3 *color_data, int width, int height);  // Forward declaration of save_image

// Function to set the color of a pixel in the output buffer
void set_pixel(Vector3 *color_data, int x, int y, int width, Vector3 color) {
    color_data[y * width + x] = color;
}

void render(struct Scene scene, Camera camera, int width, int height, int optimize) {
    Vector3 *color_data = malloc(sizeof(Vector3) * width * height);
    if (!color_data) {
        fprintf(stderr, "Error: Unable to allocate memory for color buffer.\n");
        exit(1);
    }

    // Check if the scene has at least one object or light
    if (scene.objects.sphere_count <= 0 && scene.point_light_count <= 0 && scene.directional_light_count <= 0) {
        fprintf(stderr, "Warning: No objects or lights in the scene.\n");
    }

    // Loop over each pixel and trace rays
    for (int y = 0; y < height; y++) {
        for (int x = (optimize && y % 2 == 1) ? 1 : 0; x < width; x += (optimize ? 2 : 1)) {
            Ray ray = generate_camera_ray(camera, x, y, width, height);

            // Confirm ray direction is valid
            if (ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0) {
                fprintf(stderr, "Warning: Generated ray at (%d, %d) has zero direction.\n", x, y);
                continue;
            }

            Vector3 color = trace_ray(&scene, ray, MAX_RECURSION_DEPTH);
            if (color.x < 0 || color.y < 0 || color.z < 0) {
                fprintf(stderr, "Warning: Invalid color generated at pixel (%d, %d).\n", x, y);
            }

            set_pixel(color_data, x, y, width, color);
        }
    }

    // Apply post-processing effects
    apply_gamma_correction(color_data, width, height, 1.0f); // Gamma correction
    apply_brightness(color_data, width, height, 1.5f);       // Brightness adjustment

    // Save or display the image
    save_image(color_data, width, height);

    // Clean up memory
    free(color_data);
}


// Save image function
void save_image(Vector3 *color_data, int width, int height) {
    FILE *file = fopen("output.ppm", "w");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file for output.\n");
        return;
    }

    // Write the PPM header
    fprintf(file, "P3\n%d %d\n255\n", width, height);

    // Write the pixel data
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vector3 color = color_data[y * width + x];
            int r = (int)(clamp(color.x, 0.0f, 1.0f) * 255.0f);
            int g = (int)(clamp(color.y, 0.0f, 1.0f) * 255.0f);
            int b = (int)(clamp(color.z, 0.0f, 1.0f) * 255.0f);
            fprintf(file, "%d %d %d ", r, g, b);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Image saved to output.ppm\n");
}

#include "postprocessing.h"
#include <math.h>

// Apply gamma correction to each pixel in the color data
void apply_gamma_correction(Vector3 *color_data, int width, int height, float gamma) {
    float gamma_inv = 1.0f / gamma;

    for (int i = 0; i < width * height; i++) {
        color_data[i].x = powf(color_data[i].x, gamma_inv);
        color_data[i].y = powf(color_data[i].y, gamma_inv);
        color_data[i].z = powf(color_data[i].z, gamma_inv);

        // Clamp colors between 0 and 1 after gamma correction
        color_data[i].x = fmin(fmax(color_data[i].x, 0.0f), 1.0f);
        color_data[i].y = fmin(fmax(color_data[i].y, 0.0f), 1.0f);
        color_data[i].z = fmin(fmax(color_data[i].z, 0.0f), 1.0f);
    }
}

// Apply brightness adjustment to each pixel in the color data
void apply_brightness(Vector3 *color_data, int width, int height, float brightness_factor) {
    for (int i = 0; i < width * height; i++) {
        color_data[i].x *= brightness_factor;
        color_data[i].y *= brightness_factor;
        color_data[i].z *= brightness_factor;

        // Clamp colors between 0 and 1 after brightness adjustment
        color_data[i].x = fmin(fmax(color_data[i].x, 0.0f), 1.0f);
        color_data[i].y = fmin(fmax(color_data[i].y, 0.0f), 1.0f);
        color_data[i].z = fmin(fmax(color_data[i].z, 0.0f), 1.0f);
    }
}

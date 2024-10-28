#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "vector.h"

// Apply gamma correction to the color data
void apply_gamma_correction(Vector3 *color_data, int width, int height, float gamma);

// Apply brightness adjustment to the color data
void apply_brightness(Vector3 *color_data, int width, int height, float brightness_factor);

// Additional post-processing effects can be declared here

#endif // POSTPROCESSING_H


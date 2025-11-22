
/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "gpupixel_macros.h"

// base
#include "framebuffer.h"
#include "framebuffer_cache.h"
#include "gl_program.h"
#include "gpupixel_context.h"

// utils
#include "../utils/math_toolbox.h"
#include "../utils/util.h"

// source
#include "../source/source.h"
//#include "../source/source_camera.h"
#include "../source/source_image.h"

// target
#include "../target/target.h"
#include "../target/target_view.h"

// base filters
#include "../filter/filter.h"
#include "../filter/filter_group.h"
#include "../filter/box_blur_filter.h"
#include "../filter/box_difference_filter.h"
#include "../filter/box_high_pass_filter.h"
#include "../filter/box_mono_blur_filter.h"

// general filters
#include "../filter/bilateral_filter.h"
#include "../filter/brightness_filter.h"
#include "../filter/canny_edge_detection_filter.h"
#include "../filter/color_invert_filter.h"
#include "../filter/color_matrix_filter.h"
#include "../filter/contrast_filter.h"
#include "../filter/convolution3x3_filter.h"
#include "../filter/crosshatch_filter.h"
#include "../filter/directional_non_maximum_suppression_filter.h"
#include "../filter/directional_sobel_edge_detection_filter.h"
#include "../filter/emboss_filter.h"
#include "../filter/exposure_filter.h"
#include "../filter/gaussian_blur_filter.h"
#include "../filter/gaussian_blur_mono_filter.h"
#include "../filter/glass_sphere_filter.h"
#include "../filter/grayscale_filter.h"
#include "../filter/hsb_filter.h"
#include "../filter/halftone_filter.h"
#include "../filter/hue_filter.h"
#include "../filter/luminance_range_filter.h"
#include "../filter/nearby_sampling3x3_filter.h"
#include "../filter/non_maximum_suppression_filter.h"
#include "../filter/pixellation_filter.h"
#include "../filter/posterize_filter.h"
#include "../filter/rgb_filter.h"
#include "../filter/saturation_filter.h"
#include "../filter/single_component_gaussian_blur_filter.h"
#include "../filter/single_component_gaussian_blur_mono_filter.h"
#include "../filter/sketch_filter.h"
#include "../filter/smooth_toon_filter.h"
#include "../filter/sobel_edge_detection_filter.h"
#include "../filter/sphere_refraction_filter.h"
#include "../filter/toon_filter.h"
#include "../filter/weak_pixel_inclusion_filter.h"
#include "../filter/white_balance_filter.h"

// beauty filters
#include "../filter/beauty_face_filter.h"
#include "../filter/beauty_face_unit_filter.h"
#include "../filter/blusher_filter.h"
#include "../filter/face_makeup_filter.h"
#include "../filter/face_reshape_filter.h"
#include "../filter/lipstick_filter.h"

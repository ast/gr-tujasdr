//
//  tujavolk.h
//  libtujavolk
//
//  Created by Albin Stigö on 2018-12-21.
//  Copyright © 2018 Albin Stigo. All rights reserved.
//

#pragma once

#include <stdint.h>
#include <arm_neon.h>
#include <volk/volk.h>

// Kernels that are not yet in volk

static inline void
volk_32i_s32f_convert_32f_neon(float* outputVector,
                               const int32_t* inputVector,
                               const float scalar,
                               unsigned int num_points) {
    float* outputVectorPtr = outputVector;
    const int32_t* inputVectorPtr = inputVector;
    const float iScalar = 1.0 / scalar;
    unsigned int number;
    unsigned int quarter_points = num_points / 4;
    int32x4_t input_vec;
    float32x4_t ouput_vec;
    
    const float32x4_t iscalar_vec = vdupq_n_f32(iScalar);
    
    for(number = 0; number < quarter_points; number++) {
        // load s32
        input_vec = vld1q_s32(inputVectorPtr);
        // Prefetch next 4
        __VOLK_PREFETCH(inputVectorPtr+4);
        // convert s32 to f32
        ouput_vec = vcvtq_f32_s32(input_vec);
        // scale
        ouput_vec = vmulq_f32(ouput_vec, iscalar_vec);
        // store
        vst1q_f32(outputVectorPtr, ouput_vec);
        // move pointers ahead
        outputVectorPtr+=4;
        inputVectorPtr+=4;
    }
    
    // deal with the rest
    for(number = quarter_points * 4; number < num_points; number++) {
        *outputVectorPtr++ = ((float)(*inputVectorPtr++)) * iScalar;
    }
}

static inline void
volk_32f_s32f_convert_32i_neon(int32_t* outputVector,
                               const float* inputVector,
                               const float scalar,
                               unsigned int num_points) {
    int32_t* outputVectorPtr = outputVector;
    const float* inputVectorPtr = inputVector;
    unsigned int number;
    unsigned int quarter_points = num_points / 4;
    float32x4_t input_vec;
    int32x4_t ouput_vec;
    
    float min_val = -2147483647;
    float max_val = 2147483647;
    float r;
    
    const float32x4_t scalar_vec = vdupq_n_f32(scalar);
    
    for(number = 0; number < quarter_points; number++) {
        // load f32
        input_vec = vld1q_f32(inputVectorPtr);
        // Prefetch next 4
        __VOLK_PREFETCH(inputVectorPtr+4);
        // scale, this is saturating
        input_vec = vmulq_f32(input_vec, scalar_vec);
        // convert f32 to s32
        ouput_vec = vcvtq_s32_f32(input_vec);
        // store
        vst1q_s32(outputVectorPtr, ouput_vec);
        // move pointers ahead
        outputVectorPtr+=4;
        inputVectorPtr+=4;
    }
    
    // deal with the rest
    for(number = quarter_points * 4; number < num_points; number++) {
        r = *inputVectorPtr++ * scalar;
        if(r > max_val)
            r = max_val;
        else if(r < min_val)
            r = min_val;
        *outputVectorPtr++ = (int32_t)(r);
    }
}

static void inline
volk_32fc_sum_parts_32f_neon(float* outputVector,
                             const lv_32fc_t* inputVector,
                             unsigned int num_points) {
    
    unsigned int number = 0;
    unsigned int quarter_points = num_points / 4;
    float* outputVectorPtr = outputVector;
    const lv_32fc_t* inputVectorPtr = inputVector;
    
    float32x4x2_t input_vec;
    float32x4_t output_vec;
    
    for(number = 0; number < quarter_points; number++) {
        // Load to lanes interleaved
        input_vec = vld2q_f32((const float*)inputVectorPtr);
        // Prefetch next one, speeds things up
        __VOLK_PREFETCH(inputVectorPtr+4);
        // Sum parts
        output_vec = vaddq_f32(input_vec.val[0], input_vec.val[1]);
        // Store result
        vst1q_f32(outputVectorPtr, output_vec);
        // move pointers ahead
        outputVectorPtr+=4;
        inputVectorPtr+=4;
    }
    
    // Deal with the rest
    for(number = quarter_points * 4; number < num_points; number++) {
        *outputVectorPtr = (*inputVectorPtr).real() + (*inputVectorPtr).imag();
        outputVectorPtr++;
        inputVectorPtr++;
    }
}


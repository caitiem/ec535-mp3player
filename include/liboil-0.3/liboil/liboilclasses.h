/*
 * LIBOIL - Library of Optimized Inner Loops
 * Copyright (c) 2005 David A. Schleef <ds@schleef.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* This file is automatically generated.  Do not edit. */

#ifndef _LIBOIL_CLASSES_H_
#define _LIBOIL_CLASSES_H_

#include <liboil/liboilfunction.h>

#ifdef __cplusplus
extern "C" {
#endif

OIL_DECLARE_CLASS(abs_f32_f32);
OIL_DECLARE_CLASS(abs_f64_f64);
OIL_DECLARE_CLASS(abs_u16_s16);
OIL_DECLARE_CLASS(abs_u32_s32);
OIL_DECLARE_CLASS(abs_u8_s8);
OIL_DECLARE_CLASS(add_const_rshift_s16);
OIL_DECLARE_CLASS(add_f32);
OIL_DECLARE_CLASS(add_s16);
OIL_DECLARE_CLASS(add_s16_u8);
OIL_DECLARE_CLASS(argb_paint_u8);
OIL_DECLARE_CLASS(average2_u8);
OIL_DECLARE_CLASS(ayuv2argb_u8);
OIL_DECLARE_CLASS(ayuv2uyvy);
OIL_DECLARE_CLASS(ayuv2yuyv);
OIL_DECLARE_CLASS(ayuv2yvyu);
OIL_DECLARE_CLASS(clamp_f32);
OIL_DECLARE_CLASS(clamp_f64);
OIL_DECLARE_CLASS(clamp_s16);
OIL_DECLARE_CLASS(clamp_s32);
OIL_DECLARE_CLASS(clamp_s8);
OIL_DECLARE_CLASS(clamp_u16);
OIL_DECLARE_CLASS(clamp_u32);
OIL_DECLARE_CLASS(clamp_u8);
OIL_DECLARE_CLASS(clamphigh_f32);
OIL_DECLARE_CLASS(clamphigh_f64);
OIL_DECLARE_CLASS(clamphigh_s16);
OIL_DECLARE_CLASS(clamphigh_s32);
OIL_DECLARE_CLASS(clamphigh_s8);
OIL_DECLARE_CLASS(clamphigh_u16);
OIL_DECLARE_CLASS(clamphigh_u32);
OIL_DECLARE_CLASS(clamphigh_u8);
OIL_DECLARE_CLASS(clamplow_f32);
OIL_DECLARE_CLASS(clamplow_f64);
OIL_DECLARE_CLASS(clamplow_s16);
OIL_DECLARE_CLASS(clamplow_s32);
OIL_DECLARE_CLASS(clamplow_s8);
OIL_DECLARE_CLASS(clamplow_u16);
OIL_DECLARE_CLASS(clamplow_u32);
OIL_DECLARE_CLASS(clamplow_u8);
OIL_DECLARE_CLASS(clip_f32);
OIL_DECLARE_CLASS(clip_f64);
OIL_DECLARE_CLASS(clip_s16);
OIL_DECLARE_CLASS(clip_s32);
OIL_DECLARE_CLASS(clip_s8);
OIL_DECLARE_CLASS(clip_u16);
OIL_DECLARE_CLASS(clip_u32);
OIL_DECLARE_CLASS(clip_u8);
OIL_DECLARE_CLASS(clipconv8x8_u8_s16);
OIL_DECLARE_CLASS(clipconv_s16_f32);
OIL_DECLARE_CLASS(clipconv_s16_f64);
OIL_DECLARE_CLASS(clipconv_s16_s32);
OIL_DECLARE_CLASS(clipconv_s16_u16);
OIL_DECLARE_CLASS(clipconv_s16_u32);
OIL_DECLARE_CLASS(clipconv_s32_f32);
OIL_DECLARE_CLASS(clipconv_s32_f64);
OIL_DECLARE_CLASS(clipconv_s32_u32);
OIL_DECLARE_CLASS(clipconv_s8_f32);
OIL_DECLARE_CLASS(clipconv_s8_f64);
OIL_DECLARE_CLASS(clipconv_s8_s16);
OIL_DECLARE_CLASS(clipconv_s8_s32);
OIL_DECLARE_CLASS(clipconv_s8_u16);
OIL_DECLARE_CLASS(clipconv_s8_u32);
OIL_DECLARE_CLASS(clipconv_s8_u8);
OIL_DECLARE_CLASS(clipconv_u16_f32);
OIL_DECLARE_CLASS(clipconv_u16_f64);
OIL_DECLARE_CLASS(clipconv_u16_s16);
OIL_DECLARE_CLASS(clipconv_u16_s32);
OIL_DECLARE_CLASS(clipconv_u16_u32);
OIL_DECLARE_CLASS(clipconv_u32_f32);
OIL_DECLARE_CLASS(clipconv_u32_f64);
OIL_DECLARE_CLASS(clipconv_u32_s32);
OIL_DECLARE_CLASS(clipconv_u8_f32);
OIL_DECLARE_CLASS(clipconv_u8_f64);
OIL_DECLARE_CLASS(clipconv_u8_s16);
OIL_DECLARE_CLASS(clipconv_u8_s32);
OIL_DECLARE_CLASS(clipconv_u8_s8);
OIL_DECLARE_CLASS(clipconv_u8_u16);
OIL_DECLARE_CLASS(clipconv_u8_u32);
OIL_DECLARE_CLASS(colorspace_argb);
OIL_DECLARE_CLASS(colsad8x8_u8);
OIL_DECLARE_CLASS(compare_u8);
OIL_DECLARE_CLASS(composite_add_argb);
OIL_DECLARE_CLASS(composite_add_argb_const_src);
OIL_DECLARE_CLASS(composite_add_u8);
OIL_DECLARE_CLASS(composite_add_u8_const_src);
OIL_DECLARE_CLASS(composite_in_argb);
OIL_DECLARE_CLASS(composite_in_argb_const_mask);
OIL_DECLARE_CLASS(composite_in_argb_const_src);
OIL_DECLARE_CLASS(composite_in_over_argb);
OIL_DECLARE_CLASS(composite_in_over_argb_const_mask);
OIL_DECLARE_CLASS(composite_in_over_argb_const_src);
OIL_DECLARE_CLASS(composite_over_argb);
OIL_DECLARE_CLASS(composite_over_argb_const_src);
OIL_DECLARE_CLASS(composite_over_u8);
OIL_DECLARE_CLASS(conv8x8_f64_s16);
OIL_DECLARE_CLASS(conv8x8_s16_f64);
OIL_DECLARE_CLASS(conv_f32_f64);
OIL_DECLARE_CLASS(conv_f32_s16);
OIL_DECLARE_CLASS(conv_f32_s32);
OIL_DECLARE_CLASS(conv_f32_s8);
OIL_DECLARE_CLASS(conv_f32_u16);
OIL_DECLARE_CLASS(conv_f32_u32);
OIL_DECLARE_CLASS(conv_f32_u8);
OIL_DECLARE_CLASS(conv_f64_f32);
OIL_DECLARE_CLASS(conv_f64_s16);
OIL_DECLARE_CLASS(conv_f64_s32);
OIL_DECLARE_CLASS(conv_f64_s8);
OIL_DECLARE_CLASS(conv_f64_u16);
OIL_DECLARE_CLASS(conv_f64_u32);
OIL_DECLARE_CLASS(conv_f64_u8);
OIL_DECLARE_CLASS(conv_s16_f32);
OIL_DECLARE_CLASS(conv_s16_f64);
OIL_DECLARE_CLASS(conv_s16_s32);
OIL_DECLARE_CLASS(conv_s16_s8);
OIL_DECLARE_CLASS(conv_s16_u16);
OIL_DECLARE_CLASS(conv_s16_u32);
OIL_DECLARE_CLASS(conv_s16_u8);
OIL_DECLARE_CLASS(conv_s32_f32);
OIL_DECLARE_CLASS(conv_s32_f64);
OIL_DECLARE_CLASS(conv_s32_s16);
OIL_DECLARE_CLASS(conv_s32_s8);
OIL_DECLARE_CLASS(conv_s32_u16);
OIL_DECLARE_CLASS(conv_s32_u32);
OIL_DECLARE_CLASS(conv_s32_u8);
OIL_DECLARE_CLASS(conv_s8_f32);
OIL_DECLARE_CLASS(conv_s8_f64);
OIL_DECLARE_CLASS(conv_s8_s16);
OIL_DECLARE_CLASS(conv_s8_s32);
OIL_DECLARE_CLASS(conv_s8_u16);
OIL_DECLARE_CLASS(conv_s8_u32);
OIL_DECLARE_CLASS(conv_s8_u8);
OIL_DECLARE_CLASS(conv_u16_f32);
OIL_DECLARE_CLASS(conv_u16_f64);
OIL_DECLARE_CLASS(conv_u16_s16);
OIL_DECLARE_CLASS(conv_u16_s32);
OIL_DECLARE_CLASS(conv_u16_s8);
OIL_DECLARE_CLASS(conv_u16_u32);
OIL_DECLARE_CLASS(conv_u16_u8);
OIL_DECLARE_CLASS(conv_u32_f32);
OIL_DECLARE_CLASS(conv_u32_f64);
OIL_DECLARE_CLASS(conv_u32_s16);
OIL_DECLARE_CLASS(conv_u32_s32);
OIL_DECLARE_CLASS(conv_u32_s8);
OIL_DECLARE_CLASS(conv_u32_u16);
OIL_DECLARE_CLASS(conv_u32_u8);
OIL_DECLARE_CLASS(conv_u8_f32);
OIL_DECLARE_CLASS(conv_u8_f64);
OIL_DECLARE_CLASS(conv_u8_s16);
OIL_DECLARE_CLASS(conv_u8_s32);
OIL_DECLARE_CLASS(conv_u8_s8);
OIL_DECLARE_CLASS(conv_u8_u16);
OIL_DECLARE_CLASS(conv_u8_u32);
OIL_DECLARE_CLASS(convert_s16_f32);
OIL_DECLARE_CLASS(convert_s16_f64);
OIL_DECLARE_CLASS(convert_s16_s32);
OIL_DECLARE_CLASS(convert_s16_s8);
OIL_DECLARE_CLASS(convert_s16_u16);
OIL_DECLARE_CLASS(convert_s16_u32);
OIL_DECLARE_CLASS(convert_s16_u8);
OIL_DECLARE_CLASS(convert_s32_f64);
OIL_DECLARE_CLASS(convert_s32_s16);
OIL_DECLARE_CLASS(convert_s32_s8);
OIL_DECLARE_CLASS(convert_s32_u16);
OIL_DECLARE_CLASS(convert_s32_u32);
OIL_DECLARE_CLASS(convert_s32_u8);
OIL_DECLARE_CLASS(convert_s8_f32);
OIL_DECLARE_CLASS(convert_s8_f64);
OIL_DECLARE_CLASS(convert_s8_s16);
OIL_DECLARE_CLASS(convert_s8_s32);
OIL_DECLARE_CLASS(convert_s8_u16);
OIL_DECLARE_CLASS(convert_s8_u32);
OIL_DECLARE_CLASS(convert_s8_u8);
OIL_DECLARE_CLASS(convert_u16_f32);
OIL_DECLARE_CLASS(convert_u16_f64);
OIL_DECLARE_CLASS(convert_u16_s16);
OIL_DECLARE_CLASS(convert_u16_s32);
OIL_DECLARE_CLASS(convert_u16_u32);
OIL_DECLARE_CLASS(convert_u16_u8);
OIL_DECLARE_CLASS(convert_u32_f64);
OIL_DECLARE_CLASS(convert_u32_s32);
OIL_DECLARE_CLASS(convert_u32_u16);
OIL_DECLARE_CLASS(convert_u32_u8);
OIL_DECLARE_CLASS(convert_u8_f32);
OIL_DECLARE_CLASS(convert_u8_f64);
OIL_DECLARE_CLASS(convert_u8_s16);
OIL_DECLARE_CLASS(convert_u8_s32);
OIL_DECLARE_CLASS(convert_u8_s8);
OIL_DECLARE_CLASS(convert_u8_u16);
OIL_DECLARE_CLASS(convert_u8_u32);
OIL_DECLARE_CLASS(copy8x8_u8);
OIL_DECLARE_CLASS(copy_u8);
OIL_DECLARE_CLASS(dct36_f32);
OIL_DECLARE_CLASS(deinterleave);
OIL_DECLARE_CLASS(deinterleave2_s16);
OIL_DECLARE_CLASS(dequantize8x8_s16);
OIL_DECLARE_CLASS(diff8x8_average_s16_u8);
OIL_DECLARE_CLASS(diff8x8_const128_s16_u8);
OIL_DECLARE_CLASS(diff8x8_s16_u8);
OIL_DECLARE_CLASS(diffsquaresum_f64);
OIL_DECLARE_CLASS(divide_f32);
OIL_DECLARE_CLASS(err_inter8x8_u8);
OIL_DECLARE_CLASS(err_inter8x8_u8_avg);
OIL_DECLARE_CLASS(err_intra8x8_u8);
OIL_DECLARE_CLASS(fdct8_f64);
OIL_DECLARE_CLASS(fdct8x8_f64);
OIL_DECLARE_CLASS(fdct8x8s_s16);
OIL_DECLARE_CLASS(fdct8x8theora);
OIL_DECLARE_CLASS(floor_f32);
OIL_DECLARE_CLASS(idct8_f64);
OIL_DECLARE_CLASS(idct8theora_s16);
OIL_DECLARE_CLASS(idct8x8_f64);
OIL_DECLARE_CLASS(idct8x8_s16);
OIL_DECLARE_CLASS(idct8x8lim10_f64);
OIL_DECLARE_CLASS(idct8x8lim10_s16);
OIL_DECLARE_CLASS(idct8x8theora_s16);
OIL_DECLARE_CLASS(imdct12_f64);
OIL_DECLARE_CLASS(imdct32_f32);
OIL_DECLARE_CLASS(imdct36_f64);
OIL_DECLARE_CLASS(interleave);
OIL_DECLARE_CLASS(interleave2_s16);
OIL_DECLARE_CLASS(inverse_f32);
OIL_DECLARE_CLASS(lift_add_135);
OIL_DECLARE_CLASS(lift_add_mult_shift12);
OIL_DECLARE_CLASS(lift_add_shift1);
OIL_DECLARE_CLASS(lift_add_shift2);
OIL_DECLARE_CLASS(lift_sub_135);
OIL_DECLARE_CLASS(lift_sub_mult_shift12);
OIL_DECLARE_CLASS(lift_sub_shift1);
OIL_DECLARE_CLASS(lift_sub_shift2);
OIL_DECLARE_CLASS(lshift_s16);
OIL_DECLARE_CLASS(mas2_across_add_s16);
OIL_DECLARE_CLASS(mas2_add_s16);
OIL_DECLARE_CLASS(mas4_across_add_s16);
OIL_DECLARE_CLASS(mas4_add_s16);
OIL_DECLARE_CLASS(mas8_across_add_s16);
OIL_DECLARE_CLASS(mas8_add_s16);
OIL_DECLARE_CLASS(maximum_f32);
OIL_DECLARE_CLASS(md5);
OIL_DECLARE_CLASS(mdct12_f64);
OIL_DECLARE_CLASS(mdct36_f64);
OIL_DECLARE_CLASS(merge_linear_argb);
OIL_DECLARE_CLASS(merge_linear_u8);
OIL_DECLARE_CLASS(minimum_f32);
OIL_DECLARE_CLASS(mix_u8);
OIL_DECLARE_CLASS(mt19937);
OIL_DECLARE_CLASS(mult8x8_s16);
OIL_DECLARE_CLASS(multiply_and_acc_12xn_s16_u8);
OIL_DECLARE_CLASS(multiply_and_add_s16);
OIL_DECLARE_CLASS(multiply_and_add_s16_u8);
OIL_DECLARE_CLASS(multiply_f32);
OIL_DECLARE_CLASS(multsum_f32);
OIL_DECLARE_CLASS(multsum_f64);
OIL_DECLARE_CLASS(negative_f32);
OIL_DECLARE_CLASS(null);
OIL_DECLARE_CLASS(permute_f32);
OIL_DECLARE_CLASS(permute_f64);
OIL_DECLARE_CLASS(permute_s16);
OIL_DECLARE_CLASS(permute_s32);
OIL_DECLARE_CLASS(permute_s8);
OIL_DECLARE_CLASS(permute_u16);
OIL_DECLARE_CLASS(permute_u32);
OIL_DECLARE_CLASS(permute_u8);
OIL_DECLARE_CLASS(recon8x8_inter);
OIL_DECLARE_CLASS(recon8x8_inter2);
OIL_DECLARE_CLASS(recon8x8_intra);
OIL_DECLARE_CLASS(resample_linear_argb);
OIL_DECLARE_CLASS(resample_linear_u8);
OIL_DECLARE_CLASS(rgb2bgr);
OIL_DECLARE_CLASS(rgb2rgba);
OIL_DECLARE_CLASS(rgb565_to_argb);
OIL_DECLARE_CLASS(rowsad8x8_u8);
OIL_DECLARE_CLASS(sad8x8_f64);
OIL_DECLARE_CLASS(sad8x8_f64_2);
OIL_DECLARE_CLASS(sad8x8_s16);
OIL_DECLARE_CLASS(sad8x8_s16_2);
OIL_DECLARE_CLASS(sad8x8_u8);
OIL_DECLARE_CLASS(sad8x8_u8_avg);
OIL_DECLARE_CLASS(scalaradd_f32);
OIL_DECLARE_CLASS(scalaradd_f32_ns);
OIL_DECLARE_CLASS(scalaradd_f64);
OIL_DECLARE_CLASS(scalaradd_s16);
OIL_DECLARE_CLASS(scalaradd_s32);
OIL_DECLARE_CLASS(scalaradd_s8);
OIL_DECLARE_CLASS(scalaradd_u16);
OIL_DECLARE_CLASS(scalaradd_u32);
OIL_DECLARE_CLASS(scalaradd_u8);
OIL_DECLARE_CLASS(scalarmult_f32);
OIL_DECLARE_CLASS(scalarmult_f64);
OIL_DECLARE_CLASS(scalarmult_s16);
OIL_DECLARE_CLASS(scalarmult_s32);
OIL_DECLARE_CLASS(scalarmult_s8);
OIL_DECLARE_CLASS(scalarmult_u16);
OIL_DECLARE_CLASS(scalarmult_u32);
OIL_DECLARE_CLASS(scalarmult_u8);
OIL_DECLARE_CLASS(scalarmultiply_f32_ns);
OIL_DECLARE_CLASS(scaleconv_f32_s16);
OIL_DECLARE_CLASS(scaleconv_f32_s32);
OIL_DECLARE_CLASS(scaleconv_f32_s8);
OIL_DECLARE_CLASS(scaleconv_f32_u16);
OIL_DECLARE_CLASS(scaleconv_f32_u32);
OIL_DECLARE_CLASS(scaleconv_f32_u8);
OIL_DECLARE_CLASS(scaleconv_f64_s16);
OIL_DECLARE_CLASS(scaleconv_f64_s32);
OIL_DECLARE_CLASS(scaleconv_f64_s8);
OIL_DECLARE_CLASS(scaleconv_f64_u16);
OIL_DECLARE_CLASS(scaleconv_f64_u32);
OIL_DECLARE_CLASS(scaleconv_f64_u8);
OIL_DECLARE_CLASS(scaleconv_s16_f32);
OIL_DECLARE_CLASS(scaleconv_s16_f64);
OIL_DECLARE_CLASS(scaleconv_s32_f32);
OIL_DECLARE_CLASS(scaleconv_s32_f64);
OIL_DECLARE_CLASS(scaleconv_s8_f32);
OIL_DECLARE_CLASS(scaleconv_s8_f64);
OIL_DECLARE_CLASS(scaleconv_u16_f32);
OIL_DECLARE_CLASS(scaleconv_u16_f64);
OIL_DECLARE_CLASS(scaleconv_u32_f32);
OIL_DECLARE_CLASS(scaleconv_u32_f64);
OIL_DECLARE_CLASS(scaleconv_u8_f32);
OIL_DECLARE_CLASS(scaleconv_u8_f64);
OIL_DECLARE_CLASS(scanlinescale2_u8);
OIL_DECLARE_CLASS(sign_f32);
OIL_DECLARE_CLASS(sincos_f64);
OIL_DECLARE_CLASS(splat_u16_ns);
OIL_DECLARE_CLASS(splat_u32);
OIL_DECLARE_CLASS(splat_u32_ns);
OIL_DECLARE_CLASS(splat_u8);
OIL_DECLARE_CLASS(splat_u8_ns);
OIL_DECLARE_CLASS(split_135);
OIL_DECLARE_CLASS(split_53);
OIL_DECLARE_CLASS(split_approx97);
OIL_DECLARE_CLASS(split_daub97);
OIL_DECLARE_CLASS(squaresum_f64);
OIL_DECLARE_CLASS(squaresum_shifted_s16);
OIL_DECLARE_CLASS(subtract_f32);
OIL_DECLARE_CLASS(subtract_s16);
OIL_DECLARE_CLASS(subtract_s16_u8);
OIL_DECLARE_CLASS(sum_f64);
OIL_DECLARE_CLASS(sum_s16);
OIL_DECLARE_CLASS(swab_u16);
OIL_DECLARE_CLASS(swab_u32);
OIL_DECLARE_CLASS(synth_135);
OIL_DECLARE_CLASS(synth_53);
OIL_DECLARE_CLASS(synth_approx97);
OIL_DECLARE_CLASS(synth_daub97);
OIL_DECLARE_CLASS(tablelookup_u8);
OIL_DECLARE_CLASS(testzero_u8);
OIL_DECLARE_CLASS(trans8x8_f64);
OIL_DECLARE_CLASS(trans8x8_u16);
OIL_DECLARE_CLASS(trans8x8_u32);
OIL_DECLARE_CLASS(trans8x8_u8);
OIL_DECLARE_CLASS(unzigzag8x8_s16);
OIL_DECLARE_CLASS(utf8_validate);
OIL_DECLARE_CLASS(uyvy2ayuv);
OIL_DECLARE_CLASS(vectoradd_f32);
OIL_DECLARE_CLASS(vectoradd_f64);
OIL_DECLARE_CLASS(vectoradd_s16);
OIL_DECLARE_CLASS(vectoradd_s32);
OIL_DECLARE_CLASS(vectoradd_s8);
OIL_DECLARE_CLASS(vectoradd_s_f32);
OIL_DECLARE_CLASS(vectoradd_s_f64);
OIL_DECLARE_CLASS(vectoradd_s_s16);
OIL_DECLARE_CLASS(vectoradd_s_s8);
OIL_DECLARE_CLASS(vectoradd_s_u16);
OIL_DECLARE_CLASS(vectoradd_s_u8);
OIL_DECLARE_CLASS(vectoradd_u16);
OIL_DECLARE_CLASS(vectoradd_u32);
OIL_DECLARE_CLASS(vectoradd_u8);
OIL_DECLARE_CLASS(yuv2rgbx_sub2_u8);
OIL_DECLARE_CLASS(yuv2rgbx_sub4_u8);
OIL_DECLARE_CLASS(yuv2rgbx_u8);
OIL_DECLARE_CLASS(yuyv2ayuv);
OIL_DECLARE_CLASS(yvyu2ayuv);
OIL_DECLARE_CLASS(zigzag8x8_s16);

#ifdef __cplusplus
}
#endif

#endif


#pragma once

////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
//
// Copyright (c) 2017 Nicholas Frechette & Animation Compression Library contributors
// Copyright (c) 2018 Nicholas Frechette & Realtime Math contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "rtm/math.h"
#include "rtm/impl/compiler_utils.h"
#include "rtm/impl/scalar_common.h"

#include <algorithm>
#include <cmath>

RTM_IMPL_FILE_PRAGMA_PUSH

namespace rtm
{
	//////////////////////////////////////////////////////////////////////////
	// Creates a scalar from a floating point value.
	//////////////////////////////////////////////////////////////////////////
	inline scalard RTM_SIMD_CALL scalar_set(double xyzw) RTM_NO_EXCEPT
	{
#if defined(RTM_SSE2_INTRINSICS)
		return _mm_set1_pd(xyzw);
#else
		return xyzw;
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	// Writes a scalar to memory.
	//////////////////////////////////////////////////////////////////////////
	inline void scalar_store(double input, double* output) RTM_NO_EXCEPT
	{
		*output = input;
	}

	//////////////////////////////////////////////////////////////////////////
	// Casts a scalar into a floating point value.
	//////////////////////////////////////////////////////////////////////////
	inline double RTM_SIMD_CALL scalar_cast(scalard input) RTM_NO_EXCEPT
	{
#if defined(RTM_SSE2_INTRINSICS)
		return _mm_cvtsd_f64(input);
#else
		return input;
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the largest integer value not greater than the input.
	// scalar_floor(1.8) = 1.0
	// scalar_floor(-1.8) = -2.0
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_floor(double input) RTM_NO_EXCEPT
	{
#if defined(RTM_SSE4_INTRINSICS)
		const __m128d value = _mm_set1_pd(input);
		return _mm_cvtsd_f64(_mm_round_sd(value, value, 0x9));
#else
		return std::floor(input);
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the smallest integer value not less than the input.
	// scalar_ceil(1.8) = 2.0
	// scalar_ceil(-1.8) = -1.0
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_ceil(double input) RTM_NO_EXCEPT
	{
#if defined(RTM_SSE4_INTRINSICS)
		const __m128d value = _mm_set1_pd(input);
		return _mm_cvtsd_f64(_mm_round_sd(value, value, 0xA));
#else
		return std::ceil(input);
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the input if it is within the min/max values otherwise the
	// exceeded boundary is returned.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_clamp(double input, double min, double max) RTM_NO_EXCEPT
	{
#if defined(RTM_SSE2_INTRINSICS)
		return _mm_cvtsd_f64(_mm_min_sd(_mm_max_sd(_mm_set1_pd(input), _mm_set1_pd(min)), _mm_set1_pd(max)));
#else
		return std::min(std::max(input, min), max);
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the absolute value of the input.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_abs(double input) RTM_NO_EXCEPT
	{
		return std::fabs(input);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the square root of the input.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_sqrt(double input) RTM_NO_EXCEPT
	{
		return std::sqrt(input);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the reciprocal square root of the input.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_sqrt_reciprocal(double input) RTM_NO_EXCEPT
	{
		return 1.0 / scalar_sqrt(input);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the reciprocal of the input.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_reciprocal(double input) RTM_NO_EXCEPT
	{
		return 1.0 / input;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the subtraction of the two scalar inputs.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_sub(double lhs, double rhs) RTM_NO_EXCEPT
	{
		return lhs - rhs;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the multiplication/addition of the three inputs: s2 + (s0 * s1)
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_mul_add(double s0, double s1, double s2) RTM_NO_EXCEPT
	{
		return (s0 * s1) + s2;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the linear interpolation of the two inputs at the specified alpha.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_lerp(double start, double end, double alpha) RTM_NO_EXCEPT
	{
		return ((end - start) * alpha) + start;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the sine of the input angle.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_sin(double angle) RTM_NO_EXCEPT
	{
		return std::sin(angle);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the cosine of the input angle.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_cos(double angle) RTM_NO_EXCEPT
	{
		return std::cos(angle);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns both sine and cosine of the input angle.
	//////////////////////////////////////////////////////////////////////////
	inline void scalar_sincos(double angle, double& out_sin, double& out_cos) RTM_NO_EXCEPT
	{
		out_sin = scalar_sin(angle);
		out_cos = scalar_cos(angle);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the arc-cosine of the input.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_acos(double value) RTM_NO_EXCEPT
	{
		return std::acos(value);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the arc-tangent of [x/y] using the sign of the arguments to
	// determine the correct quadrant.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_atan2(double x, double y) RTM_NO_EXCEPT
	{
		return std::atan2(x, y);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the smallest of the two inputs.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_min(double left, double right) RTM_NO_EXCEPT
	{
#if defined(RTM_SSE2_INTRINSICS)
		return _mm_cvtsd_f64(_mm_min_sd(_mm_set1_pd(left), _mm_set1_pd(right)));
#else
		return std::min(left, right);
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the largest of the two inputs.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_max(double left, double right) RTM_NO_EXCEPT
	{
#if defined(RTM_SSE2_INTRINSICS)
		return _mm_cvtsd_f64(_mm_max_sd(_mm_set1_pd(left), _mm_set1_pd(right)));
#else
		return std::max(left, right);
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns true if both inputs are equal, false otherwise.
	//////////////////////////////////////////////////////////////////////////
	inline bool scalar_is_equal(double lhs, double rhs) RTM_NO_EXCEPT
	{
		return lhs == rhs;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns true if lhs < rhs, false otherwise.
	//////////////////////////////////////////////////////////////////////////
	inline bool scalar_is_lower(double lhs, double rhs) RTM_NO_EXCEPT
	{
		return lhs < rhs;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns true if both inputs are nearly equal, false otherwise.
	//////////////////////////////////////////////////////////////////////////
	inline bool scalar_near_equal(double lhs, double rhs, double threshold = 0.00001) RTM_NO_EXCEPT
	{
		return scalar_abs(lhs - rhs) < threshold;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns true if the input is finite (not NaN or Inf), false otherwise.
	//////////////////////////////////////////////////////////////////////////
	inline bool scalar_is_finite(double input) RTM_NO_EXCEPT
	{
		return std::isfinite(input);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the rounded input using a symmetric algorithm.
	// scalar_symmetric_round(1.5) = 2.0
	// scalar_symmetric_round(1.2) = 1.0
	// scalar_symmetric_round(-1.5) = -2.0
	// scalar_symmetric_round(-1.2) = -1.0
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_symmetric_round(double input) RTM_NO_EXCEPT
	{
		return input >= 0.0 ? scalar_floor(input + 0.5) : scalar_ceil(input - 0.5);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the fractional part of the input.
	//////////////////////////////////////////////////////////////////////////
	inline double scalar_fraction(double value) RTM_NO_EXCEPT
	{
		return value - scalar_floor(value);
	}

	//////////////////////////////////////////////////////////////////////////
	// Safely casts an integral input into a float64 output.
	//////////////////////////////////////////////////////////////////////////
	template<typename SrcIntegralType>
	inline double scalar_safe_to_double(SrcIntegralType input) RTM_NO_EXCEPT
	{
		double input_f = double(input);
		RTM_ASSERT(SrcIntegralType(input_f) == input, "Conversion to double would result in truncation");
		return input_f;
	}

	//////////////////////////////////////////////////////////////////////////
	// SSE implementation of scalard
	//////////////////////////////////////////////////////////////////////////

#if defined(RTM_SSE2_INTRINSICS)
	//////////////////////////////////////////////////////////////////////////
	// Writes a scalar to memory.
	//////////////////////////////////////////////////////////////////////////
	inline void RTM_SIMD_CALL scalar_store(scalard input, double* output) RTM_NO_EXCEPT
	{
		_mm_store_sd(output, input);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the reciprocal of the input.
	//////////////////////////////////////////////////////////////////////////
	inline scalard RTM_SIMD_CALL scalar_reciprocal(scalard input) RTM_NO_EXCEPT
	{
		return _mm_div_sd(_mm_set1_pd(1.0), input);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the subtraction of the two scalar inputs.
	//////////////////////////////////////////////////////////////////////////
	inline scalard RTM_SIMD_CALL scalar_sub(scalard lhs, scalard rhs) RTM_NO_EXCEPT
	{
		return _mm_sub_sd(lhs, rhs);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the multiplication/addition of the three inputs: s2 + (s0 * s1)
	//////////////////////////////////////////////////////////////////////////
	inline scalard RTM_SIMD_CALL scalar_mul_add(scalard s0, scalard s1, scalard s2) RTM_NO_EXCEPT
	{
		return _mm_add_sd(_mm_mul_sd(s0, s1), s2);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the linear interpolation of the two inputs at the specified alpha.
	//////////////////////////////////////////////////////////////////////////
	inline scalard RTM_SIMD_CALL scalar_lerp(scalard start, scalard end, double alpha) RTM_NO_EXCEPT
	{
		return scalar_mul_add(scalar_sub(end, start), scalar_set(alpha), start);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the smallest of the two inputs.
	//////////////////////////////////////////////////////////////////////////
	inline scalard RTM_SIMD_CALL scalar_min(scalard lhs, scalard rhs) RTM_NO_EXCEPT
	{
		return _mm_min_sd(lhs, rhs);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the largest of the two inputs.
	//////////////////////////////////////////////////////////////////////////
	inline scalard RTM_SIMD_CALL scalar_max(scalard lhs, scalard rhs) RTM_NO_EXCEPT
	{
		return _mm_max_sd(lhs, rhs);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the absolute value of the input.
	//////////////////////////////////////////////////////////////////////////
	inline scalard RTM_SIMD_CALL scalar_abs(scalard input) RTM_NO_EXCEPT
	{
		return scalar_max(scalar_sub(_mm_setzero_pd(), input), input);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns true if both inputs are equal, false otherwise.
	//////////////////////////////////////////////////////////////////////////
	inline bool RTM_SIMD_CALL scalar_is_equal(scalard lhs, scalard rhs) RTM_NO_EXCEPT
	{
		return _mm_comieq_sd(lhs, rhs) != 0;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns true if lhs < rhs, false otherwise.
	//////////////////////////////////////////////////////////////////////////
	inline bool RTM_SIMD_CALL scalar_is_lower(scalard lhs, scalard rhs) RTM_NO_EXCEPT
	{
		return _mm_comilt_sd(lhs, rhs) != 0;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns true if both inputs are nearly equal, false otherwise.
	//////////////////////////////////////////////////////////////////////////
	inline bool scalar_near_equal(scalard lhs, scalard rhs, scalard threshold) RTM_NO_EXCEPT
	{
		return scalar_is_lower(scalar_abs(scalar_sub(lhs, rhs)), threshold);
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns true if both inputs are nearly equal, false otherwise.
	//////////////////////////////////////////////////////////////////////////
	inline bool scalar_near_equal(scalard lhs, scalard rhs) RTM_NO_EXCEPT
	{
		return scalar_near_equal(lhs, rhs, scalar_set(0.00001));
	}
#endif
}

RTM_IMPL_FILE_PRAGMA_POP

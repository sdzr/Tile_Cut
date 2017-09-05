// Copyright (c) 2014 Google, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// FarmHash, by Geoff Pike

//
// http://code.google.com/p/farmhash/


#ifndef __US_CRYPT_FARMHASH_HPP__
#define __US_CRYPT_FARMHASH_HPP__

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif
#ifndef __US_CRYPT_CITYHASH_HPP__
#include "us_crypt_cityhash.hpp"
#endif // !__US_CRYPT_CITYHASH_HPP__


#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>   // for memcpy and memset
#include <utility>

#ifndef NAMESPACE_FOR_HASH_FUNCTIONS
#define NAMESPACE_FOR_HASH_FUNCTIONS unispace
#endif

namespace NAMESPACE_FOR_HASH_FUNCTIONS {

//#if defined(FARMHASH_UINT128_T_DEFINED)
//#if defined(__clang__)
//#if !defined(uint128_t)
//#define uint128_t __uint128_t
//#endif
//#endif
//	inline uint64_t Uint128Low64(const uint128_t x) {
//		return static_cast<uint64_t>(x);
//	}
//	inline uint64_t Uint128High64(const uint128_t x) {
//		return static_cast<uint64_t>(x >> 64);
//	}
//	inline uint128_t Uint128(uint64_t lo, uint64_t hi) {
//		return lo + (((uint128_t)hi) << 64);
//	}
//#else
//	typedef std::pair<uint64_t, uint64_t> uint128_t;
//	inline uint64_t Uint128Low64(const uint128_t x) { return x.first; }
//	inline uint64_t Uint128High64(const uint128_t x) { return x.second; }
//	inline uint128_t Uint128(uint64_t lo, uint64_t hi) { return uint128_t(lo, hi); }
//#endif


	// BASIC STRING HASHING

	// Hash function for a byte array.
	// May change from time to time, may differ on different platforms, may differ
	// depending on NDEBUG.
	_US_UTIL_DLL size_t us_farm_hash(const char* s, size_t len);

	// Hash function for a byte array.  Most useful in 32-bit binaries.
	// May change from time to time, may differ on different platforms, may differ
	// depending on NDEBUG.
	_US_UTIL_DLL uint32_t us_farm_hash32(const char* s, size_t len);

	// Hash function for a byte array.  For convenience, a 32-bit seed is also
	// hashed into the result.
	// May change from time to time, may differ on different platforms, may differ
	// depending on NDEBUG.
	_US_UTIL_DLL uint32_t us_farm_hash32_with_seed(const char* s, size_t len, uint32_t seed);

	// Hash function for a byte array.
	// May change from time to time, may differ on different platforms, may differ
	// depending on NDEBUG.
	_US_UTIL_DLL uint64_t us_farm_hash64(const char* s, size_t len);

	// Hash function for a byte array.  For convenience, a 64-bit seed is also
	// hashed into the result.
	// May change from time to time, may differ on different platforms, may differ
	// depending on NDEBUG.
	_US_UTIL_DLL uint64_t us_farm_hash64_with_seed(const char* s, size_t len, uint64_t seed);

	// Hash function for a byte array.  For convenience, two seeds are also
	// hashed into the result.
	// May change from time to time, may differ on different platforms, may differ
	// depending on NDEBUG.
	_US_UTIL_DLL uint64_t us_farm_hash64_with_seeds(const char* s, size_t len,
		uint64_t seed0, uint64_t seed1);

	// Hash function for a byte array.
	// May change from time to time, may differ on different platforms, may differ
	// depending on NDEBUG.
	_US_UTIL_DLL uint128_t us_farm_hash128(const char* s, size_t len);

	// Hash function for a byte array.  For convenience, a 128-bit seed is also
	// hashed into the result.
	// May change from time to time, may differ on different platforms, may differ
	// depending on NDEBUG.
	_US_UTIL_DLL uint128_t us_farm_hash128_with_seed(const char* s, size_t len, uint128_t seed);

	// BASIC NON-STRING HASHING

	// Hash 128 input bits down to 64 bits of output.
	// This is intended to be a reasonably good hash function.
	// May change from time to time, may differ on different platforms, may differ
	// depending on NDEBUG.
	//inline uint64_t Hash128to64(uint128_t x) {
	//	// Murmur-inspired hashing.
	//	const uint64_t kMul = 0x9ddfea08eb382d69ULL;
	//	uint64_t a = (Uint128Low64(x) ^ Uint128High64(x)) * kMul;
	//	a ^= (a >> 47);
	//	uint64_t b = (Uint128High64(x) ^ a) * kMul;
	//	b ^= (b >> 47);
	//	b *= kMul;
	//	return b;
	//}

	// FINGERPRINTING (i.e., good, portable, forever-fixed hash functions)

	// Fingerprint function for a byte array.  Most useful in 32-bit binaries.
	// 计算字节数组的指纹。获取最有价值的32bit二进制。
	_US_UTIL_DLL uint32_t us_farm_fingerprint32(const char* s, size_t len);

	// Fingerprint function for a byte array.
	_US_UTIL_DLL uint64_t us_farm_fingerprint64(const char* s, size_t len);

	// Fingerprint function for a byte array.
	_US_UTIL_DLL uint128_t us_farm_fingerprint128(const char* s, size_t len);

	// This is intended to be a good fingerprinting primitive.
	// See below for more overloads.
	inline uint64_t us_farm_fingerprint(uint128_t x) {
		// Murmur-inspired hashing.
		const uint64_t kMul = 0x9ddfea08eb382d69ULL;
		uint64_t a = (Uint128Low64(x) ^ Uint128High64(x)) * kMul;
		a ^= (a >> 47);
		uint64_t b = (Uint128High64(x) ^ a) * kMul;
		b ^= (b >> 44);
		b *= kMul;
		b ^= (b >> 41);
		b *= kMul;
		return b;
	}

	// This is intended to be a good fingerprinting primitive.
	inline uint64_t us_farm_fingerprint(uint64_t x) {
		// Murmur-inspired hashing.
		const uint64_t kMul = 0x9ddfea08eb382d69ULL;
		uint64_t b = x * kMul;
		b ^= (b >> 44);
		b *= kMul;
		b ^= (b >> 41);
		b *= kMul;
		return b;
	}
}  // namespace NAMESPACE_FOR_HASH_FUNCTIONS


#endif // !__US_CRYPT_FARMHASH_HPP__



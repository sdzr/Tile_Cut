#ifndef __US_CRYPT_CITY_HASH_HPP__
#define __US_CRYPT_CITY_HASH_HPP__

#ifndef __US_UTIL_HPP__
#include "../us_util.hpp"
#endif

namespace unispace
{

	//class _US_UTIL_DLL us_crypt_cityhash
	//typedef struct { uint64_t first; uint64_t second; }uint128_t;
	typedef std::pair<uint64_t, uint64_t> uint128_t;

	inline uint64_t Uint128Low64(const uint128_t& x) { return x.first; }
	inline uint64_t Uint128High64(const uint128_t& x) { return x.second; }

	// Hash function for a byte array.
	// 对字节数组计算散列值的函数
	_US_UTIL_DLL uint64_t us_city_hash64(const char *buf, size_t len);

	// Hash function for a byte array.  For convenience, a 64-bit seed is also
	// hashed into the result.
	// 对字节数组计算散列值的函数
	// 为了方便，计算64bit的种子seed也被散列在结果中
	_US_UTIL_DLL uint64_t us_city_hash64_with_seed(const char *buf, size_t len, uint64_t seed);

	// Hash function for a byte array.  For convenience, two seeds are also
	// hashed into the result.
	_US_UTIL_DLL uint64_t us_city_hash64_with_seeds(const char *buf, size_t len,
		uint64_t seed0, uint64_t seed1);

	// Hash function for a byte array.
	_US_UTIL_DLL uint128_t us_city_hash128(const char *s, size_t len);

	// Hash function for a byte array.  For convenience, a 128-bit seed is also
	// hashed into the result.
	_US_UTIL_DLL uint128_t us_city_hash128_with_seed(const char *s, size_t len, uint128_t seed);

	// Hash 128 input bits down to 64 bits of output.
	// This is intended to be a reasonably good hash function.
	// 128位散列值降级为64位散列至
	inline uint64_t Hash128to64(const uint128_t& x) {
		// Murmur-inspired hashing.
		// Murmur 启发散列
		const uint64_t kMul = 0x9ddfea08eb382d69ULL;
		uint64_t a = (Uint128Low64(x) ^ Uint128High64(x)) * kMul;
		a ^= (a >> 47);
		uint64_t b = (Uint128High64(x) ^ a) * kMul;
		b ^= (b >> 47);
		b *= kMul;
		return b;
	}


}



#endif // !__US_CRYPT_CITY_HASH_HPP__

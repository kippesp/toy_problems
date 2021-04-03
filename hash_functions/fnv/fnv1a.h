#pragma once

#include <stdint.h>
#include <stdlib.h>

namespace Hash::Fnv1a {

using Fnv128_t = struct {
  uint64_t w64[2]; /* w64[0] is low order, w64[1] is high order word */
};

// return 128-bit result from fnv_128a_buf()
Fnv128_t hash128(const char*, size_t);

// return 64-bit result from fnv_64a_buf()
uint64_t hash64(const char*, size_t);

// return 32-bit result from fnv_32a_buf()
uint32_t hash32(const char*, size_t);

}  // namespace Hash::Fnv1a

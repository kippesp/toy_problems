#pragma once

#include <stdint.h>
#include <stdlib.h>

namespace Hash::Sip {

using SipKey_t = uint8_t[16];
using SipHalfKey_t = uint8_t[8];

using Sip128_t = struct {
  uint64_t w64[2]; /* w64[0] is low order, w64[1] is high order word */
};

/* SipHash-2-4-128 */
Sip128_t hash128(const char*, size_t, SipKey_t* = nullptr);

/* SipHash-2-4-64 */
uint64_t hash64(const char*, size_t, SipKey_t* = nullptr);

/* HalfSipHash-2-4-32 */
uint32_t hash32(const char*, size_t, SipHalfKey_t* = nullptr);

/* SipHash-4-8-128 */
Sip128_t hash128h(const char*, size_t, SipKey_t* = nullptr);

/* SipHash-4-8-64 */
uint64_t hash64h(const char*, size_t, SipKey_t* = nullptr);

/* HalfSipHash-4-8-32 */
uint32_t hash32h(const char*, size_t, SipHalfKey_t* = nullptr);

}  // namespace Hash::Sip

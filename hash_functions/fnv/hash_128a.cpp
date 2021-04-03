#include <stdint.h>
#include <stdlib.h>

#include "fnv1a.h"

using Fnv128_t = ::Hash::Fnv1a::Fnv128_t;

namespace Hash::Fnv1aImpl {

Fnv128_t fnv_128a_buf(const void* buf, size_t len, const Fnv128_t& hval)
{
  unsigned const char* bp = (unsigned const char*)buf;
  unsigned const char* be = bp + len;

  uint64_t val[4]; /* hash value in base 2^32 */
  uint64_t tmp[4]; /* tmp 128 bit value */

  const uint32_t FNV_128_PRIME_LOW = 0x13b; /* lower bits of FNV prime */
  const int FNV_128_PRIME_SHIFT = 24;       /* top FNV prime shift above 2^64 */

  /*
   * Convert Fnv128_t hval into a base 2^32 array
   */
  val[0] = hval.w64[0];
  val[1] = (val[0] >> 32);
  val[0] &= 0xffffffff;
  val[2] = hval.w64[1];
  val[3] = (val[2] >> 32);
  val[2] &= 0xffffffff;

  while (bp < be)
  {
    val[0] ^= (uint64_t)*bp++;

    /* multiply by the lowest order digit base 2^16 */
    tmp[0] = val[0] * FNV_128_PRIME_LOW;
    tmp[1] = val[1] * FNV_128_PRIME_LOW;
    tmp[2] = val[2] * FNV_128_PRIME_LOW;
    tmp[3] = val[3] * FNV_128_PRIME_LOW;

    /* multiply by the other non-zero digit */
    tmp[2] += val[0] << FNV_128_PRIME_SHIFT; /* tmp[2] += val[0] * 0x1000000 */
    tmp[3] += val[1] << FNV_128_PRIME_SHIFT; /* tmp[3] += val[1] * 0x1000000 */

    /* propagate carries */
    tmp[1] += (tmp[0] >> 32);
    val[0] = tmp[0] & 0xffffffff;
    tmp[2] += (tmp[1] >> 32);
    val[1] = tmp[1] & 0xffffffff;
    val[3] = tmp[3] + (tmp[2] >> 32);
    val[2] = tmp[2] & 0xffffffff;

    /*
     * Doing a val[3] &= 0xffffffff; is not really needed since it simply
     * removes multiples of 2^128.  We can discard these excess bits
     * outside of the loop when we convert to Fnv128_t.
     */
  }

  Fnv128_t rvalue;
  rvalue.w64[1] = ((val[3] << 32) | val[2]);
  rvalue.w64[0] = ((val[1] << 32) | val[0]);

  return rvalue;
}

}  // namespace Hash::Fnv1aImpl

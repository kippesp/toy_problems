#include "fnv1a.h"

#include <stddef.h>
#include <stdint.h>

namespace Hash {

using Fnv128_t = Fnv1a::Fnv128_t;

namespace Fnv1aImpl {

extern "C" {

#define HAVE_64BIT_LONG_LONG
#define NO_FNV_GCC_OPTIMIZATION

#include "fnv_upstream/fnv.h"
#include "fnv_upstream/hash_32a.c"
#include "fnv_upstream/hash_64a.c"
}

Fnv128_t fnv_128a_buf(const void*, size_t, const Fnv128_t&);

};  // namespace Fnv1aImpl

namespace Fnv1a {

using namespace Fnv1aImpl;

Fnv128_t hash128(const char* buffer, size_t size)
{
  const Fnv128_t FNV1A_128_INIT = {0x62b821756295c58dULL,
                                   0x6c62272e07bb0142ULL};

  Fnv128_t val = Fnv1aImpl::fnv_128a_buf(buffer, size, FNV1A_128_INIT);

  return val;
}

uint64_t hash64(const char* buffer, size_t size)
{
  uint64_t val = Fnv1aImpl::fnv_64a_buf((void*)buffer, size, FNV1A_64_INIT);

  return val;
}

uint32_t hash32(const char* buffer, size_t size)
{
  uint64_t val = Fnv1aImpl::fnv_32a_buf((void*)buffer, size, FNV1_32A_INIT);

  return val;
}

};  // namespace Fnv1a

};  // namespace Hash

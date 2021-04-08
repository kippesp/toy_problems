#include "sip.h"

using namespace std;

namespace Hash {

namespace SipImpl {

extern "C" {

/* SipHash-2-4 */

#define siphash siphash_default

#include "siphash_upstream/siphash.c"

#undef siphash

#undef cROUNDS
#undef dROUNDS
#undef ROTL
#undef SIPROUND

/* SipHash-4-8 */

#define cROUNDS 4
#define dROUNDS 8
#define siphash siphash_hardened

#include "siphash_upstream/siphash.c"

#undef siphash

#undef cROUNDS
#undef dROUNDS
#undef ROTL
#undef SIPROUND

/* HalfSipHash-2-4 */

#define halfsiphash halfsiphash_default

#include "siphash_upstream/halfsiphash.c"

#undef halfsiphash

#undef cROUNDS
#undef dROUNDS
#undef ROTL
#undef SIPROUND

/* HalfSipHash-4-8 */

#define cROUNDS 4
#define dROUNDS 8
#define halfsiphash halfsiphash_hardened

#include "siphash_upstream/halfsiphash.c"

#undef halfsiphash

#undef cROUNDS
#undef dROUNDS
#undef ROTL
#undef SIPROUND
}

}  // namespace SipImpl

namespace Sip {

/* my default 128-bit key */
const SipKey_t default_key = {0x44, 0x61, 0x73, 0x68, 0x49, 0x73, 0x41, 0x43,
                              0x75, 0x74, 0x65, 0x50, 0x6f, 0x75, 0x63, 0x68};

/* my default 64-bit key */
const SipHalfKey_t default_halfkey = {0x46, 0x61, 0x73, 0x74,
                                      0x44, 0x61, 0x73, 0x68};

Sip128_t hash128(const char* buffer, size_t size, SipKey_t* user_key)
{
  uint8_t* key;

  if (user_key == nullptr)
    key = (uint8_t*)&default_key[0];
  else
    key = *user_key;
  uint8_t out[16];

  SipImpl::siphash_default(buffer, size, key, out, 16);

  Sip128_t res;

  for (int i = 0; i < 8; i++)
  {
    res.w64[1] = res.w64[1] << 8 | out[i];
    res.w64[0] = res.w64[0] << 8 | out[8 + i];
  }

  return res;
}

Sip128_t hash128h(const char* buffer, size_t size, SipKey_t* user_key)
{
  uint8_t* key;

  if (user_key == nullptr)
    key = (uint8_t*)&default_key[0];
  else
    key = *user_key;
  uint8_t out[16];

  SipImpl::siphash_hardened(buffer, size, key, out, 16);

  Sip128_t res;

  for (int i = 0; i < 8; i++)
  {
    res.w64[1] = res.w64[1] << 8 | out[i];
    res.w64[0] = res.w64[0] << 8 | out[8 + i];
  }

  return res;
}

uint64_t hash64(const char* buffer, size_t size, SipKey_t* user_key)
{
  uint8_t* key;

  if (user_key == nullptr)
    key = (uint8_t*)&default_key[0];
  else
    key = *user_key;
  uint8_t out[8];

  SipImpl::siphash_default(buffer, size, key, out, 8);

  uint64_t res;

  for (int i = 0; i < 8; i++) res = res << 8 | out[i];

  return res;
}

uint64_t hash64h(const char* buffer, size_t size, SipKey_t* user_key)
{
  uint8_t* key;

  if (user_key == nullptr)
    key = (uint8_t*)&default_key[0];
  else
    key = *user_key;
  uint8_t out[8];

  SipImpl::siphash_hardened(buffer, size, key, out, 8);

  uint64_t res;

  for (int i = 0; i < 8; i++) res = res << 8 | out[i];

  return res;
}

uint32_t hash32(const char* buffer, size_t size, SipHalfKey_t* user_key)
{
  uint8_t* key;

  if (user_key == nullptr)
    key = (uint8_t*)&default_halfkey[0];
  else
    key = *user_key;
  uint8_t out[8];

  SipImpl::halfsiphash_default(buffer, size, key, out, 4);

  uint32_t res;

  for (int i = 0; i < 4; i++) res = res << 8 | out[i];

  return res;
}

uint32_t hash32h(const char* buffer, size_t size, SipHalfKey_t* user_key)
{
  uint8_t* key;

  if (user_key == nullptr)
    key = (uint8_t*)&default_halfkey[0];
  else
    key = *user_key;
  uint8_t out[8];

  SipImpl::halfsiphash_hardened(buffer, size, key, out, 4);

  uint32_t res;

  for (int i = 0; i < 4; i++) res = res << 8 | out[i];

  return res;
}

}  // namespace Sip

}  // namespace Hash

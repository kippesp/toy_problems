#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <iostream>

#include "fnv/fnv1a.h"

using namespace std;

int main(int argc, char* argv[])
{
  // const char* b = "1234567890abcdefg";
  // val: b6e2fe55b55a0d1f90bbc6ab04080924
  //
  // const char* b = "abcd";
  // val: 696f7cc66e757277b806e97644f1b9e5
  //
  // const char* b = "a";
  // val: d228cb696f1a8caf78912b704e4a8964
  //
  const char* b = "abcdefghijklmnopqrstuvwxyz1234567890";
  // val: 9c3de1c5da11148ef7c569160e6d4eeb

#if 0
  uint64_t hash = Hash::Fnv1a::hash64(b, strlen(b));
  // uint64_t hash = Hash::Fnv1a::hash64str(b);

  printf("%0llx\n", hash);
#endif

  //uint32_t hash = Hash::Fnv1a::hash32(b, strlen(b));
  // uint64_t hash = Hash::Fnv1a::hash64str(b);

  //printf("%0x\n", hash);

  auto a = Hash::Fnv1a::hash128(b, strlen(b));

  cout << "hi: " << hex << a.w64[1] << endl;
  cout << "lo: " << hex << a.w64[0] << endl;

  return 0;
}

/*
  tc0000.cpp
  ------------------------------------------------------------------------------
  Checkup for a Block of Memory, Containing a Repeated Single Byte
  ------------------------------------------------------------------------------
  Test #0 - Basic Random Tests for Success and Failure
  ------------------------------------------------------------------------------
  Ver  1.00  Initial version                                        January 24
  Ver  2.00  Add Toby Speight 'mem_eq' testing                      January 24
  ------------------------------------------------------------------------------
  Copyright (c) 2024 A.Yakovlev
*/

#include <iostream>
#include <random>

#include "compare.hpp"

using std::cout;
using std::endl;

bool constexpr USE_MEM_EQ = true;

unsigned constexpr NUM_REPEATS = 20;
unsigned constexpr MAX_SIZE = 10000;

bool mem_eq(const void *const p, const char c, const size_t len)
{
  if (!len) { return true; }
  auto const mem = static_cast<const char*>(p);
  if (*mem != c) { return false; }
  return memcmp(mem, mem+1, len-1) == 0;
}

inline auto compare(const unsigned char* const PTR, unsigned char const BYTE, std::size_t const N)
{
  return USE_MEM_EQ ? mem_eq(PTR, BYTE, N) : compare<unsigned long>(PTR, BYTE, N);
}

int main()
{
  std::random_device rd;
  std::mt19937 g(rd());
  for (auto i = 0U; i < NUM_REPEATS; ++i)
  {
    auto const size = g() % MAX_SIZE;
    cout << size;
    auto const ptr = new unsigned char[size];
    memset(ptr, 'Q', size);
    auto const pos = g() % size;
    cout << '\t' << pos;
    auto const success = compare(ptr + pos, 'Q', size - pos);
    if (not success) {cout << "Test failed!!!" << endl; break;}
    cout << '\t' << success;
    auto const posToFail = pos + g() % (size - pos);
    cout << '\t' << posToFail;
    ptr[posToFail] = '0';
    auto const fail = compare<unsigned long>(ptr + pos, 'Q', size - pos);
    if (fail) {cout << "Test failed!!!" << endl; break;}
    cout << '\t' << fail;
    delete[] ptr;
    cout << endl;
  }
}

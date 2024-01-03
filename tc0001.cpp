/*
  tc0001.cpp
  ------------------------------------------------------------------------------
  Checkup for a Block of Memory, Containing a Repeated Single Byte
  ------------------------------------------------------------------------------
  Test #1 - Performance Tests for Various Unsigned Types
  ------------------------------------------------------------------------------
  Ver  1.00  Initial version                                         January 24
  ------------------------------------------------------------------------------
  Copyright (c) 2024 A.Yakovlev
*/

#include <chrono>
#include <iostream>

#include "compare.hpp"

using Clock = std::chrono::steady_clock;
using Duration = std::chrono::duration<double>;

using std::cout;
using std::endl;

unsigned constexpr MAX_SIZE = 100000;

template <typename T>
auto test()
{
  auto const rc = new bool[MAX_SIZE / 2];
  auto const ptr = new unsigned char[MAX_SIZE];
  memset(ptr, 'Q', MAX_SIZE);
  // ------ timed loop with various memory block sizes 
  auto const tStart = Clock::now();
  for (auto i = 0U; i < MAX_SIZE / 2; ++i)
  {
    rc[i] = compare<T>(ptr + i, 'Q', MAX_SIZE - 2 * i);
  }
  Duration const sec = Clock::now() - tStart;
  // ------ all results must be 'true'
  for (auto i = 0U; i < MAX_SIZE / 2; ++i)
  {
    if (not rc[i])
    {
      cout << "Test failed!!!" << endl;
      break;
    }
  }
  delete[] ptr;
  delete[] rc;
  return sec.count();
}

int main()
{
  cout << "Time for 'unsigned char'  = " << test<unsigned char>() << endl;
  cout << "Time for 'unsigned short' = " << test<unsigned short>() << endl;
  cout << "Time for 'unsigned'       = " << test<unsigned>() << endl;
  cout << "Time for 'unsigned long'  = " << test<unsigned long>() << endl;
}

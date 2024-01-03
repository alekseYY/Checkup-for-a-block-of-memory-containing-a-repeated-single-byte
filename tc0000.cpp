/*
  tc0000.cpp
  ------------------------------------------------------------------------------
  Checkup for a Block of Memory, Containing a Repeated Single Byte
  ------------------------------------------------------------------------------
  Test #0 - Basic Random Tests for Success and Failure
  ------------------------------------------------------------------------------
  Ver  1.00  Initial version                                        January 24
  ------------------------------------------------------------------------------
  Copyright (c) 2024 A.Yakovlev
*/

#include <iostream>
#include <random>

#include "compare.hpp"

using std::cout;
using std::endl;

unsigned constexpr NUM_REPEATS = 20;
unsigned constexpr MAX_SIZE = 10000;

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
    auto const success = compare<unsigned long>(ptr + pos, 'Q', size - pos);
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

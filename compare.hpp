/*
  compare.hpp
  ------------------------------------------------------------------------------
  Checkup for a Block of Memory, Containing a Repeated Single Byte
  ------------------------------------------------------------------------------
  Ver  1.00  Initial version                                        January 24
  ------------------------------------------------------------------------------
  Copyright (c) 2024 A.Yakovlev
*/

#pragma once

#include <cstring>
#include <memory>

template <typename T>
inline auto repeatedByte(unsigned char const BYTE)
{
  T res = 0;
  memset(&res, BYTE, sizeof(T));
  return res;
}

inline auto compareBytes(const unsigned char* PTR, unsigned char const BYTE, std::size_t const N)
{
  std::size_t i = 0;
  while (i < N && *PTR == BYTE) {++i; ++PTR;}
  return (i >= N);
}

template <typename T>
auto compare(const void* const PTR, unsigned char const BYTE, std::size_t const N)
{
  if (N > 2 * sizeof(T))
  {
    auto ptrAligned = const_cast<void*>(PTR);
    std::size_t sizeAligned = N;
    std::align(alignof(T), sizeof(T), ptrAligned, sizeAligned);
    if (compareBytes(static_cast<const unsigned char*>(PTR), BYTE, N - sizeAligned))
    {
      auto const value = repeatedByte<T>(BYTE);
      auto const n = sizeAligned / sizeof(T);
      auto ptrT = static_cast<const T*>(ptrAligned);
      std::size_t i = 0;
      while (i < n && *ptrT == value) {++i; ++ptrT;}
      if (i < n)
      {
        return false;
      }
      else if (sizeAligned % sizeof(T) > 0)
      {
        return compareBytes(reinterpret_cast<const unsigned char*>(ptrT), BYTE, sizeAligned - n * sizeof(T));
      }
      else
      {
        return true;
      }
    }
    else
    {
      return false;
    }
  }
  else
  {
    return compareBytes(static_cast<const unsigned char*>(PTR), BYTE, N);
  }
}

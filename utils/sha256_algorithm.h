#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <bitset>

class sha256
{
private:
public:
  // sigma family functions
  std::string sigma_0(std::string);
  std::string sigma_1(std::string);

  // bits shift and rotatatory functions
  std::string right_shift(std::string, int);
  std::string right_rotate_shift(std::string, int);

  // xor implementation
  std::string re_xor(std::string, std::string);

  // other functions
  std::string ch_func(std::string, std::string, std::string);
  std::string maj_func(std::string, std::string, std::string);
};
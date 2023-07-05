#pragma once
#include "../utils/preprocessing.h"
#include "../utils/sha256_algorithm.h"
#include "../utils/compression.h"
#include <vector>
#include <iostream>
#include <bitset>

class hashing
{
public:
  std::string object;
  std::string hash;
  std::string get_hash();
};
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>

class pre_process
{
private:
  std::string bin_message;

public:
  int PRE_BITS = 448;
  int POST_BITS = 64;
  int bin_len;
  std::string message_box;

  void set_bin_message(std::string);
  void set_message_box_pre();
  void set_message_box_post();
  std::string confirm_process();
  std::string int_to_bit(int);
  std::string encode_message(std::string);
};
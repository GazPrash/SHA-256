#include "preprocessing.h"

void pre_process ::set_bin_message(std::string message)
{
  message = encode_message(message);
  bin_message = message;
  message_box = message;
  bin_len = message.length();
}

void pre_process ::set_message_box_pre()
{
  int suffix_adj_len = PRE_BITS - bin_len - 1;
  message_box += '1';
  while (suffix_adj_len > 0)
  {
    message_box += '0';
    suffix_adj_len--;
  }
}

void pre_process ::set_message_box_post()
{
  std::string len_bits = int_to_bit(bin_len);

  int bits = len_bits.length();
  while (bits < POST_BITS)
  {
    len_bits.insert(len_bits.begin(), '0');
    bits++;
  }

  message_box += len_bits;
}

std::string pre_process ::confirm_process()
{
  if (message_box.length() == 512)
  {
    return message_box;
  }

  return bin_message; // raise some error for indication TODO.
}

std::string pre_process ::int_to_bit(int x)
{
  std::string out;
  while (x > 0)
  {
    out += (x % 2 == 0 ? "0" : "1");
    x /= 2;
  }
  reverse(out.begin(), out.end());

  return out;
}

std::string pre_process ::encode_message(std::string message)
{
  std::string out_stream;
  for (std::size_t i = 0; i < message.size(); ++i)
  {
    out_stream += std::bitset<8>(message.c_str()[i]).to_string();
  }
  return out_stream;
}
#include "hashing.h"

std::string hashing ::get_hash()
{
  pre_process val1;
  val1.set_bin_message(object);
  val1.set_message_box_pre();
  val1.set_message_box_post();
  std::string message_box1 = val1.confirm_process();

  std::vector<std::string> message_schedule;
  int word_bit = 0;

  while (word_bit < 512)
  {
    message_schedule.push_back(message_box1.substr(word_bit, 32));
    word_bit += 32;
  }

  int t = 16;
  while (t < 64)
  {
    // sigma_1 (t-2) + (t-7) + sigma_0 (t-15) + (t-16)
    sha256 algorithm;

    std::string a = algorithm.sigma_1(message_schedule[t - 2]);
    std::string b = message_schedule[t - 7];
    std::string c = algorithm.sigma_0(message_schedule[t - 15]);
    std::string d = message_schedule[t - 16];

    unsigned long big = stoul(a, nullptr, 2) +
                        stoul(b, nullptr, 2) +
                        stoul(c, nullptr, 2) +
                        stoul(d, nullptr, 2);
    // big %= (long)pow(2, 32);
    std::string bin_value = std::bitset<32>(big).to_string();
    message_schedule.push_back(bin_value);
    t++;
  }

  hash_compression hcomp;
  hcomp.prepare_states(message_schedule);
  hash = hcomp.hex_digest();

  return hash;
}

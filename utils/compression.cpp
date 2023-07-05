#include "compression.h"

hash_compression ::hash_compression()
{
  for (int k : state_registers_int)
  {
    double diff = abs(long(sqrt(k)) - double(sqrt(k)));
    unsigned long mid_int = diff * (long long)(pow(2, 32));
    state_registers_bin.push_back(std::bitset<32>(mid_int).to_string());
  }

  for (std::string hex_val : k_constants_hex)
  {
    stringstream ss;
    ss << std::hex << ("0x" + hex_val);
    unsigned t;
    ss >> t;
    bitset<32> bset(t);
    k_constants_bin.push_back(bset.to_string());
  }
}

void hash_compression ::prepare_states(vector<std::string> &message_schedule)
{
  // t1 = sigma_1 (e) + ch(e, f, g) + h + k0 + wo
  // t2 = sigma_0 (a) + maj(a, b c)

  sha256 algorithm;
  int rounds = 0;

  std::vector<std::string> temp_states(8);
  for (int i = 0; i < 8; i++)
  {
    temp_states[i] = state_registers_bin[i];
  }

  // t1 & t2 calculation
  while (rounds <= 63)
  {
    auto sigma_ex = [&](std::string wi, int a, int b, int c) -> std::string
    {
      std::string w1 = algorithm.right_rotate_shift(wi, a);
      std::string w2 = algorithm.right_rotate_shift(wi, b);
      std::string w3 = algorithm.right_rotate_shift(wi, c);

      return (algorithm.re_xor(w3, algorithm.re_xor(w1, w2)));
    };
    std::string s1_e = sigma_ex(temp_states[4], 6, 11, 25);
    std::string ch_efg = algorithm.ch_func(temp_states[4],
                                           temp_states[5],
                                           temp_states[6]);

    std::string s0_a = sigma_ex(temp_states[0], 2, 13, 22);
    std::string maj_abc = algorithm.maj_func(temp_states[0],
                                             temp_states[1],
                                             temp_states[2]);

    unsigned long mid_int1 = (stoul(s1_e, nullptr, 2) +
                              stoul(ch_efg, nullptr, 2) +
                              stoul(temp_states[7], nullptr, 2) +
                              stoul(k_constants_bin[rounds], nullptr, 2) +
                              stoul(message_schedule[rounds], nullptr, 2)) %
                             (long long)(pow(2, 32));

    unsigned long mid_int2 = (stoul(s0_a, nullptr, 2) +
                              stoul(maj_abc, nullptr, 2)) %
                             (long long)(pow(2, 32));

    unsigned long mid_int = (mid_int1 + mid_int2) % (long long)(pow(2, 32));

    std::string new_state = std::bitset<32>(mid_int).to_string();
    temp_states.pop_back();
    temp_states.insert(temp_states.begin(), new_state);
    unsigned long mid_int3 = (stoul(temp_states[4], nullptr, 2) + mid_int1) % (long long)(pow(2, 32));
    temp_states[4] = std::bitset<32>(mid_int3).to_string();
    rounds++;
  }

  for (int i = 0; i < 8; i++)
  {
    unsigned long temp_int = (stoul(temp_states[i], nullptr, 2) +
                              stoul(state_registers_bin[i], nullptr, 2)) %
                             (long long)(pow(2, 32));
    state_registers_bin[i] = std::bitset<32>(temp_int).to_string();
  }
}

std::string hash_compression ::hex_digest()
{
  std::string hash;
  unsigned long mid_intt = 0;
  int temp = 0;
  for (std::string state : state_registers_bin)
  {
    mid_intt = stoul(state, nullptr, 2);
    std::stringstream ss;
    ss << std::hex << mid_intt;
    hash += ss.str();
  }

  return hash;
}
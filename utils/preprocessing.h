#pragma once
#include"to_bin.h"
#include<iostream>
#include<vector>

class pre_process{
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

};

void pre_process :: set_bin_message(std::string message){
    message = encode_message(message);
    bin_message = message;
    message_box = message;
    bin_len = message.length();
    
}

void pre_process :: set_message_box_pre(){
    int suffix_adj_len = PRE_BITS - bin_len - 1;
    message_box += '1';
    while (suffix_adj_len > 0){
        message_box += '0';
        suffix_adj_len--;
    }

}

void pre_process :: set_message_box_post(){
    std::string len_bits = int_to_bit(bin_len);

    int bits = len_bits.length();
    while (bits < POST_BITS){
        len_bits.insert(len_bits.begin(), '0');
        bits++;
    }

    message_box += len_bits;
}

std::string pre_process :: confirm_process(){
    if (message_box.length() == 512){
        return message_box;
    }

    return bin_message; // raise some error for indication TODO.
}

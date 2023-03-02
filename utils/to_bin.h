// Program to convert strings to binary based on the ASCII Conversion Chart.
#pragma once
#include<string>
#include<bitset>
#include<algorithm>


std::string int_to_bit(int x){
    std::string out;
    while ( x > 0){
        out += (x%2 == 0 ? "0" : "1");
        x /= 2;
    }
    reverse(out.begin(), out.end());
    
    return out;
}

std::string encode_message(std::string message){
    std::string out_stream;
    for (std::size_t i = 0; i < message.size(); ++i){
        out_stream += std::bitset<8>(message.c_str()[i]).to_string();
    }
    return out_stream;

}
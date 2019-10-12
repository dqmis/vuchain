//
// Created by Dominykas  on 14/09/2019.
//

#include "HASH.h"

void HASH::string_to_binary(std::string st_val) {
    std::string binary_rep;
    for(char c: st_val) {
        binary_rep = std::bitset<8>(int(c)).to_string();
        for (char b: binary_rep)
            bin_val.push_back(int(b) - 48);
    }
}

void HASH::init_key(std::vector<int>& key) {
    key.reserve(32);
    for(int i = 0; i < 4; i++) {
        std::string bin = std::bitset<8>(std::rand()).to_string();
        for(char& b: bin)
            key.push_back(int(b) - 48);
    }
}

void HASH::shuffle_bits() {
    int a, b;
    for (int i = 0; i < bin_val.size() - 8; i++) {
        if(i % 2 == 0) {
            bin_val[i + 8] = bin_val[i] ^ bin_val[i + 8];
        } else {
            bin_val[i] = bin_val[i] ^ bin_val[i + 8];
        }
    }
    for(int i = 0; i < bin_val.size() / 2; i++) {
        a = bin_val[i];
        b = bin_val[bin_val.size() - i - 1];
        bin_val[i] = a ^ b;
        bin_val[bin_val.size() - i - 1] = a | b;
    }
}

std::string HASH::mul_bites() {
    std::vector<int> res;
    res.reserve(512);

    for (int c = 0; c < bin_val.size() / 2; c += 512) {
        for(int i = 0; i < 16; i++) {
            std::transform(
                    keys[i].begin(),
                    keys[i].end(),
                    bin_val.begin() + c + (i * 32),
                    std::back_inserter(res),
                    std::bit_xor<int>());
        }
        for (int k = 0; k < 16; k++) {
            keys[k].assign(res.begin() + k, res.begin() + 16 + k);
        }
    }
    std::stringstream result;
    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(result));
    return result.str();
}

std::string HASH::string_to_hex(std::string bin) {
    std::string res = "";
    for (int i = 0; i < 512; i += 4) {
        std::stringstream hex;
        std::bitset<4> set(bin.substr(i, 4));
        hex << std::hex << set.to_ulong();
        res += hex.str();
    }
    return res;
}

void HASH::padding(std::vector<int>& bin) {
    std::string binary_val = std::bitset<8>(bin.size()).to_string();
    std::vector<int> len_bin(64 - binary_val.length(), 0);
    int chunks = 512 * (bin.size() / 512);
    for(char& c: binary_val)
        len_bin.push_back(int(c) - 48);
    bin.reserve(((bin.size() / 512) + 1) * 512);
    if(bin.size() - chunks < 448) {
        bin.push_back(1);
        while (bin.size() - chunks != 448)
            bin.push_back(0);
    }
    bin.insert(bin.end(), len_bin.begin(), len_bin.end());
}

std::string vu::hash(std::string st) {
    HASH _hash(42);
    return _hash.hash(st);
}

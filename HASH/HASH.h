//
// Created by Dominykas  on 14/09/2019.
//

#ifndef VUHASH_HASH_H
#define VUHASH_HASH_H

#include <string>
#include <vector>
#include <cmath>
#include <bitset>
#include <iostream>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <functional>
#include <sstream>

class HASH {
private:
    void padding(std::vector<int>& bin);
    void string_to_binary(std::string st_val);
    void init_key(std::vector<int>& key);
    void shuffle_bits();
    std::string string_to_hex(std::string bin);
    std::string mul_bites();

    std::vector<std::vector<int>> keys;
    std::vector<int> bin_val;
public:
    HASH(int rand_const_ = 42) {
        std::srand(rand_const_);
        keys.reserve(16);
        for(int i = 0; i < 16; i++) {
            std::vector<int> key;
            init_key(key);
            keys.push_back(key);
        }
    }
    std::string hash(const std::string st) {
        string_to_binary(st);
        if (!bin_val.size() % 512 == 0) padding(bin_val);
        shuffle_bits();
        return string_to_hex(mul_bites());
    }
};

namespace vu {
    std::string hash(std::string st);
};


#endif //VUHASH_HASH_H

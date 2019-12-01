//
// Created by Dominykas  on 12/10/2019.
//

#ifndef VUCHAIN_BLOCK_H
#define VUCHAIN_BLOCK_H

#include "main.h"
#include "./HASH/sha256.h"
#include <ctime>

class Block {
private:
    std::string prev_hash;
    std::string thash;
    std::string hash;
    int nonce = 0;
    int timestamp;
public:
    Block(std::string prev_hash_, std::string t_hash) {
        timestamp = std::time(0);
        prev_hash = prev_hash_;
        thash = t_hash;
    }

    bool mine(int difficulty, int nonce_try = 40000, double mine_time = 10) {
        std::string m_hash = sha256(std::to_string(nonce) + thash + prev_hash + std::to_string(timestamp));
        std::string dif_(difficulty, '0');
        clock_t begin = clock();
        while((m_hash > prev_hash && m_hash.substr(0, difficulty) == dif_) == false) {
            nonce++;
            m_hash = sha256(std::to_string(nonce) + thash + prev_hash + std::to_string(timestamp));

            if (nonce >= nonce_try && (double(clock() - begin) > mine_time)) return false;
        }
        hash = m_hash;
        return true;
    }
    std::string get_hash() { return hash; }
    int get_nonce() { return nonce; }
};

#endif //VUCHAIN_BLOCK_H

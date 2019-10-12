//
// Created by Dominykas  on 12/10/2019.
//

#ifndef VUCHAIN_BLOCK_H
#define VUCHAIN_BLOCK_H

#include "main.h"

class Block {
private:
    std::string prev_hash;
    std::string thash;
    std::string hash;
    int nonce;
    int timestamp;
public:
    Block() {};
};

#endif //VUCHAIN_BLOCK_H

//
// Created by Dominykas  on 12/10/2019.
//

#ifndef VUCHAIN_BLOCK_H
#define VUCHAIN_BLOCK_H

#include "main.h"
#include "transaction_list.h"

class Block {
private:
    std::string prev_hash;
    std::string thash;
    std::string hash;
    int nonce = 0;
    int timestamp;
    TransactionList *tl;
    //float difficulty;
public:
    Block(std::string prev_hash_, TransactionList *tl_) {
        timestamp = std::time(0);
        prev_hash = prev_hash_;
        thash = tl_->get_mhash();
        tl = tl_;
    }
    void mine() {
        while(vu::hash(
                std::to_string(nonce) +
                thash +
                prev_hash
                ) >= prev_hash) {
            nonce ++;
        }
        hash = vu::hash(std::to_string(nonce) + thash + prev_hash);
        tl->appproved();
    }
    std::string get_hash() { return hash; }
    int get_nonce() { return nonce; }
};

#endif //VUCHAIN_BLOCK_H

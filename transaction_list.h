//
// Created by Dominykas  on 12/10/2019.
//

#ifndef VUCHAIN_TRANSACTION_LIST_H
#define VUCHAIN_TRANSACTION_LIST_H

#include "main.h"
#include "transaction.h"
#include "./HASH/sha256.h"
#include <bitcoin/bitcoin.hpp>

class TransactionList {
private:
    bc::hash_list merkle;
    bc::hash_digest mhash;
public:
    void add_transaction(std::string hash_) {
        char hash[65] = "";
        for (int i = 0; i < 65; i++)
            hash[i] = hash_[i];
        merkle.push_back(bc::hash_literal(hash));
    }

    void create_merkle() {
        if (merkle.empty()) {
            mhash = bc::null_hash;
            return;
        }
        else if (merkle.size() == 1) {
            mhash = merkle[0];
            return;
        }

        while (merkle.size() > 1)
        {
            if (merkle.size() % 2 != 0)
                merkle.push_back(merkle.back());
            assert(merkle.size() % 2 == 0);

            bc::hash_list new_merkle;
            for (auto it = merkle.begin(); it != merkle.end(); it += 2)
            {
                bc::data_chunk concat_data(bc::hash_size * 2);
                auto concat = bc::serializer<
                        decltype(concat_data.begin())>(concat_data.begin());
                concat.write_hash(*it);
                concat.write_hash(*(it + 1));
                bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
                new_merkle.push_back(new_root);
            }
            merkle = new_merkle;
        }
        mhash = merkle[0];
    }

    std::string get_mhash() { return bc::encode_base16(mhash); }
};

#endif //VUCHAIN_TRANSACTION_LIST_H

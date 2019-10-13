//
// Created by Dominykas  on 12/10/2019.
//

#ifndef VUCHAIN_TRANSACTION_LIST_H
#define VUCHAIN_TRANSACTION_LIST_H

#include "main.h"
#include "transaction.h"

class TransactionList {
private:
    std::vector<Transaction> tlist;
    float award = 0;
    std::string mhash = "";
public:
    void add_transaction(Transaction & t) {
        tlist.push_back(t);
        mhash = vu::hash(mhash + t.get_hash());
        award += t.get_tvalue() * 0.01;
    }
    std::string get_mhash() { return mhash; }
    float get_award() { return award; }
    void appproved() {
        for(Transaction & t: tlist) {
            if (t.valid()) {
                t.approved();
            }
        }
    }
    void clear() {
        mhash = "";
        award = 0;
        tlist.clear();
    }
};

#endif //VUCHAIN_TRANSACTION_LIST_H

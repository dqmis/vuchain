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
        if (t.valid()) {
            tlist.push_back(t);
            award += t.get_tvalue() * 0.01;
            mhash = vu::hash(mhash + t.get_hash());
        }
    }
    std::string get_mhash() { return mhash; }
    float get_award() { return award; }
    void appproved() {
        for(Transaction & t: tlist)
            t.approved();
    }
};

#endif //VUCHAIN_TRANSACTION_LIST_H

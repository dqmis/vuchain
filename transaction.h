//
// Created by Dominykas  on 12/10/2019.
//

#ifndef VUCHAIN_TRANSACTION_H
#define VUCHAIN_TRANSACTION_H

#include "main.h"
#include "user.h"

class Transaction {
private:
    std::string rhash;
    std::string shash;
    float tvalue;
    User *ru;
    User *su;
    int status = 0;
public:
    Transaction(User *ru_, User *su_, float tvalue_) {
        ru = ru_;
        su = su_;
        rhash = ru->get_pkey();
        shash = su->get_pkey();
        tvalue = tvalue_;
    }
    std::string get_hash() { return vu::hash(rhash + shash + std::to_string(tvalue)); }
    float get_tvalue() { return tvalue; }
    bool valid() { return su->get_balance() >= tvalue; };
    void approved() {
        if (status == 0) {
            su->pay(tvalue);
            ru->receive(tvalue);
            status = 1;
        }
    }
};


#endif //VUCHAIN_TRANSACTION_H

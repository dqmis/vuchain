//
// Created by Dominykas  on 12/10/2019.
//

#ifndef VUCHAIN_USER_H
#define VUCHAIN_USER_H

#include "main.h"

class User {
private:
    std::string name;
    std::string pkey;
    float balance;
public:
    User() {}
    User(std::string name_, float balance_) {
        std::random_device rd;
        std::mt19937 generator(rd());

        name = name_;
        balance = balance_;
        pkey = vu::hash(name + std::to_string(std::time(0)) + std::to_string(generator()));
    }
    std::string get_name() { return name; }
    std::string get_pkey() { return pkey; }
    float get_balance() { return balance; }
    void pay(float am) { balance -= am; }
    void receive(float am) { balance += am; }
};


#endif //VUCHAIN_USER_H

#include <iostream>
#include "user.h"
#include "transaction.h"
#include "transaction_list.h"
#include "block.h"

int main() {
    TransactionList tl;

    User u2("shrek", 69);
    User u1("satoshi", 10);
    Transaction t(&u1, &u2, 55);
    tl.add_transaction(t);

    Block gen_block(
            "09168ee94ed042cb6bdc3111290f57aed4d032dafef648eba250ac3af8dad98d42c6ab2e40fd7f2d68c5e0737521ca9f9728a2f259b7ff1464617244f1d57f3",
            &tl);
    gen_block.mine();
    tl.clear();

    std::vector<User> users;
    users.reserve(1000);
    std::vector<Transaction> transactions;
    transactions.reserve(1000);
    for (int i = 0; i < 1000; i++) {
        User u("name" + std::to_string(i), rand() % 1000 + 1);
        users.push_back(u);
    }
    for (int i = 0; i < 1000; i++) {
        User u1 = users[rand() % 1000];
        User u2 = users[rand() % 1000];
        Transaction t(&u1, &u2, u2.get_balance() * 0.2);
        transactions.push_back(t);
    }

    Block b(gen_block.get_hash(), &tl);
    while(transactions.size() > 0) {
        for (int i = 0; i < 100; i++) {
            tl.add_transaction(transactions[i]);
        }
        std::cout << tl.get_mhash() << std::endl;
        b.mine();
        std::cout << b.get_hash() << std::endl;
        tl.clear();
        transactions.erase(transactions.begin(), transactions.begin() + 100);
        std::string prev_hash = b.get_hash();
        Block b(prev_hash, &tl);
    }
    return 0;
}
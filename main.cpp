#include <iostream>
#include "user.h"
#include "transaction.h"
#include "blockchain.h"

int main() {
    std::srand(time(0));
    Blockchain vuchain(0.001, 1);

    std::vector<User> users;
    users.reserve(1000);

    for (int i = 0; i < 1000; i++) {
        User u("name" + std::to_string(i), rand() % 1000 + 1);
        users.push_back(u);
    }

    int u1, u2;
    for (int i = 0; i < 1000; i++) {
        u1 = rand() % 1000;
        u2 = rand() % 1000;
        Transaction t(&users[u1], &users[u2], users[u2].get_balance() * 0.01);
        vuchain.add_transaction(t);
    }

    std::cout << users[0].get_balance() << std::endl;
    while (vuchain.get_transaction_count() > 10) {
        vuchain.mine(users[0], 400000, 5);
    }
    std::cout << users[0].get_balance() << std::endl;

    return 0;
}
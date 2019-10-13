#include <iostream>
#include "user.h"
#include "transaction.h"
#include "transaction_list.h"
#include "block.h"

int main() {
    User u2("shrek", 69);
    User u1("satoshi", 10);
    Transaction t(&u1, &u2, 55);
    TransactionList tl;
    tl.add_transaction(t);

    Block gen_block("09168ee94ed042cb6bdc3111290f57aed4d032dafef648eba250ac3af8dad98d42c6ab2e40fd7f2d68c5e0737521ca9f9728a2f259b7ff1464617244f1d57f3", &tl);
    gen_block.mine();
    tl.clear();

    std::cout << u1.get_name() << " " << u1.get_balance() << std::endl;
    std::cout << u2.get_name() << " " << u2.get_balance() << std::endl;

    Transaction t1(&u1, &u2, 10);
    tl.add_transaction(t1);

    Block block1(gen_block.get_hash(), &tl);
    block1.mine();

    std::cout << u1.get_name() << " " << u1.get_balance() << std::endl;
    std::cout << u2.get_name() << " " << u2.get_balance() << std::endl;

    std::cout << gen_block.get_hash() << std::endl;
    std::cout << block1.get_hash() << std::endl;add
    return 0;
}
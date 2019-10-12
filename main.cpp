#include <iostream>
#include "user.h"
#include "transaction.h"
#include "transaction_list.h"

int main() {
    User user1("dominykas", 100);
    User user2("ne dominykas", 12);
    User user3("opa dominykas", 39);
    Transaction t1(&user2, &user1, user1.get_balance());
    Transaction t2(&user1, &user3, 15);
    TransactionList w1;
    w1.add_transaction(t1);

    std::cout << user1.get_name() << " " << user1.get_pkey() << " " << user1.get_balance() << std::endl;
    std::cout << user2.get_name() << " " << user2.get_pkey() << " " << user2.get_balance() << std::endl;
    std::cout << t1.get_hash() << " " << t1.get_tvalue() << std::endl;
    std::cout << w1.get_mhash() << " " << w1.get_award() << std::endl;
    w1.add_transaction(t2);
    std::cout << w1.get_mhash() << " " << w1.get_award() << std::endl;

    std::cout << user1.get_name() << " " << user1.get_pkey() << " " << user1.get_balance() << std::endl;
    std::cout << user2.get_name() << " " << user2.get_pkey() << " " << user2.get_balance() << std::endl;
    return 0;
}
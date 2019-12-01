//
// Created by Dominykas  on 30/11/2019.
//

#ifndef VUCHAIN_BLOCKCHAIN_H
#define VUCHAIN_BLOCKCHAIN_H

#include "main.h"
#include "block.h"
#include "transaction.h"
#include "user.h"
#include "./HASH/sha256.h"
#include "transaction_list.h"

class MineCandidate {
private:
    int index;
    float reward = 0;
    TransactionList t_list;
    std::vector<int> transaction_indexes;
public:
    MineCandidate(int t_count, std::vector<Transaction> & pool, float reward_range) {
        for (int i = 0; i < t_count; i++) {
            index = rand() % pool.size();
            Transaction t = pool[index];
            if ((t.valid() && t.get_hash() == t.get_gen_hash())) {
                t_list.add_transaction(t);
                transaction_indexes.push_back(index);
                reward += t.get_tvalue() * reward_range;
            }
        }
    }
    void push_index(int i) { transaction_indexes.push_back(i); }
    void add_transaction(Transaction t) { t_list.add_transaction(t); }
    float get_reward() { return reward; }
    TransactionList get_transaction_list() { return t_list; }
    std::vector<int> get_indexes() { return transaction_indexes; }
};

class Blockchain {
private:
    std::vector<Block> chain;
    std::vector<Transaction> pool;
    float reward_range;
    int difficulty;

    User chain_wallet;

    void clear_pool(std::vector<int> indexes) {
        for (int idx : indexes)
            pool[idx].approved();
        for (int i = 0; i < pool.size(); i++) {
            if (pool[i].is_approved())
                pool.erase(pool.begin() + i);
        }
    }
public:
    Blockchain(float r_r, int dif) {
        Block genesis_block(
                "0196C0A1831D74CA1FD80ED58589B27E54F49E905CA34A669F89AC48DF7986B9",
                sha256("transaction")
                );
        genesis_block.mine(1);
        chain.push_back(genesis_block);

        reward_range = r_r;
        difficulty = dif;
        User wallet("wallet", 0);
        chain_wallet = wallet;
    }

    void add_transaction(Transaction t) {
        pool.push_back(t);
    }

    void mine(User miner, int nonce_try = 4000000, double mine_time = 10) {
        MineCandidate a(100, pool, reward_range);
        MineCandidate b(100, pool, reward_range);
        MineCandidate c(100, pool, reward_range);
        MineCandidate d(100, pool, reward_range);
        MineCandidate e(100, pool, reward_range);

        std::string hash;
        float reward;
        std::vector<int> indexes;
        char b_name;

        Block block_a(chain[chain.size() - 1].get_hash(), a.get_transaction_list().get_mhash());
        Block block_b(chain[chain.size() - 1].get_hash(), b.get_transaction_list().get_mhash());
        Block block_c(chain[chain.size() - 1].get_hash(), c.get_transaction_list().get_mhash());
        Block block_d(chain[chain.size() - 1].get_hash(), d.get_transaction_list().get_mhash());
        Block block_e(chain[chain.size() - 1].get_hash(), e.get_transaction_list().get_mhash());

        if(block_a.mine(difficulty, nonce_try, mine_time)) {
            chain.push_back(block_a);
            reward = a.get_reward();
            hash = block_a.get_hash();
            b_name = 'a';
            indexes = a.get_indexes();
        } else if (block_b.mine(difficulty, nonce_try, mine_time)) {
            chain.push_back(block_b);
            reward = b.get_reward();
            hash = block_b.get_hash();
            b_name = 'b';
            indexes = b.get_indexes();
        } else if (block_c.mine(difficulty, nonce_try, mine_time)) {
            chain.push_back(block_c);
            reward = c.get_reward();
            hash = block_c.get_hash();
            b_name = 'c';
            indexes = c.get_indexes();
        } else if (block_d.mine(difficulty, nonce_try, mine_time)) {
            chain.push_back(block_d);
            reward = d.get_reward();
            hash = block_d.get_hash();
            b_name = 'd';
            indexes = d.get_indexes();
        } else if (block_e.mine(difficulty, nonce_try, mine_time)) {
            chain.push_back(block_e);
            reward = e.get_reward();
            hash = block_e.get_hash();
            b_name = 'e';
            indexes = e.get_indexes();
        } else {
            std::cout << "Block was not mined!" << std::endl;
            return;
        }

    chain_wallet.receive(reward);
        std::cout << "Block " << b_name << " mined: " << hash << std::endl;
        clear_pool(indexes);
        Transaction award(&miner, &chain_wallet, reward);
        pool.push_back(award);
    }

    int get_transaction_count() {
        return pool.size();
    }
};


#endif //VUCHAIN_BLOCKCHAIN_H

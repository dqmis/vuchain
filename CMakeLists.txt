cmake_minimum_required(VERSION 3.14)
project(vuchain)

set(CMAKE_CXX_STANDARD 17)

add_executable(vuchain main.cpp user.h main.h ./HASH/HASH.cpp ./HASH/HASH.h ./HASH/sha256.cpp ./HASH/sha256.h transaction.h transaction_list.h block.h HASH/sha256.cpp HASH/sha256.h blockchain.cpp blockchain.h)
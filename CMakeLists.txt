cmake_minimum_required(VERSION 3.14)
project(vuchain)

set(CMAKE_CXX_STANDARD 11)
set(ENV{PKG_CONFIG_PATH} "/usr/local/libbitcoin/lib/pkgconfig/:$ENV{PKG_CONFIG_PATH}")

find_package(PkgConfig REQUIRED)
find_library(libbitcoin PKG_CONFIG_PATH)
pkg_check_modules(LIB_BITCOIN REQUIRED libbitcoin)

add_executable(vuchain main.cpp user.h main.h ./HASH/HASH.cpp ./HASH/HASH.h ./HASH/sha256.cpp ./HASH/sha256.h transaction.h transaction_list.h block.h HASH/sha256.cpp HASH/sha256.h blockchain.cpp blockchain.h)

target_link_libraries(vuchain PRIVATE ${LIB_BITCOIN_LINK_LIBRARIES})
target_include_directories(vuchain PRIVATE ${LIB_BITCOIN_INCLUDE_DIRS})


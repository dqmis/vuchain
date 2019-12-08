# vuchain - the best blockchain

This is my attempt to create an usable blockchain.  
<img src="https://media.giphy.com/media/ehtr0A3IhmXPq/giphy.gif" width=200px/>

## How does my blockchain work?
How does my blockchain work? Well, it is actually not that difficult to explain. It works because of the magic! No, but really here are the main steps that define my blockchain's workflow:

* The genesis block is created
* Users are created, I give them a random amount of money
* Transactions are created and put into the pool
* Blocks are mined until there are 10 or fewer transactions into the pool

I am also creating 5 different candidates of blocks to be added to the chain. This makes the mining process faster. 

### File structure
* `HASH` - Folder where my hash function + `sha256` are held in
* `block.h` - Header file o blockchain's block
* `blockchain.cpp` - Source file of Blockchain
* `blockchain.h` - Header file of blockchain
* `main.cpp` - Main file
* `main.h` - Main header file
* `transaction.h` - Header file of transaction
* `transaction_list.h` - Header file of transaction lists
* `user.h` - User's header file

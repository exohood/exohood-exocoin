<p  align="center">
	<img  src="zelg.png">
</p>

*  [About Exohood](#About-Exohood)
*  [Blockchain Technical Background](#Blockchain-Technical-Background)
	*  [The CryptoNote Protocol](#The-CryptoNote-Protocol)
		* [double-Spending Proof](#double-Spending-Proof)
	*  [Exohood Blockchain](#Exohood-Blockchain)
*  [Exchange Listing Guide](#Exchange-Listing-Guide)
	*  [Binaries](#Binaries)
		* [Relevant Binaries for Exchange Integration](#Relevant-Binaries-for-Exchange-Integration)
	* [Building Binaries from Source](#Building-Binaries-from-Source)
		* [dependencies](#dependencies)
		* [Install All dependencies at Once on Ubuntu](#Install-All-dependencies-at-Once-on-Ubuntu)
		* [Cloning the Repository](#Cloning-the-Repository)
		* [Build Instructions](#Build-Instructions)
	* [Executing Binaries](#Executing-Binaries)
		* [Start Exohood Node](#Start-Exohood-Node)
		* [Start Exohood Wallet RPC](#Start-Exohood-Wallet-RPC)
	* [Exohood Wallet](#Exohood-Wallet)
		* [Creating a new Wallet](#Creating-a-new-Wallet)
		* [Open Wallet](#Open-Wallet)
		* [Close Wallet](#Close-Wallet)
		* [Get Wallet Adress](#Get-Wallet-Adress)
		* [Get Wallet Balance](#Get-Wallet-Balance)
		* [Get Height](#Get-Height)
		* [Wallet Accounts](#Wallet-Accounts)
			* [Create Account](#Create-Account)
			* [Get Accounts](#Get-Accounts)
		* [Transfer Split](#Transfer-Split)
		* [Sweep All](#Sweep-All)
		* [Get Transfers](#Get-Transfers)
		* [Get Payments](#Get-Payments)
		* [Rescan Spent](#Rescan-Spent)
		* [Wallet Backup](#Wallet-Backup)
		* [Wallet Recovery](#Wallet-Recovery)
	*  [Best Practice Wallet Setup](#Best-Practice-Wallet-Setup)
		* [Optimizing Wallet Transaction Times](#Optimizing-Wallet-Transaction-Times)
		* [Cold Storage](#Cold-Storage)
		* [exo Mobile App QR Code](#exo-Mobile-App-QR-Code)
		* [Number of Confirmations](#Number-of-Confirmations)
		* [Identifying deposits](#Identifying-deposits)
			* [Accounts](#Accounts)
			* [Payment Id](#Payment-Id)
	*  [Troubleshooting](#Troubleshooting)
		*  [Problems when Syncing the Blockchain](#Problems-when-Syncing-the-Blockchain)
		*  [Restarting the daemon](#Restarting-the-daemon)
*  [Useful Exohood Links](#Useful-Exohood-Links)
	*  [Technical Links](#Technical-Links)
	*  [Social Media Links](#Social-Media-Links)
	*  [Exohood Support desk & FAQ's](#Exohood-Support-desk-&-FAQ's)

# About ExoCoin
ExoCoin is an mobile miner puts a small amount of EXO into the hands of users every day, providing market liquidity and driving viral growth. We building a global technology that allows instant cryptocurrency payments. The ability to SPEND EXO instantly is only half the equation. We are developing an API that will allow easy integration to ACCEPT EXO instantly. This means it will be simple to allow an ecommerce system to give instant check out, and even allow easy integration into ePOS systems (electronic point of sales systems or tills).

The core of ExoCoin is open source and completely free to use without restrictions. We introduced some fairly radical changes to the cryptonote blockchain, those consisting on a new consensus algorithm we’ve coined as Proof of Responsibility and change from a full permission-less blockchain to a Moderated Blockchain.

A Moderated Blockchain, powered by the Proof of Responsibility consensus algorithm, allow Exohood's to have more control over the blockchain while keeping a good degree of decentralization. This ultimately improves our security while making the blockchain’s commercial & economic model more attractive. Besides these main features, we’ve included a few minor changes that contributes to the blockchain’s operability and scalability.

In 2023, in order to comply with regulations and remove obstacles to the growth of the project, we migrated away from blockchain privacy with our V2 fork, and opted for a completely transparent and public blockchain.

# Blockchain Technical Background
The Exohood blockchain is a UTXO-model blockchain that was originally based on the Monero/CryptoNote open-source projects, but we have since removed all the privacy features. Starting from our blockchain update, transactions and adresses are completely public in a very similar manner to that of Bitcoin's. That puts us in line with regulators around the globe.

## The CryptoNote Protocol
Exohood blockchain is building on top of the CryptoNote Protocol, an open-source technology with advanced mathematical and cryptograph features to empower end-users with the best blockchain technology currently available.

### double-Spending Proof
We have a database driven UTXO book-keeping, meaning that nobody is able to spend the same exo twice

### Proof of Responsibility
Our block validation is permissioned, and those entities that are permissioned to validate blocks are contracted and monitored based on both their responsibility using the proceeds of their validations, and their good natured participation in our network. We have a number of charities who are using the proceeds to help developing nations and other people in need.

## Exohood Blockchain
Although Exohood is building and forked from Monero project and we have been implementing several unique and essential changes to the protocol, being steps closer to become the mass adopted mobile cryptocurrency.

Some of the major features we have introduced enables higher transaction throughput in the blockchain and KYC & AML (Know Your Customer & Anti-Money Laundry) processes through the removal of all of the privacy features present in Monero.

We recommend reading the [**daemon RPC**](https://github.com/Exohood/exohood-coin/blob/develop/docs/daemon-rpc-documentation.md) & [**Wallet RPC**](https://github.com/Exohood/exohood-coin/blob/develop/docs/wallet-rpc-documentation.md) documentation before integrating Exohood into your exchange.

# Exchange Listing Guide
This document is aimed at providing information and access to resources to ensure a seamless listing of Exohood (exo) on your exchange.

Exohood has its own blockchain and therefore the management of Exohood on your exchange is different from that of ERC20 tokens. This document is our current best practice guide on how to structure and manage Exohood in the most efficient way for your exchange.

## Binaries
Exohood is an open-source project. Binaries can be downloaded directly from our [**GitHub**](https://github.com/Exohood/exohood-coin/releases) or built by yourself on Ubuntu, Windows and MacOS.

### Relevant Binaries for Exchange Integration

| Binary | description |
| --- | --- |
| Exohood | This is the Exohood node software, responsible to sync and interact with the blockchain |
| Exohood-wallet-cli | CLI wallet client. Manages wallets through a command-line interface |
| Exohood-wallet-rpc | RPC wallet client. Manages wallets through a RPC-based interface |

## Building Binaries from Source
### dependencies
The following table summarizes the tools and libraries required to build. A few of the libraries are also included in this repository (marked as "Vendored"). By default, the build uses the library installed on the system, and ignores the vendored sources. However, if no library is found installed on the system, then the vendored source will be built and used. The vendored sources are also used for tatically-linked builds because distribution packages often include only shared library binaries (`.so`) but not static library archives (`.a`).

| dep | Min. version | Vendored | debian/Ubuntu pkg | Arch pkg | Fedora | Optional | Purpose |
| ------------ | ------------- | -------- | ------------------ | ------------ | ----------------- | -------- | ---------------- |
| GCC | 4.7.3 | NO | `build-essential` | `base-devel` | `gcc` | NO | C/C++ compiler |
| CMake | 3.5 | NO | `cmake` | `cmake` | `cmake` | NO | Build system |
| pkg-config | any | NO | `pkg-config` | `base-devel` | `pkgconf` | NO | Compiler options |
| Boost | 1.58 | NO | `libboost-all-dev` | `boost` | `boost-devel` | NO | C++ libraries |
| OpenSSL | basically any | NO | `libssl-dev` | `openssl` | `openssl-devel` | NO | sha256 sum |
| libzmq | 3.0.0 | NO | `libzmq3-dev` | `zeromq` | `cppzmq-devel` | NO | ZeroMQ library |
| OpenPGM | ? | NO | `libpgm-dev` | `libpgm` | `openpgm-devel` | NO | For ZeroMQ |
| libnorm[2] | ? | NO | `libnorm-dev` | | ` | YES | For ZeroMQ |
| libunbound | 1.4.16 | YES | `libunbound-dev` | `unbound` | `unbound-devel` | NO | dNS resolver |
| libsodium | ? | NO | `libsodium-dev` | `libsodium` | `libsodium-devel` | NO | cryptography |
| libunwind | any | NO | `libunwind8-dev` | `libunwind` | `libunwind-devel` | YES | Stack traces |
| liblzma | any | NO | `liblzma-dev` | `xz` | `xz-devel` | YES | For libunwind |
| libreadline | 6.3.0 | NO | `libreadline6-dev` | `readline` | `readline-devel` | YES | Input editing |
| ldns | 1.6.17 | NO | `libldns-dev` | `ldns` | `ldns-devel` | YES | SSL toolkit |
| expat | 1.1 | NO | `libexpat1-dev` | `expat` | `expat-devel` | YES | XML parsing |
| GTest | 1.5 | YES | `libgtest-dev`[1] | `gtest` | `gtest-devel` | YES | Test suite |
| doxygen | any | NO | `doxygen` | `doxygen` | `doxygen` | YES | documentation |
| Graphviz | any | NO | `graphviz` | `graphviz` | `graphviz` | YES | documentation |
| lrelease | ? | NO | `qttools5-dev-tools` | `qt5-tools` | `qt5-linguist` | YES | Translations |
| libhidapi | ? | NO | `libhidapi-dev` | `hidapi` | `hidapi-devel` | YES | Hardware wallet |
| libusb | ? | NO | `libusb-dev` | `libusb` | `libusb-devel` | YES | Hardware wallet |
| libprotobuf | ? | NO | `libprotobuf-dev` | `protobuf` | `protobuf-devel` | YES | Hardware wallet |
| protoc | ? | NO | `protobuf-compiler` | `protobuf` | `protobuf-compiler` | YES | Hardware wallet |

[1] On debian/Ubuntu `libgtest-dev` only includes sources and headers. You must build the library binary manually. This can be done with the following command ```sudo apt-get install libgtest-dev && cd /usr/src/gtest && sudo cmake . && sudo make && sudo mv libg* /usr/lib/ ```

[2] libnorm-dev is needed if your zmq library was built with libnorm, and not needed otherwise.

### Install All dependencies at Once on Ubuntu:
``` sudo apt update && sudo apt install build-essential cmake pkg-config libboost-all-dev libssl-dev libzmq3-dev libunbound-dev libsodium-dev libunwind8-dev liblzma-dev libreadline6-dev libldns-dev libexpat1-dev doxygen graphviz libpgm-dev libusb-dev```

### Cloning the Repository
Clone recursively to pull-in needed submodule(s):
`$ git clone --recursive https://github.com/Exohood/exohood-coin`

If you already have a repo cloned, initialize and update:
`$ cd Exohood && git submodule init && git submodule update`

### Build Instructions
Exohood uses the CMake build system and a top-level Makefile that invokes cmake commands as needed.

* Install the dependencies
* Change to the root of the source code directory, change to the most recent release branch, and build:
```bash
cd Exohood
make
```
*Optional*: If your machine has several cores and enough memory, enable parallel build by running `make -j<number of threads>` instead of `make`. For this to be worthwhile, the machine should have one core and about 2GB of RAM
available per thread.
* The resulting executables can be found in `build/release/bin`
* Ad `PATH="$PATH:$HOME/Exohood/build/release/bin"` to `.profile`

## Executing Binaries
### Start Exohood Node

* Run Exohood node with `Exohood`
	*Optional*: Use `Exohood --help` to see a list of supported startup arguments.
	*Optional*: Use `Exohood --detach` to startup the Exohood node in detached mode.

* The Exohood node will start synchronizing with network. The blockchain data will be saved by default at `~/.Exohood`, but can be changed with `--data-dir <path>` startup argument.
	*Optional*: We recommend using the startup argument `--block-sync-size 10` to speed up the sync process.

Please refer to [daemon RPC documentation](https://github.com/Exohood/exohood-coin/blob/develop/docs/daemon-rpc-documentation.md) for more information.

### Start Exohood Wallet RPC

* Run Exohood wallet rpc with `nohup ./Exohood-wallet-rpc`

List of Parameters:
| Parameter Name | description |
| --- | --- |
| rpc-bind-ip (arg) | Specify ip to bind rpc server |
| rpc-bind-port (arg) | Sets bind port for server |
| confirm-external-bind | Confirm rpc-bind-ip value is NOT a loopback (local) IP |
| disable-rpc-login | disable HTTP authentication for RPC |
| wallet-dir (arg) | directory for newly created wallets |

Example:
```
nohup ./Exohood-wallet-rpc --rpc-bind-ip 0.0.0.0 --rpc-bind-port 28071 --confirm-external-bind --disable-rpc-login --wallet-dir "/home/wallets" & echo $1;
```

Please refer to [Wallet RPC documentation](https://github.com/Exohood/exohood-coin/blob/develop/docs/wallet-rpc-documentation.md) for more information.

**All requests to the Exohood Wallet RPC needs to be sent to the following endpoint**
```
POST: http://<wallet_rpc_adress>:<port>/json_rpc
```

## Exohood Wallet
In this section, we list relevant RPC commands for exchange integration. Any wallet interaction is done through REST Requests towards the Exohood Wallet RPC.

### Creating a new Wallet
Create a new wallet. You need to have set the argument `–wallet-dir` when launching Exohood Wallet RPC to make this work.

The wallet will be automatically opened in Exohood Wallet RPC after its creation process. Other RPC methods such as  `query_key`  and  `getadress`  (demonstrated above) will be executed against this current opened wallet.

> Request ([create_wallet](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#create_wallet))
```
{
	"jsonrpc":"2.0",
	"id":"0",
	"method":"create_wallet",
	"params":{
		"filename":"<wallet_name>",
		"password":"<wallet_password>",
		"language":"English"
	}
}
```

### Open Wallet
Open a wallet. You need to have set the argument "–wallet-dir" when launching Exohood Wallet RPC to make this work.

> Request ([open_wallet](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#open_wallet))
```
{
	"jsonrpc": "2.0",
	"id": "0",
	"method": "open_wallet",
	"params": {
		"filename": "<wallet_name>",
		"password": "<wallet_password>"
	}
}
```

### Close Wallet
Close the currently opened wallet, after trying to save it.

> Request ([close_wallet](https://github.com/Exohood/Exohood/blob/master/docs/wallet-rpc-documentation.md#close_wallet))
```
{
	"jsonrpc": "2.0",
	"id": "0",
	"method": "close_wallet"
}
```

### Get Wallet Adress
Return the wallet's adresses for an account. Optionally filter for specific set of accounts.

> Request ([get_adress](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#get_adress))
```
{
	"jsonrpc":"2.0",
	"id":"0",
	"method":"get_adress"
}
```

### Get Wallet Balance
Return the wallet's balance.

> Request ([get_balance](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#get_balance))
```
{
	"jsonrpc":"2.0",
	"id":"0",
	"method":"get_balance"
}
```
> Response
```
{
	"id": "0",
	"jsonrpc": "2.0",
	"result": {
		"balance": 300000,
		"blocks_to_unlock": 0,
		"multisig_import_needed": false,
		"per_subadress": [{
			"adress": "exokKzqmNPQMk7dehZMif4FLJa1hpUQXjH6ULFEmyVUkRfJfrbphCZsCQt8G2dq1hbC2h4QsdMeohMrUeHcTmtSF4uG2NL756Z",
			"adress_index": 0,
			"balance": 100000,
			"blocks_to_unlock": 4,
			"label": "Primary account",
			"num_unspent_outputs": 5281,
			"unlocked_balance": 50000
		}],
		"unlocked_balance": 150000
}
```

### Get Height
Returns the wallet's current block height.

> Request ([get_height](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#get_height))
```
{
	"jsonrpc": "2.0",
	"id": "0",
	"method": "get_height"
}
```
> Response
```
{
	"id": "0",
	"jsonrpc": "2.0",
	"result": {
		"height": 145545
	}
}
```


### Wallet Accounts
You have the ability to create _accounts_ inside each wallet. If your wallet was like a safe, accounts work as boxes inside to keep things tidy and ordered. Each box comes with its own adress, so funds sent to each one appear under their respective account.

For exchange integration, wallet accounts can be used as a deposit adress for each user. In this case, the `account_index` should be linked to the user in your exchange database.

#### Create Account
Create a new account with an optional label.
> Request ([create_account](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#create_account))
```
{
	"jsonrpc": "2.0",
	"id": "0",
	"method": "create_account"
}
```
> Response
```
{
	"id": "0",
	"jsonrpc": "2.0",
	"result": {
		"account_index": 1,
		"adress": "exokfduwUbTcLs9LtSF2ULduLV44wmyKr9JJgdGt26aUe82LxYFcJzAXWWLdj5jeKdhNXdo9wPNzGcW3s13yoBw65zr23u671f"
	}
}
```

#### Get Accounts
Get all accounts for a wallet. Optionally filter accounts by index or tag.

> Request ([get_accounts](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#get_accounts))
```
{
	"jsonrpc": "2.0",
	"id": "0",
	"method": "get_accounts",
	"params": {
		"account_index": "1"
	}
}
```
> Response
```
{
	"id": "0",
	"jsonrpc": "2.0",
	"result": {
		"account_major_offset": 0,
		"subadress_accounts": [
		{
			"account_index": 1,
			"balance": 0,
			"base_adress": "exokfduwUbTcLs9LtSF2ULduLV44wmyKr9JJgdGt26aUe82LxYFcJzAXWWLdj5jeKdhNXdo9wPNzGcW3s13yoBw65zr23u671f",
			"label": "",
			"tag": "",
			"unlocked_balance": 0
		}],
		"total_balance": 0,
		"total_unlocked_balance": 0
	}
}
```

### Transfer Split
Send exo to a number of recipients.

We recommend the usage of **transfer_split** over the **transfer** due to it being a legacy command.

If your wallet has multiple accounts, you need to specify the `account_index` (defaults to 0) from which exo will be spent from.


> Request ([transfer_split](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#transfer_split))
```
{
	"jsonrpc": "2.0",
	"id": "0",
	"method": "transfer_split",
	"params": {
		"account_index": 0
		"destinations": [
		{
			"amount": 58000,
			"adress": "exokWaJUHsB6JWCNC1X8AMVms5ujU281mEKSNHuK7Ah4exoedfbTdbCNmxtjxunGtfiXUrxJVczRzSSTYxA38di7fN25Yq4eY"
		}],
		"get_tx_key": true,
		"new_algorithm": true
	}
}
```
> Response
```
{
	"id": "0",
	"jsonrpc": "2.0",
	"result": {
		"amount_list": [58000],
		"fee_list": [10],
		"multisig_txset": "",
		"tx_hash_list": ["4adcdc1af3f665770cdf8fb7a380887cd07ac53c2b771bd18df5ca375d5e7540"],
		"tx_key_list": ["5b455c0f97168be652a2c03c5c68a064bb84cdae4def01b5c48d73a0bbb27075fb714f2ca19ea6c8ff592417e606adea6deb1d6530e2969f75681ffcbfc4075677b94a8c9197963ae38fa6f543ee68f0a4c4bbda4c453f39538f00b28e980ea08509730b51c004960101ba2f3adbc34cbbdff0d5af9dba061b523090debd06"],
		"unsigned_txset": ""
	}
}
```

### Sweep All

Sends all unlocked balance to an adress.

> Request ([sweep_all](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#sweep_all))
```
{
	"jsonrpc": "2.0",
	"id": "0",
	"method": "sweep_all",
	"params": {
		"adress": "exojw64JfkwKapwWyCenbu8Zj4odo4p6dMJo6dozdx3cwtbMKzgw4ScjVaWi8psbGdvdUKz4PJ6d7rU2bsLKhJE4EEuob3K1X",
		"unlock_time": 0,
		"get_tx_keys": true
	}
}
```
> Response
```
{
	"id": "0",
	"jsonrpc": "2.0",
	"result": {
		"amount_list": [30000],
		"fee_list": [10],
		"multisig_txset": "",
		"tx_hash_list": ["ab4b6b65cc8cd8c9d317d0b90d97582d68d0aa1637b0065b05b61f9a66ea5c5"],
		"tx_key_list": ["b9b4b39d3bb3062db85ec0266d4df39058f4c86077d99309f218ce4d76af607"],
		"unsigned_txset": ""
	}
}
```

### Get Transfers
Returns a list of transfers.

You can get transfers for all accounts in this wallet or for a particular `account_index`. It is possible to filter by incoming, outgoing, pending, pool and failed transactions.

> Request ([get_transfers](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#get_transfers))
```
{
	"jsonrpc": "2.0",
	"id": "0",
	"method": "get_transfers",
	"params": {
		"account_index": 0,
		"pool": false,
		"in": true,
		"out": false,
		"migration": false,
		"pending": false
	}
}
```
> Response
```
{
	"id": "0",
	"jsonrpc": "2.0",
	"result": {
		"in": [
		{
			"adress": "exojw64JfkwKapwWyCenbu8Zj4odo4p6dMJo6dozdx3cwtbMKzgw4ScjVaWi8psbGdvdUKz4PJ6d7rU2bsLKhJE4EEuob3K1X",
			"amount": 10000,
			"confirmations": 1,
			"double_spend_seen": false,
			"fee": 0,
			"height": 1071196,
			"nonexistent_utxo_seen": false,
			"note": "",
			"payment_id": "0000000000000000",
			"subadr_index": {
			"major": 0,
			"minor": 0
		},
		"subadr_indices": [
			{
				"major": 0,
				"minor": 0
			}
		],
		"suggested_confirmations_threshold": 5,
		"timestamp": 1628486571,
		"txid": "fb80573819d20f1b13212fc407b7f8b881047742e9ebc8d7c8256c6d24efb2da",
		"type": "in",
		"unlock_time": 1071201
		}]
	}
}
```

### Get Payments
Get a list of incoming payments using a given payment id.

Exohood wallet supports sending payments with a Payment Id (MEMO) to identify payments to a specific user. If you choose to use the Payment Id to identify user deposits rather than using Accounts, you should use this command to get all transfers for a given Payment Id.

> Request ([get_payments](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#get_payments))
```
{
	"jsonrpc": "2.0",
	"id": "0",
	"method": "get_payments",
	"params": {
		"payment_id": "4279257e0a20608e25dba8744949c9e1caff4fcdafc7d5362ecf14225f3d9030"
	}
}
```
> Response
```
{
	"id": "0",
	"jsonrpc": "2.0",
	"result": {
		"payments": [{
			"adress": "exoku32HZrgZBqT2d3gtMBVvyAYobaPpQP38Ju7TBq89Yz5o8TVp4NnXkVX4d5f3sLHgpd8haep9HKk69eu4sQmw8jbVUfQ1cY",
			"amount": 1000000,
			"block_height": 727606,
			"payment_id": "60900e5603bf96e3",
			"subadr_index": {
			"major": 0,
			"minor": 0
		},
		"tx_hash": "3292e83ad28fc1cc7bc26dbd38862308f4588680fbf93eae3e803cd1bd614f",
		"unlock_time": 0
		}]
	}
}
```

### Rescan Spent
Rescan the blockchain for spent outputs.

> Request ([rescan_spent](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#rescan_spent))
```
{
	"jsonrpc":"2.0",
	"id":"0",
	"method":"rescan_spent"
}
```

### Wallet Backup
Wallet backup consists in saving a particular private key, known as private spend key. This key is mandatory for wallet recovery and should be saved offline for best security.

> Request ([query_key](https://github.com/Exohood/exohood-coin/blob/master/docs/wallet-rpc-documentation.md#query_key))
```
{
	"jsonrpc":"2.0",
	"id":"0",
	"method":"query_key",
	"params":{
		"key_type":"spend_key"
	}
}
```
The key retrieved in the response should be stored safely for wallet recovery. Anyone with access to this key can restore, view and spend exo from this wallet.

### Wallet Recovery
The wallet recovery process is done through the **Exohood Wallet CLI** software.

- Run the Wallet CLI with `Exohood-wallet-cli --generate-from-spend-key <wallet_file>`
- Specify the **private spend key** when asked in the CLI
- Specify & confirm a **new password** for the wallet
- Specify the **restore block height** or **restore date**. This should be the block height of the first transaction in this wallet, or its approximate date.
- Save the wallet with `save` and exit with `exit`
- Copy the wallet file (`<wallet_file>`) to the Exohood Wallet RPC wallets directory
- Open the wallet in the Exohood Wallet RPC


## Best Practice Wallet Setup

We recommend having at least one withdrawal wallet and one deposit wallet. Our best practice recommendation to ensure that your deposit and withdrawal wallets run as efficiently as possible is to rotate on a monthly basis, as illustrated below in Figure 1:

<p  align="center">
<img  src="image">
</p>

You should periodically rotate your **WITHdRAW WALLET 1** by ```sweep_all``` into your second withdraw wallet (**WITHdRAW WALLET 2**). This allows you to open wallet 2 from the sweep block height (minus 720 blocks) and use with virtually no delay.

After another month the rotation should return to **WITHdRAW WALLET 1** by using ```sweep_all``` into **WALLET 1** from **WITHdRAW WALLET 2**. The actual frequency of rotation can be amended by you based on the number of transactions you perform and the response time.

### Optimizing Wallet Transaction Times

Over time, the transaction speed of highly active **dEPOSIT WALLET** and **WITHdRAWAL WALLETS** wallets will start to decrease. This is due to the UTXO model of outputs used for the blockchain and wallet, which accumulates outputs in the wallet cache over time, thereby increasing the wallet size and the extent of balance fragmentation, which can degrade performance in a number of ways.

In order to negate this and optimize your wallet transaction time, we recommend the following housekeeping process to be run on a monthly basis (this shouldn't take any longer than 1-2 hours per month). You can view this process as being akin to defragmenting a hard drive.

This process can be done from **WITHdRAWAL WALLET 1** to **WITHdRAWAL WALLET 2** (and vice-versa) and/or from **dEPOSIT WALLET** to **COLd STORAGE WALLET**, significantly improving performance leading to virtually no delay in response.

**The procedure for this is as follows:**

- Start the Exohood Wallet RPC (see [Start Wallet RPC](#Start-Exohood-Wallet-RPC))
- Open the **WITHdRAWAL WALLET 1** with [open_wallet](#Open-Wallet)
- Sweep all from the **WITHdRAWAL WALLET 1**  to **WITHdRAWAL WALLET 2**  with [sweep_all](#Sweep-All)
- Get the **WITHdRAWAL WALLET 1** block height with [get_height](#Get-Height)
- Close **WITHdRAWAL WALLET 1** with [close_wallet](#Close-Wallet)
- Restore **WITHdRAWAL WALLET 2** (see [Wallet Recovery](#Wallet-Recovery)), using the block height from previous step
- Open the **WITHdRAWAL WALLET 2** with [open_wallet](#Open-Wallet)
- Execute [rescan_spent](#Rescan-Spent) command to prevent any errors


### Cold Storage

It is considered best practice to ensure you are keeping a percentage of your exo in cold storage in a separate wallet or wallets. Again, depending on the transaction numbers you could rotate these wallets for increased wallet efficiency.

### exo Mobile App QR Code

The exo Mobile app can scan QR Codes to pre-populate fields for sending exo. If you generate a QR code with the following information, it can be imported directly.

```
Exohood:WALLET_AdRESS?tx_payment_id=YOUR_PAYMENT_Id
```

**Example:**
```
Exohood:exo12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345?tx_payment_id=a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9a9
```

### Number of Confirmations

NUMBER OF CONFIRMATIONS: **5 BLOCKS**

When a user transfer funds to an adress, the transaction sits in the mempool until it gets processed into a block. The first few blocks are susceptible to "blockchain reorganizations" and, although block reorganizations being a natural behavior of the blockchain, it may cause a rollback in transactions contained in a given reorganized block(s). In other words, the transactions included in a recent block may get back to mempool or even back to the sender.

To assure that the funds sent from a user to your exchange is confirmed by the blockchain and an eventual rollback won't happen, your system needs to wait for a few more blocks to come. This "wait" is technically the number of confirmations (measured in blocks) you need before unlocking the funds to the user.

We recommend that you use **5 blocks as number of confirmations** required to optimal security of funds.

### Identifying deposits

You can identify deposits by one of the two currently available methods.

#### Accounts
The wallet has the ability to create _accounts_ inside each wallet. If your wallet was like a safe, accounts work as boxes inside to keep things tidy and ordered. Each box comes with its own adress, so funds sent to each one appear under their respective account.

When using [Get Wallet Balance](#Get-Wallet-Balance) in Exohood Wallet RPC, you can see the total balance of all its accounts, but you can filter by _account_index_ if you want see the individual balances as well. 

The _account_index_ should be used to link your user to one of the wallet's account in a 1-to-1 relationship. Accounts can be created with [Create Account](#Create-Account) and retrieved with [Get Accounts](#Get-Accounts) Wallet RPC commands.

Transfers for a specific Wallet Account can be retrieved with [Get Transfers](#Get-Transfers) by specifying the _account_index_.

It's important to note that your wallet can sign transactions for all accounts within this particular wallet, since the adress for each account is derived from the same private keys. This can be achieved with [Transfer Split](#Transfer-Split) by providing the _account_index_ attribute. However, you can send only one transaction per account at a time, so sending the funds to your Cold Storage would require multiple transactions (one for each account).

#### Payment Id
This is the most used method of identifying deposits by exchanges that supports exo, it is simple, effective and most exchanges already use a similar method (MEMO).

In this case, the deposit wallet adress should be shared among all exchange users and deposits should require an unique / per-user Payment Id (MEMO) to identify deposits to a particular user.

A Payment Ids are 16 or 64 hexadecimal character strings and can be created by your system.

Transactions that contains a particular Payment Id can be retrieved with [Get Payments](#Get-Payments) Wallet RPC command.

## Troubleshooting

### Problems when Syncing the Blockchain

If your Exohood daemon is stuck syncing the blockchain, please follow the steps bellow.

#### 1. Make sure you're running Exohood's latest software.

Binaries can be found at: [https://github.com/Exohood/exohoodcoin/releases](https://github.com/Exohood/Exohood/releases)

#### 2. delete the p2pstate.bin file

Make sure Exohood daemon is not running by typing "exit" in Exohood. After closing Exohood's daemon and wallets, you can safely delete the p2pstate.bin file located at:

```
$HOME/.Exohood
```

This directory is hiden by default. On Linux you can use CTRL + H to unhide directories (note that this might not work on all Linux distributions).

After you've deleted p2pstate.bin you can restart Exohood. If this did not resolve your issue, please read further and make sure Exohood is closed again.

#### 3. Change the block sync size

We're going to ad the following flag:
```
--block-sync-size 10
```

This will change the batch of fetched blocks from 100 to 10.

You can ad the flag as follows:
```
./Exohood --block-sync-size 10
```

If your blockchain is still stuck after ading this flag, please browse again to ```$HOME/.Exohood```, open Exohood.log and check it for any errors. If you see any of these errors (or similar to them), your blockchain is most likely corrupted.

```Error opening database: Failed to query m_blocks: MdB_BAd_TXN: Transaction must abort, has a child, or is invalid```

```Failed to parse and validate tx from blob```

You can use the ```--db-salvage``` flag to the daemon, sometimes it can recover from a corrupted data base. If the daemon is still struggling to sync, you may need to resync the blockchain from scratch.

This is done by deleting data.mdb from ```$HOME/.Exohood/lmdb```, which will trigger the resync.

### Restarting the daemon

To force restart the daemon you should use the following command:

sudo systemctl restart Exohood

# Useful Exohood Links

## Technical Links

*  [GitHub Repository](https://github.com/Exohood/exohood-coin)
*  [Block explorer](https://blockexplorer.exohood.com)
*  [daemon RPC documentation](https://github.com/Exohood/exohood-coin/blob/develop/docs/daemon-rpc-documentation.md)
*  [Wallet RPC documentation](https://github.com/Exohood/exohood-coin/blob/develop/docs/wallet-rpc-documentation.md)

## Social Media Links

Official social media channels managed in office by our PR/social media team

*  [Blog](https://exohood.com/blog/)
*  [Twitter](https://twitter.com/ExohoodOfficial)
*  [Discord](https://discord.com/invite/exohood)

## Exohood Support desk & FAQ's

Support site: [https://Exohood.com/support/](https://Exohood.com/support/)

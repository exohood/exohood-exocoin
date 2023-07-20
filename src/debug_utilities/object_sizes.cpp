/*
/***
*     ______           __                    __
*    / _____  ______  / /_  ____  ____  ____/ /
*   / __/ | |/_/ __ \/ __ \/ __ \/ __ \/ __  / 
*  / /____>  </ /_/ / / / / /_/ / /_/ / /_/ /  
* /_____/_/|_|\____/_/ /_/\____/\____/\__,_/   
*                                             
*   
*    
* https://www.exohood.com
*
* MIT License
* ===========
*
* Copyright (c) 2020 - 2023 Exohood Protocol
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <map>
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/tx_extra.h"
#include "cryptonote_core/cryptonote_core.h"
#include "cryptonote_core/blockchain.h"
#include "p2p/p2p_protocol_defs.h"
#include "net/connection_basic.hpp"
#include "p2p/net_peerlist.h"
#include "p2p/net_node.h"
#include "cryptonote_protocol/cryptonote_protocol_handler.h"
#include "blockchain_db/lmdb/db_lmdb.h"
#include "wallet/wallet2.h"
#include "wallet/api/wallet.h"
#include "wallet/api/transaction_info.h"
#include "wallet/api/transaction_history.h"
#include "wallet/api/unsigned_transaction.h"
#include "wallet/api/pending_transaction.h"

#undef EXOHOOD_DEFAULT_LOG_CATEGORY
#define EXOHOOD_DEFAULT_LOG_CATEGORY "debugtools.objectsizes"

class size_logger
{
public:
  ~size_logger()
  {
    for (const auto &i: types)
      std::cout << std::to_string(i.first) << "\t" << i.second << std::endl;
  }
  void add(const char *type, size_t size) { types.insert(std::make_pair(size, type)); }
private:
  std::multimap<size_t, const std::string> types;
};
#define SL(type) sl.add(#type, sizeof(type))

int main(int argc, char* argv[])
{
  size_logger sl;

  tools::on_startup();

  mlog_configure("", true);

  SL(boost::thread);
  SL(boost::asio::io_service);
  SL(boost::asio::io_service::work);
  SL(boost::asio::deadline_timer);

  SL(cryptonote::DB_ERROR);
  SL(cryptonote::mdb_txn_safe);
  SL(cryptonote::mdb_threadinfo);

  SL(cryptonote::block_header);
  SL(cryptonote::block);
  SL(cryptonote::transaction_prefix);
  SL(cryptonote::transaction);

  SL(cryptonote::txpool_tx_meta_t);

  SL(epee::net_utils::ipv4_network_address);
  SL(epee::net_utils::network_address);
  SL(epee::net_utils::connection_context_base);
  SL(epee::net_utils::connection_basic);

  SL(nodetool::peerlist_entry);
  SL(nodetool::anchor_peerlist_entry);
  SL(nodetool::node_server<cryptonote::t_cryptonote_protocol_handler<cryptonote::core>>);
  SL(nodetool::p2p_connection_context_t<cryptonote::t_cryptonote_protocol_handler<cryptonote::core>::connection_context>);
  SL(nodetool::network_address_old);
  SL(nodetool::peerlist_entry_base<nodetool::network_address_old>);

  SL(nodetool::network_config);
  SL(nodetool::basic_node_data);
  SL(cryptonote::CORE_SYNC_DATA);

  SL(tools::wallet2::transfer_details);
  SL(tools::wallet2::payment_details);
  SL(tools::wallet2::unconfirmed_transfer_details);
  SL(tools::wallet2::confirmed_transfer_details);
  SL(tools::wallet2::tx_construction_data);
  SL(tools::wallet2::pending_tx);
  SL(tools::wallet2::unsigned_tx_set);
  SL(tools::wallet2::signed_tx_set);

  SL(EXOHOOD::WalletImpl);
  SL(EXOHOOD::AddressBookRow);
  SL(EXOHOOD::TransactionInfoImpl);
  SL(EXOHOOD::TransactionHistoryImpl);
  SL(EXOHOOD::PendingTransactionImpl);
  SL(EXOHOOD::UnsignedTransactionImpl);

  return 0;
}

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

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/tx_extra.h"
#include "cryptonote_core/blockchain.h"
#include "common/command_line.h"
#include "version.h"

#undef Exohood_DEFAULT_LOG_CATEGORY
#define Exohood_DEFAULT_LOG_CATEGORY "debugtools.deserialize"

namespace po = boost::program_options;
using namespace epee;

using namespace cryptonote;

static std::string extra_nonce_to_string(const cryptonote::tx_extra_nonce &extra_nonce)
{
  if (extra_nonce.nonce.size() == 9 && extra_nonce.nonce[0] == TX_EXTRA_NONCE_ENCRYPTED_PAYMENT_ID)
    return "encrypted payment ID: " + epee::string_tools::buff_to_hex_nodelimer(extra_nonce.nonce.substr(1));
  if (extra_nonce.nonce.size() == 33 && extra_nonce.nonce[0] == TX_EXTRA_NONCE_PAYMENT_ID)
    return "plaintext payment ID: " + epee::string_tools::buff_to_hex_nodelimer(extra_nonce.nonce.substr(1));
  return epee::string_tools::buff_to_hex_nodelimer(extra_nonce.nonce);
}

static void print_extra_fields(const std::vector<cryptonote::tx_extra_field> &fields)
{
  std::cout << "tx_extra has " << fields.size() << " field(s)" << std::endl;
  for (size_t n = 0; n < fields.size(); ++n)
  {
    std::cout << "field " << n << ": ";
    if (typeid(cryptonote::tx_extra_padding) == fields[n].type()) std::cout << "extra padding: " << boost::get<cryptonote::tx_extra_padding>(fields[n]).size << " bytes";
    else if (typeid(cryptonote::tx_extra_pub_key) == fields[n].type()) std::cout << "extra pub key: " << boost::get<cryptonote::tx_extra_pub_key>(fields[n]).pub_key;
    else if (typeid(cryptonote::tx_extra_nonce) == fields[n].type()) std::cout << "extra nonce: " << extra_nonce_to_string(boost::get<cryptonote::tx_extra_nonce>(fields[n]));
    else if (typeid(cryptonote::tx_extra_merge_mining_tag) == fields[n].type()) std::cout << "extra merge mining tag: depth " << boost::get<cryptonote::tx_extra_merge_mining_tag>(fields[n]).depth << ", merkle root " << boost::get<cryptonote::tx_extra_merge_mining_tag>(fields[n]).merkle_root;
    else if (typeid(cryptonote::tx_extra_additional_pub_keys) == fields[n].type()) std::cout << "additional tx pubkeys: " << boost::join(boost::get<cryptonote::tx_extra_additional_pub_keys>(fields[n]).data | boost::adaptors::transformed([](const crypto::public_key &key){ return epee::string_tools::pod_to_hex(key); }), ", " );
    else if (typeid(cryptonote::tx_extra_mysterious_minergate) == fields[n].type()) std::cout << "extra minergate custom: " << epee::string_tools::buff_to_hex_nodelimer(boost::get<cryptonote::tx_extra_mysterious_minergate>(fields[n]).data);
    else std::cout << "unknown";
    std::cout << std::endl;
  }
}

int main(int argc, char* argv[])
{
  uint32_t log_level = 0;
  std::string input;

  tools::on_startup();

  boost::filesystem::path output_file_path;

  po::options_description desc_cmd_only("Command line options");
  po::options_description desc_cmd_sett("Command line options and settings options");
  const command_line::arg_descriptor<uint32_t> arg_log_level  = {"log-level",  "", log_level};
  const command_line::arg_descriptor<std::string> arg_input = {"input", "Specify input has a hexadecimal string", ""};

  command_line::add_arg(desc_cmd_sett, arg_log_level);
  command_line::add_arg(desc_cmd_sett, arg_input);

  command_line::add_arg(desc_cmd_only, command_line::arg_help);

  po::options_description desc_options("Allowed options");
  desc_options.add(desc_cmd_only).add(desc_cmd_sett);

  po::variables_map vm;
  bool r = command_line::handle_error_helper(desc_options, [&]()
  {
    po::store(po::parse_command_line(argc, argv, desc_options), vm);
    po::notify(vm);
    return true;
  });
  if (! r)
    return 1;

  if (command_line::get_arg(vm, command_line::arg_help))
  {
    std::cout << "Exohood '" << Exohood_RELEASE_NAME << "' (v" << EXOHOOD_VERSION_FULL << ")" << ENDL << ENDL;
    std::cout << desc_options << std::endl;
    return 1;
  }

  log_level    = command_line::get_arg(vm, arg_log_level);
  input        = command_line::get_arg(vm, arg_input);
  if (input.empty())
  {
    std::cerr << "--input is mandatory" << std::endl;
    return 1;
  }

  mlog_configure("", true);

  cryptonote::blobdata blob;
  if (!epee::string_tools::parse_hexstr_to_binbuff(input, blob))
  {
    std::cerr << "Invalid hex input" << std::endl;
    return 1;
  }

  bool full;
  cryptonote::block block;
  cryptonote::transaction tx;
  std::vector<cryptonote::tx_extra_field> fields;
  if (cryptonote::parse_and_validate_block_from_blob(blob, block))
  {
    std::cout << "Parsed block:" << std::endl;
    std::cout << cryptonote::obj_to_json_str(block) << std::endl;
  }
  else if (cryptonote::parse_and_validate_tx_from_blob(blob, tx) || cryptonote::parse_and_validate_tx_base_from_blob(blob, tx))
  {
    if (tx.pruned)
      std::cout << "Parsed pruned transaction:" << std::endl;
    else
      std::cout << "Parsed transaction:" << std::endl;
    std::cout << cryptonote::obj_to_json_str(tx) << std::endl;

    bool parsed = cryptonote::parse_tx_extra(tx.extra, fields);
    if (!parsed)
      std::cout << "Failed to parse tx_extra" << std::endl;

    if (!fields.empty())
    {
      print_extra_fields(fields);
    }
    else
    {
      std::cout << "No fields were found in tx_extra" << std::endl;
    }
  }
  else if (((full = cryptonote::parse_tx_extra(std::vector<uint8_t>(blob.begin(), blob.end()), fields)) || true) && !fields.empty())
  {
    std::cout << "Parsed" << (full ? "" : " partial") << " tx_extra:" << std::endl;
    print_extra_fields(fields);
  }
  else
  {
    std::cerr << "Not a recognized CN type" << std::endl;
    return 1;
  }



  return 0;
}

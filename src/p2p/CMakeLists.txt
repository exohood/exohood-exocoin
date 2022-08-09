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
* Copyright (c) 2020 - 2022 Exohood Protocol
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

set(device_sources
  device.cpp
  device_default.cpp
  log.cpp
  )

if(HIDAPI_FOUND)
  set(device_sources 
    ${device_sources} 
    device_ledger.cpp
    device_io_hid.cpp
    )
endif()

set(device_headers
  device.hpp
  device_io.hpp
  device_default.hpp
  device_cold.hpp
  log.hpp
 )

if(HIDAPI_FOUND)
  set(device_headers 
    ${device_headers} 
    device_ledger.hpp
    device_io_hid.hpp
    )
endif()

set(device_private_headers)


exohood_private_headers(device
  ${device_private_headers})

exohood_add_library(device
  ${device_sources}
  ${device_headers}
  ${device_private_headers})

target_link_libraries(device
  PUBLIC
    ${HIDAPI_LIBRARIES}
    cncrypto
    ringct_basic
    ${OPENSSL_CRYPTO_LIBRARIES}
    ${Boost_SERIALIZATION_LIBRARY}
  PRIVATE
    version
    ${Blocks}
    ${EXTRA_LIBRARIES})

cmake_minimum_required (VERSION 2.6)
project (exohood CXX)

file(GLOB P2P *)
source_group(p2p FILES ${P2P})

#add_library(p2p ${P2P})

#exohood_private_headers(p2p ${P2P})
exohood_add_library(p2p ${P2P})
target_link_libraries(p2p
  PUBLIC
    version
    cryptonote_core
    net
    ${UPNP_LIBRARIES}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})

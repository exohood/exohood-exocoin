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

set(cn_deserialize_sources
  cn_deserialize.cpp
  )

exohood_add_executable(cn_deserialize
  ${cn_deserialize_sources}
  ${cn_deserialize_private_headers})

target_link_libraries(cn_deserialize
  LINK_PRIVATE
    cryptonote_core
    blockchain_db
    device
    ringct
    p2p
    epee
    ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET cn_deserialize
	PROPERTY
	OUTPUT_NAME "exohood-utils-deserialize")


set(object_sizes_sources
  object_sizes.cpp
  )

exohood_add_executable(object_sizes
  ${object_sizes_sources}
  ${object_sizes_private_headers})

target_link_libraries(object_sizes
  LINK_PRIVATE
    cryptonote_core
    blockchain_db
    p2p
    epee
    ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET object_sizes
	PROPERTY
	OUTPUT_NAME "exohood-utils-object-sizes")

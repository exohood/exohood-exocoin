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

if(MSVC OR MINGW)
  set(daemonizer_sources
    windows_service.cpp
    windows_daemonizer.inl
  )
else()
  set(daemonizer_sources
    posix_fork.cpp
    posix_daemonizer.inl
  )
endif()

set(daemonizer_headers
)

if(MSVC OR MINGW)
  set(daemonizer_private_headers
    daemonizer.h
    windows_service.h
    windows_service_runner.h
  )
else()
  set(daemonizer_private_headers
    daemonizer.h
    posix_fork.h
  )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG_TMPDIR_LOG=1)
endif()

electroneum_private_headers(daemonizer
  ${daemonizer_private_headers})
electroneum_add_library(daemonizer
  ${daemonizer_sources}
  ${daemonizer_headers}
  ${daemonizer_private_headers})
target_link_libraries(daemonizer
  PUBLIC
    common
    ${Boost_CHRONO_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
  PRIVATE
    ${EXTRA_LIBRARIES})

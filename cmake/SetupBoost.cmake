# Distributed under the MIT License. See LICENSE.txt for details.

if(APPLE)
  find_package(Boost REQUIRED)
else()
  find_package(Boost REQUIRED COMPONENTS system)
endif()

include_directories(${Boost_INCLUDE_DIR})

message(STATUS "Boost include: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")

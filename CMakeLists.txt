cmake_minimum_required(VERSION 3.30)
project(todo)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(todo main.cpp
        todo/include/Party.h
        todo/include/SecretShare.h
        todo/include/utils/ShareUtils.h

        todo/src/Party.cc
        todo/src/SecretShare.cc
        todo/src/utils/ShareUtils.cc

        todo/include/utils/constants.h
        todo/overflow/utilities.h
        todo/overflow/utilities.cc
        todo/include/ShamirSharing.h
        todo/src/ShamirSharing.cc
)

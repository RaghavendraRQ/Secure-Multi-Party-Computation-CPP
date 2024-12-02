cmake_minimum_required(VERSION 3.30)
project(todo)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(todo main.cpp
        todo/src/Task.cc
        todo/include/Task.h
        todo/include/TaskManager.h
        todo/src/TaskManager.cc
        todo/include/SecretShare.h
        todo/src/SecretShare.cc
        todo/include/Party.h
        todo/src/Party.cc
        todo/include/utils/constants.h
        todo/include/utils/ShareUtils.h
        todo/src/utils/ShareUtils.cc
)

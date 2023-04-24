cmake_minimum_required(VERSION 3.23)
project(TA_DFA_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(TA_DFA_1 main.cpp DFA.cpp DFA.h State.cpp State.h json.hpp RE.cpp RE.h ENFA.cpp ENFA.h Table.cpp Table.h)

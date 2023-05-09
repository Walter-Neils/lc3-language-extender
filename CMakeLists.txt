cmake_minimum_required(VERSION 3.25)
project(LC3_Language_Extender)

set(CMAKE_CXX_STANDARD 23)

add_executable(LC3_Language_Extender main.cpp PseudoOpCode.h StackOperations.cpp StackOperations.h StringPrintOpCode.cpp StringPrintOpCode.h SubtractOpCode.cpp SubtractOpCode.h)

cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(ex3 main.cpp Command.cpp Command.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h OpenServerCommand.cpp OpenServerCommand.h PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h WhileCommand.cpp WhileCommand.h AssignmentCommand.cpp AssignmentCommand.h IfCommand.cpp IfCommand.h)
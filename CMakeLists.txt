cmake_minimum_required(VERSION 3.26)
project(AED_PROJECT)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(AED_PROJECT main.cpp
        Student.cpp
        Student.h
        main.cpp
        UC.h
        UC.cpp
        LeicClass.h
        LeicClass.cpp
        Schedule.h
        Schedule.cpp
)

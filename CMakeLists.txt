cmake_minimum_required(VERSION 4.3)
project(Aegis_Scheduler)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/Job)

add_executable(Aegis_Scheduler
        src/Job/job.cpp
        src/Job/job.h
        main.cpp)

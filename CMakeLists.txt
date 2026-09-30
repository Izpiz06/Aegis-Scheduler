cmake_minimum_required(VERSION 3.20)
project(Aegis_Scheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/Job)

add_executable(Aegis_Scheduler
        src/Job/job_state.h
        src/Job/job_state.cpp
        src/Job/job.h
        src/Job/job.cpp
        main.cpp)

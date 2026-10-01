cmake_minimum_required(VERSION 3.20)
project(Aegis_Scheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/Job src/Resource src/Node src/Queue)

add_executable(Aegis_Scheduler
        src/Job/job_state.h
        src/Job/job_state.cpp
        src/Job/job.h
        src/Job/job.cpp
        src/Resource/resource.h
        src/Resource/resource.cpp
        src/Node/node_state.h
        src/Node/node_state.cpp
        src/Node/node.h
        src/Node/node.cpp
        src/Queue/job_queue.h
        src/Queue/job_queue.cpp
        main.cpp)

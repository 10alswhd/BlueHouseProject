cmake_minimum_required(VERSION 3.0)

project(cpu_consumer_kp)

include(FindPkgConfig)

pkg_search_module(smartslog REQUIRED smartslog)

find_library(M_LIB m)

include_directories(${smartslog_INCLUDE_DIRS})

link_directories(${smartslog_LIBRARY_DIRS})

add_executable(cpu_consumer_kp 
    main.c)

target_link_libraries(cpu_consumer_kp ${M_LIB})
target_link_libraries(cpu_consumer_kp  ${smartslog_LIBRARIES})

cmake_minimum_required(VERSION 3.5)

project(cjson_test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cJSON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/MemoryPool)

file(GLOB cjson ${CMAKE_CURRENT_SOURCE_DIR}/cJSON/cJSON.c)
file(GLOB mempool ${CMAKE_CURRENT_SOURCE_DIR}/MemoryPool/memorypool.c)
file(GLOB main ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

set(SRC_LIST ${cjson} ${mempool} ${main})

add_executable(app ${SRC_LIST})

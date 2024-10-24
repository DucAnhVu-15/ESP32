cmake_minimum_required(VERSION 3.0.0)
project(Modbus VERSION 0.1.0)

include(CTest)
enable_testing()


# # this one is important
SET(CMAKE_SYSTEM_NAME Linux)
# #this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# # specify the cross compiler
#SET(CMAKE_C_COMPILER   mipsel-openwrt-linux-musl-gcc)
#SET(CMAKE_CXX_COMPILER mipsel-openwrt-linux-musl-g++)

# # search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# # for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_executable(Modbus 
    src/main.cpp 
    src/wg_debug.cpp
    src/wg_modbus.cpp
    src/wg_convert.cpp
)

target_include_directories(Modbus PUBLIC include)
target_link_libraries(Modbus modbus mosquitto jsoncpp)

# find_library(PLOG_LIB plog)
# if(PLOG_LIB)
#     target_link_libraries(Modbus ${PLOG_LIB})
# else()
#     message("plog not found")
# endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
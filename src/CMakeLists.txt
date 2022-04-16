SET(SRC_LIST
    ./Server.cc
    ./Epoll.cc
    ./ThreadPool.cc
    ./Socket.cc
    ./error.cc
)
SET(INCLUDE_LIST
    ../include/Server.h
    ../include/ThreadPool.h
    ../include/Epoll.h
    ../include/Socket.h
    ../include/ConnecterQueue.h
    ../include/error.h
)

include_directories(../include)

# option(servermake "enable server complication" OFF)

# if(servermake)
add_executable(server ../server_chat.cc ${SRC_LIST} )
target_link_libraries(server pthread)
message('server make')
# else()
add_executable(client ../client_chat.cc ${SRC_LIST} )
target_link_libraries(client pthread)
message('client make')
# endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

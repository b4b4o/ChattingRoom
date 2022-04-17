SET(SRC_LIST
    ./Server.cc
    ./Client.cc
    ./Epoll.cc
    ./ThreadPool.cc
    ./Socket.cc
    ./error.cc
)

include_directories(../include)


add_executable(server ../server_chat.cc ${SRC_LIST} )
target_link_libraries(server pthread)
message('server make')

add_executable(client ../client_chat.cc ${SRC_LIST} )
target_link_libraries(client pthread)
message('client make')

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

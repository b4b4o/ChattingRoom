// #include "Server.h"
#include "./include/Server.h"

int main(int argc, char* args[]){

    std::unique_ptr<Server> server(new Server);
    server->start();

    return 0;
}
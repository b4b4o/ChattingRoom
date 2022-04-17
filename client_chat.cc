
#include "Client.h"

int main(int argc, char* args[]){
    srand(time(NULL));

    std::unique_ptr<Client> client(new Client());

    client -> start();

    return 0;
}
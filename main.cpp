//
// Created by naum on 27.09.2021.
//

#include <iostream>

#include "utils/config_parser.hpp"
#include "server/server.hpp"
#include <cstdio>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/socket.h>
#include <pthread.h>


void *task1(void *);

static int connFd;

int main(int argc, char** argv) {
//    std::string path = std::string("../httpd.conf");
//    if (argc > 1) {
//        path = std::string(argv[1]);
//    }
//
//    auto config = config_parser(path);
//
//    size_t port = 80;
//    if (argc > 2) {
//        port = std::stoi(argv[2]);
//    }
//    auto ser = server();
//    std::cout << ser.get_status(404) << std::endl << ser.get_method("HEAD");

    int pId, portNo, listenFd;
    socklen_t len; //store size of the address
    bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;

    pthread_t threadA[3];

    if (argc < 2)
    {
        std::cerr << "Syntam : ./server <port>" << std::endl;
        return 0;
    }

    portNo = atoi(argv[1]);

    if((portNo > 65535) || (portNo < 2000))
    {
        std::cerr << "Please enter a port number between 2000 - 65535" << std::endl;
        return 0;
    }

    //create socket
    listenFd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenFd < 0)
    {
        std::cerr << "Cannot open socket" << std::endl;
        return 0;
    }

    bzero((char*) &svrAdd, sizeof(svrAdd));

    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);

    //bind socket
    if (bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        std::cerr << "Cannot bind" << std::endl;
        return 0;
    }

    listen(listenFd, 5);

    len = sizeof(clntAdd);

    int noThread = 0;

    while (noThread < 3)
    {
        std::cout << "Listening" << std::endl;

        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);

        if (connFd < 0)
        {
            std::cerr << "Cannot accept connection" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Connection successful" << std::endl;
        }

        pthread_create(&threadA[noThread], NULL, task1, NULL);

        noThread++;
    }

    for(int i = 0; i < 3; i++)
    {
        pthread_join(threadA[i], NULL);
    }

    return 0;
}

void *task1 (void *dummyPt)
{
    std::cout << "Thread No: " << pthread_self() << std::endl;
    char test[300];
    bzero(test, 301);
    bool loop = false;
    while(!loop)
    {
        bzero(test, 301);


        read(connFd, test, 300);

        std::string tester (test);
        std::cout << tester << std::endl;


        if(tester == "exit")
            break;
    }
    std::cout << "\nClosing thread and conn" << std::endl;
    close(connFd);
    return nullptr;
}
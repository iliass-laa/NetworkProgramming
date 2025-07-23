#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <cstdlib>

#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


int clientTest(int i)
{
    char buff[1024];
    int readRet;
    std::string response;
    std::string msg[2] = {"FIRST MESSAGE !\n", "COLE Palmer , ICE COLDE\n"};
    if (i >= 2)
        return perror("Index is bigger!\n"),1;
    int socketfd;
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) 
        return (perror("Socket Creation\n"),1);
    std::cout << "Socket Fd : " << socketfd << "\n";
    if (-1 == connect(socketfd , (sockaddr *)&addr, sizeof(addr)))
        return (perror("Connect\n"),1);
    if (-1 == send(socketfd, msg[i].c_str(), msg[i].length(), MSG_CONFIRM))
        return (perror("Send\n"),1);
    readRet=recv(socketfd, (void *)buff, 1024, MSG_CONFIRM);
    if (-1 != readRet)
    {
        buff[readRet] = '\0';
        std::cout << "Response :" << buff << "<<"<< std::endl;
    }

    close(socketfd);
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return perror("PICK message!\n"),1;
    clientTest(atoi(av[1]));
    (void)ac;
    (void)av;
    return 0;
}
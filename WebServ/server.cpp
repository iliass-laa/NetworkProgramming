#include "headers/webserver.hpp"
#include "headers/structs.hpp"

#include <string.h>
#include <cerrno>


void testSocket()
{
    t_request req;
    t_response res;
    int readed, socket_fd, bind_ret, listen_ret, client_fd;
    char buffer[1024];
    std::string response = "HTTP/1.1 200 OK\r\n\r\nHello from webserv!";
    std::string responseMsg = "SERVER SAYS BACK :GOT IT";
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind_ret = bind(socket_fd, (sockaddr *)&addr, sizeof(addr) );
    if (bind_ret == -1)
    {
        std::cout <<"Bind\n";
        std::cout <<strerror(errno) << std ::endl;
        exit(1);
    }
    listen_ret = listen(socket_fd, 100);
    if (listen_ret == -1)
    {
        std::cout << "Listen\n";
        return ;
    }
    while (true)
    {
        // std::cout <<"WHILE\n";
        client_fd = accept(socket_fd,  NULL, NULL);
        if (client_fd == -1)
        {
            std::cout << "Accept Failed\n";
            break;
        }
        memset(&buffer, 0, 1024);
        // readed = read(client_fd,buffer, 1024);
        readed = recv(client_fd,buffer, 1024, MSG_CONFIRM);
        if (readed)
        {
            std::string tmp = buffer;
            try
            {
                parseRequest(tmp);
                try
                {
                    sendtheRightResponse(client_fd);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';            
                }
                
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                // std::cout << "Parsing Request Failed !\n";
            }
            
           
            std::cout   << "------------------------------------------------------------\n" 
                        << "Client Says :\n" 
                        << buffer 
                        << "------------------------------------------------------------" 
                        << std::endl;
        // write(client_fd, responseMsg.c_str(), responseMsg.size());

        }
        send (client_fd, response.c_str(), response.length(), MSG_CONFIRM);
        if (client_fd != -1)
            close(client_fd);
    }
    close(socket_fd);
}
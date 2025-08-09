#include "../headers/webserver.hpp"
#include "../headers/structs.hpp"

int sendtheRightResponse(int client_fd, t_request &req){
    if (client_fd)
    {
        std::cout << "Server is Sending A socket to this client :" + req.header.UserAgent + "\n" ;
        
    }
    return 0;
}


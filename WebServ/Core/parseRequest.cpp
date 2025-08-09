#include "../headers/webserver.hpp"


int parseRequest(std::string request, t_request req)
{

    if (request.length() == 0)
        return 1;
    std::cout << "Request Lenght : " << request.length() << "\n"; 
    
    
    req.requestBody = "Request Body";
    return 0;
}


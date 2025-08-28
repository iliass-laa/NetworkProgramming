#include "../headers/webserver.hpp"



void core(std::string reqStr, int client_fd, BaseNode *root)
{
    t_request req;
    try
    {
        parseRequest(reqStr, req);
        try {
            sendtheRightResponse(client_fd, req, root);
        }
        catch(std::exception &e)
        {
            std::cerr << e.what();
        }
    }
    catch (std::exception &e)
    {
        std::cout << "<<<Undone\n";
        std::cerr << e.what() << "\n";
        // std::cout << e.what() << "\n";
    }
}
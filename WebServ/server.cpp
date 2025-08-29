#include "headers/webserver.hpp"


int nbrReq;

int findPort(BaseNode *root)
{
    ContextNode *node, *tmp;
    DirectiveNode *Dnode;
    node = dynamic_cast<ContextNode *>(root); 
    if (root->typeNode != isDirective)
    {
        node = dynamic_cast<ContextNode *>(root);
        if(node->type_Context == MainContext)
        {
            for (int i = 0; i < node->nbrChildsC+node->nbrChildsD ; i++)
            {
                if (node->Childs[i]->typeNode == isContext)
                {
                    tmp =  dynamic_cast<ContextNode *>(node->Childs[i]);
                    if (tmp->type_Context == HttpContext)
                    {
                        node = tmp;
                        break;
                    }
                }
            }
        }
    }
    if (node->type_Context == HttpContext)
    {
        // std::cout << "Max Childs for Http Context::"<< node->nbrChildsC+node->nbrChildsD << "\n";
        for (int i = 0; i < node->nbrChildsC+node->nbrChildsD ; i++)
        {
            if (node->Childs[i]->typeNode == isContext)
            {
                tmp =  dynamic_cast<ContextNode *>(node->Childs[i]);
                if (tmp->type_Context == ServerContext)
                {
                    node = tmp;
                    break;
                }
            }
        }
    }

    if (node->type_Context == ServerContext)
    {
        // std::cout << "Max For Server Context::"<< node->nbrChildsC+node->nbrChildsD << "\n";
        for (int i = 0; i < node->nbrChildsC+node->nbrChildsD ; i++)
        {
            if (node->Childs[i]->typeNode == isDirective)
            {
                Dnode =  dynamic_cast<DirectiveNode *>(node->Childs[i]);
                if (Dnode->key.compare("listen") == 0)
                    return (std::atoi(Dnode->value.back().c_str()));
            }
        }
    }
    return -1;
}

void testSocket(char *path, BaseNode *root)
{
    int epollFd = -1;
    // ConfigFileInfos cnfInfo;
    t_request req;
    t_response res;
    int readed, socket_fd, bind_ret, listen_ret, client_fd;
    char buffer[1024];
    // parseConfigFile(path,cnfInfo);
    root = parseConfigFile(path);
    std::string response = "HTTP/1.1 200 OK\r\n\r\nHello from webserv!";
    std::string responseMsg = "SERVER SAYS BACK :GOT IT";
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr, clientInfo;
    socklen_t clInfoLen = sizeof(clientInfo);
    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));


    addr.sin_family = AF_INET; 
    int port = findPort(root);
    std::cout << ">>>>>>Port ::" << port << "\n";
    if (port < 0)
        throw(ConfigFileError("Port Nbr\n"));
    addr.sin_port = htons(8081);
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
    std::cout <<"ALL good\n";
    while (true)
    {
        client_fd = accept(socket_fd, (struct sockaddr *)&clientInfo, &clInfoLen);
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientInfo.sin_addr, ip, sizeof(ip));
        if (client_fd == -1)
        {
            std::cout << "Accept Failed\n";
            break;
        }
        else    
            nbrReq ++;
        memset(&buffer, 0, 1024);
        // readed = read(client_fd,buffer, 1024);
        readed = recv(client_fd,buffer, 1024, MSG_CONFIRM);
        if (readed)
        {
            
            std::cout   << "------------------------------------------------------------\n" 
                        << BLUE<<"Client with IP : " <<ip <<" Says :\n" 
                        << buffer 
                        << RED<<"\n------------------------------------------------------------\n"
                        <<DEF;
            core(buffer, client_fd, root);
        }
        // send (client_fd, response.c_str(), response.length(), MSG_CONFIRM);
        if (client_fd != -1)
            close(client_fd);
        std::cout << "Nbr Requets ::" << nbrReq << "<<\n";
    }
    // freeTree(root);
    close(socket_fd);
    std::cout << "epoolfd : "<< epollFd << std::endl;


    (void)response;
}
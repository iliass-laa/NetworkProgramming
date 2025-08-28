#include "../../headers/webserver.hpp"


std::string getFullPath(t_request &req, std::string rootPath, int *f_or_D, std::string &fileName )
{
    std::string tmp,res;
    DIR *dir = NULL;
    size_t pos;
    
    tmp = rootPath + req.headers.path;
    dir = opendir(tmp.c_str());
    
    if (dir || tmp.at(tmp.length() - 1) == '/')
    {
        if (dir)
        {
            closedir(dir);
        }
        *f_or_D = 1;
        return tmp;
    }
    pos = tmp.find_last_of('/');
    fileName = tmp.substr(pos + 1, tmp.length());
    res = tmp.substr(0, pos);
    return res;
}


int foundIndex(ContextNode *location, std::vector<std::string> &indexes)
{
    DirectiveNode *tmp;
    for(int i = 0; i < location->nbrChildsD + location->nbrChildsC; i++ )
    {
        if (location->Childs[i]->typeNode == isDirective)
        {
            tmp = dynamic_cast<DirectiveNode *>(location->Childs[i]);
            if (tmp->key.compare("index") == 0)
            {
                indexes = tmp->value;
                return 1;
            }
        }

    }
    return 0;
}

int dirListing(ContextNode *location)
{
    DirectiveNode *tmp;
    for(int i = 0; i < location->nbrChildsD + location->nbrChildsC; i++ )
    {
        if (location->Childs[i]->typeNode == isDirective)
        {
            tmp = dynamic_cast<DirectiveNode *>(location->Childs[i]);
            if (tmp->key.compare("autoindex") == 0 && !tmp->value.at(0).compare("on"))
                return 1;
        }

    }
    return 0;
}


void    redirectClient(int client_fd, std::string dir)
{
    std::cout <<GREEN<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>REDIRECTING >>>>\n"<< DEF;
    std::string red = "HTTP/1.1 301 Moved Permanently\nLocation: "+dir+"/\nContent-Length: 0\nConnection: keep-alive";
    send(client_fd, red.c_str(), red.size(), MSG_CONFIRM);
}

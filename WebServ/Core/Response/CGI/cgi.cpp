#include "../../../headers/webserver.hpp"



CgiExtensions checkExtension(std::string path)
{
    if (path.find_last_of(".py") == path.length() - 3)
        return py;
    if (path.find_last_of(".php") == path.length() - 4)
        return php;
    return NONE;
}


void            handleCGI(int client_fd,t_request &req,BaseNode *root)
{
    CgiExtensions ex;
    int p[2];
    int pid;

    ex = checkExtension(req.headers.path);
    getReqInfos(req, root);
    pipe(p);
    pid = fork();
    if (pid == 0)
    {

    }
    else{

    }
}

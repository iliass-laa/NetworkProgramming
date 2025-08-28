#include "../../headers/webserver.hpp"


std::string getPath(t_request &req, BaseNode *root)
{

    std::string res;
    res = req.headers.path + root->typeNode; 

    return res;
}

int executeProg(t_request &req,BaseNode *root,char **env)
{
    int ret;
    std::string path;
    path = getPath(req,root);
    ret = execve(path.c_str(), NULL, env);
    return ret;
}

void    handleCGI(int client_fd,t_request &req,BaseNode *root)
{
    int pid, res;
    char **env;

    env = getEnv(req);
    pid = fork();
    if (pid ==0)
    {
        res = executeProg(req, root, env);
    }
    
}


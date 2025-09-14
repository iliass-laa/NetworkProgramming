#include "../../../headers/webserver.hpp"



CgiExtensions checkExtension(std::string path)
{
    if (path.rfind(".py") == path.length() - 3)
        return py;
    if (path.rfind(".php") == path.length() - 4)
        return php;
    // path.fin
    return NONE;
}


int execCGI(t_request &req, char **env, CgiExtensions ext)
{
    std::string strArg;
    std::string interpreter[3] = {"/usr/bin/bash", "/usr/bin/php","/usr/bin/python3" };
    char *arg[3];
    int pos, ret;
 
    std::string extention[4]= {"bash", "php", "py", "NONE"};
    pos = req.headers.path.find("/cgi-bin");
    strArg =  req.headers.path.substr(pos + 8, req.headers.path.length());
    strArg = req.rootDir + strArg;
    arg[0] = ft_strcopy(extention[ext].c_str(), extention[ext].length());
    arg[1] = ft_strcopy(strArg.c_str(), strArg.length());
    arg[2] =  NULL;
    ret =  execve(interpreter[ext].c_str(),arg, env);
    free(arg[0]);
    free(arg[1]);
    free_D_Array(env);
    return ret;
}


int            handleCGI(int client_fd,t_request &req,BaseNode *root)
{
    std::cout << PINK <<"Handle CGI !\n" << DEF;
    std::string response;
    CgiExtensions ex;
    char **env, buff[1023];
    int p[2];
    int pid, readed, ret;

    getReqInfos(req, root);
    ex = checkExtension(req.headers.path);
    std::cout << RED <<"CGI Extension is "<<ex<< DEF <<"!\n" ;
    if (ex == NONE)
    {
        std::cout << RED <<"CGI Extension is not allowed !\n" << DEF;
        handleCGIError(req, client_fd);
        return 1;
    }
    pipe(p);
    pid = fork();
    if (pid == 0)
    {
        env = getEnv(req);
        dup2(p[1], 1);
        close(p[0]);
        ret = execCGI(req, env, ex);
        exit(ret);
    }
    else {
        close(p[1]);
        int childRet = 0;
        wait(&childRet);
        if (childRet)
        {
            std::cout << RED <<"CGI Script didn't executed properly ! return val:"<<childRet<<"\n" << DEF;
            handleCGIError(req, client_fd);
        }
        else if (childRet == 0)
        {
            readed = read(p[0], buff, 1024);
            while (readed)
            {
                buff[readed] = '\0';
                response += buff;
                readed = read(p[0], buff, 1023);
            }
            sendSuccesHeader(client_fd);
            send(client_fd, response.c_str(), response.length(), MSG_CONFIRM);
        }
        close(p[0]);

        // (void)childRet;
    }
    return 0;
}

#include "../../headers/webserver.hpp"
// #include "../../headers/structs.hpp"


void errorHandling(int client_fd , errors errType)
{
    std::cerr << "\t>>ERROR 404<<\n";
    (void)client_fd;
    // (void)root;
    (void)errType;
}



response_Types get_Res_T(t_request &req)
{
    if (req.headers.path.find("cgi") == 1)
        return CGI;
    if (req.headers.path.find("api") == 1)
        return REVERSE_PROXY;
    return STATIC;
} 
ContextNode *findServerByHost(t_request &req,BaseNode *root)
{
    ContextNode *tmp;

    tmp = findHttpContext(root);
    if (!tmp)
        return NULL;
    tmp = findServerContext(tmp, req.headers.hostname, req.headers.port);
    return tmp;
}
void    handleStatic(int client_fd,t_request &req, BaseNode *root)
{
   
    int lookingForDir;
    ContextNode *location;
    std::string HostName, fullPath, rootPath, fileTarget;
    std::vector <std::string> indexes;
    DIR *dir;
    fileTarget = "NONE";
    
    lookingForDir = 0;
    rootPath = getRootPath(root, req, &location);
    fullPath =  getFullPath(req, rootPath, &lookingForDir, fileTarget);
    // std::cout << PINK <<"Location Working With :" << location->val.back() << "<\n"<<DEF;
    dir = opendir(fullPath.c_str());
    if (!dir)
    {
        errorHandling(client_fd, PATH_NOT_FOUND);
        return;
    }
    if (lookingForDir)
    {
        if (fullPath.at(fullPath.length() -1) != '/')
        {
            redirectClient(client_fd, req.headers.path);
            return;
        }
        // std::cout << "Looking For Dir\n";
        if (foundIndex(location, indexes))
        {
            // std::cout <<GREEN<< ">>Founde Index "+indexes.at(0)+" >>>>\n"<< DEF;
            for(size_t i = 0;i < indexes.size(); i++)
            {
                std::cout << "this the Index Trying to :"+fullPath+indexes[i]+"\n";
                if  (serveFile(client_fd, dir, indexes.at(i), fullPath))
                    break;
            }
        }
        else
        {
            // std::cout <<GREEN<< ">>No index is Founded >>>>\n"<< DEF;
            if (dirListing(location))
                serveDir(client_fd, dir, req.headers.path);
            else
                errorHandling(client_fd, PATH_NOT_FOUND);
        }
    }
    else
    {
        // std::cout << "Looking For File\n";
        if (serveFile(client_fd, dir, fileTarget, fullPath))
        {
            std::cout << "U Fucked it here\n";
            errorHandling(client_fd, PATH_NOT_FOUND);
        }
    }
    closedir(dir);
}

int sendtheRightResponse(int client_fd, t_request &req, BaseNode *root)
{
    response_Types rT= get_Res_T(req); 
    switch (rT)
    {
        case REVERSE_PROXY:
            // handleReverseProxy(client_fd, req);
            break;
        case CGI:
            // handleCGI(client_fd, req, root);
            break;
        default:
            handleStatic(client_fd, req, root);
            break;
    }
    // std::
    return 0;
}


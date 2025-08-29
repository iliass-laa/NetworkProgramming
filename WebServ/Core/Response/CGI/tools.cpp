#include "../../../headers/webserver.hpp"


char *ft_strcopy(const char *s, int size)
{
    int i = 0;
    char *res;
    if (!size)
        return NULL;
    res = (char *)malloc(size + 1);
    while( i < size)
    {
        res[i] = s[i];
        i++;
    }
    res[i] = '\0';
    return res;
}



char **getEnv(t_request &req)
{
    std::map <std::string, std::vector <std::string> >::iterator it;
    size_t i,size;
    std::string line;
    char **res;

    size = req.headers.additionalHeaders.size();
    std::cout << "ENV SIZE :" << size <<"\n";
    i = 0;
    if (size == 0)
        return NULL;
    res = (char **)malloc((sizeof(char *)) * (size + 1));
    if (!res)
    {
        std::cerr << "MALLOC FAILED \n";
        return NULL;
    }
    it = req.headers.additionalHeaders.begin();
    while (i < size)
    {
        line  = it->first+"=";
        for(size_t j = 0; j < it->second.size(); j ++)
        {
            line+= (it->second[j] + ",");
        }
        // std::cout << ">>" + line +"| line Size:"<< line.size() << "\n";
        res[i] = ft_strcopy( line.c_str(), line.size());
        // std::cout << ">>"<<res[i] << "| i:"<< i << "\n";
        
        it++;
        i++;
    }
    res[i] = NULL;
    return res;
}



ContextNode* findRightServer(t_request &req,BaseNode *root)
{
    ContextNode *tmp1, *tmp2;
    DirectiveNode *d;

    tmp1 = findHttpContext(root);
    if (!tmp1)
        return NULL;
    tmp2 = findServerContext(tmp1, req.headers.hostname, req.headers.port);
    req.server = tmp2;
    if (!tmp2)
        return NULL;
    d = findDirectiveChild(tmp2, "root");
    if (d)
        req.rootDir = d->value.back();
    return tmp2;
}

ContextNode     *findRightLocation(t_request &req, ContextNode *server)
{
    DirectiveNode *d;
    ContextNode *loc;
    if (!server)
        return NULL;
    loc = findLocationContext(server, req.headers.path);
    d = findDirectiveChild(loc, "root");
    if (d)
        req.rootDir = d->value.back();
    req.location = loc;
    return loc;
}


void getReqInfos(t_request & req,BaseNode *root)
{
    req.server = findRightServer(req, root);
    req.location= findRightLocation(req, req.location);
}
    
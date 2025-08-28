#include "../../headers/webserver.hpp"


char *ft_strcopy(const char *s, int size)
{
    int i = 0;
    char *res;
    if (!size)
        return NULL;
    res = (char *)malloc(size + 1);
    while( i< size)
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
    i = 0;
    if (size == 0)
        return NULL;
    res = (char **)req.headers.additionalHeaders.size() + 1;
    it = req.headers.additionalHeaders.begin();
    while (i < size)
    {
        line  = it->first+"=";
        for(size_t j = 0; j < it->second.size(); j ++)
        {
            line+= it->second[j];
        }
        res[i] = ft_strcopy( line.c_str(), line.size());
        it++;
        i++;
    }
    res[i] = NULL;
    return res;
}


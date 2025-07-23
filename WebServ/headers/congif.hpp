# ifndef CONFIG_HPP
# define CONFIG_HPP

#include "webserver.hpp"

struct LocationConfig
{
    std::string path;
    std::string root;
    std::string index;
};




struct ServerConfig
{
    int port;
    std::string serverName;
    // std::map <>
};






#endif
# ifndef STRUCTS_HPP
# define STRUCTS_HPP

#include "includes.hpp"





enum methods{
    GET,
    POST,
    UPDATE,
    DELETE
};

typedef struct s_request_header t_request_header;
typedef struct s_request t_request;
typedef struct s_response t_response;
typedef enum methods t_methods;


// enum connectionTypes{
//     GET,
//     POST,
//     UPDATE,
//     DELETE
// };

struct s_request_header
{
    t_methods method;
    std::string UserAgent;

};


struct s_request
{
   t_request_header header;
   std::string requestBody;
};
struct s_response
{
    std::string responseBody;
};



#endif
#include "../headers/webserver.hpp"


void printMethod(t_methods M)
{
    std::string Methods[3] = {"GET", "POST", "DELETE"};
    std::cout << Methods[M];
}

void printVal(std::vector <std::string> v)
{
    std::vector <std::string> ::iterator it;

    it = v.begin();
    while (it != v.end())
    {
        std::cout << " "<<*it ;
        it++;
    }
}


void printRequest(t_request req)
{
    printMethod(req.headers.method);
    std::cout << ' ' << req.headers.path<<" " << req.headers.httpV << "\r\n";
    std::map <std::string , std::vector <std::string> > ::iterator it;

    it = req.headers.additionalHeaders.begin();
    while (it != req.headers.additionalHeaders.end())
    {
        std::cout << "H_Key :"<<it->first << " ::H_Val:" ;
        printVal(it->second); 
        std::cout << "\r\n";
        it++;
    }

}
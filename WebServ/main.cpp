#include "headers/webserver.hpp"


int main(int ac, char **av)
{
    BaseNode *root = NULL;
    if (ac == 2){   
        try {
            testSocket(av[1], root);
            freeTree(root);
        }  
        catch (std::exception &e)
        {
            std::cerr << "Caught an Error in the main\n";
            std::cerr << e.what() << std::endl;
        }
    }
    else    
    {
        std::cerr << "Need a config File first!"<< std::endl;
        return 1;
    }
    return 0;
}
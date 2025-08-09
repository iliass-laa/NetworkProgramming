#include "../headers/webserver.hpp"



void printSpaces(int level)
{
    for(int i = 0; i < level; i++)
    {
        std::cout << " ";
    }
    std::cout << "->";
}

void    printDirective( DirectiveNode * root,int Level)
{
    printSpaces(Level);
    std::cout << root->key <<  "\n";
    for(int i = 0 ; static_cast<size_t>(i) < root->value.size(); i++)
    {
        printSpaces(Level);
        std::cout <<"D_value:" + root->value[i]<<  "\n";
    }
}


void    printTypContextandVal(int type, std::vector <std::string> &val, int level)
{
    std::string Contexts[6] = {"main", "events","http", "types", "server", "location"};
    for(int i = 0; i < 6;i++)
    {
        if (i==type)
           std::cout << "typeC:"+ Contexts[i] +  " Level:" <<(level / 3) << " ";
    }
    for(size_t i = 0; i < val.size();i++)
        std::cout << val[i] << " ";
    std::cout << "\n";
}


void    printfContext(ContextNode *node, int level)
{
    printSpaces(level);
    printTypContextandVal(node->type_Context, node->val,level);
    for(size_t i = 0; i < node->Childs.size();i++)
    {
        if (node->Childs[i]->typeNode == isDirective)
            printDirective(dynamic_cast<DirectiveNode*>(node->Childs[i]), level);
        else
            printfContext(dynamic_cast<ContextNode*>(node->Childs[i]), 3 + level);
    }
}


void printTree(BaseNode * root, int Level)
{
    printfContext(dynamic_cast<ContextNode*>(root), Level);
}

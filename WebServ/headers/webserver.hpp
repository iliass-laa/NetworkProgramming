#ifndef WEBSERV_HPP
#define WEBSERV_HPP


#include "includes.hpp"
#include "structs.hpp"
#include "config.hpp"
#include "classes.hpp"
#include "AST.hpp"


void testSocket(char *path);
// void parseConfigFile(char *path, ConfigFileInfos &obj);
void parseConfigFile(char *path);
int parseRequest(std::string request, t_request req);
int sendtheRightResponse(int client_fd,  t_request &req);
// int sendtheRightResponse(int client_fd,t_request req);

BaseNode *buildTree(TokenizerData &tk);
void printTree(BaseNode * root, int);
void freeTree(BaseNode *root);

#endif

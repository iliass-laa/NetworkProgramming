#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

void testSocket();
int parseRequest(std::string &request);
int sendtheRightResponse(int client_fd,  t_request &req);

#endif
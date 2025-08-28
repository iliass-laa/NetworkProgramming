#include "../../headers/webserver.hpp"


int generateSuccfullRespons(int client_fd, std::string path)
{
    std::fstream file;
    std::string line;
    file.open(path.c_str());
    // std::cout << "this the Path :" << path << "\n";
    if (file.fail())
    {
        std::cout << "Fail to Open the File\n";
        return 1;
    }
    sendSuccesHeader(client_fd);
    while (std::getline(file, line))
    {
        line +=  "\n";
        if (send (client_fd, line.c_str(), line.length(), MSG_CONFIRM) == -1)
            std::cerr <<"Send FAILED !(to send SuccesBODY)\n";
    }
    file.close();
    return 0;
}

void    sendSuccesHeader(int client_fd)
{
    std::string succesHeader = "HTTP/1.1 200 OK\r\n\r\n";
    if (send (client_fd, succesHeader.c_str(), succesHeader.length(), MSG_CONFIRM) == -1)
        std::cerr <<"Send FAILED ! (to send SuccesHeader)\n";
}


int serveFile(int client_fd, DIR *dir,std::string fileTarget, std::string fullPath)
{

    struct dirent *readed;
    std::string tmp;

    // std::cout << "SERVING THIS FILE :"+fileTarget+"\n";
    readed  = readdir(dir);
    while (readed)
    {
        if (!fileTarget.compare(readed->d_name))
        {
            // std::cout << "Found the Right File\n";
            return generateSuccfullRespons(client_fd,fullPath+"/" + fileTarget);
            
        }
        readed  = readdir(dir);
    }
    (void)client_fd;
    return 0;
}

void serveDir(int client_fd, DIR *dir, std::string dirName)
{
    struct dirent *readed;
    std::string responseHeader, responseBody, fullResp, fName;
    
    // std::cout << RED << "Listnnig Dir:\n" <<DEF; 
    sendSuccesHeader(client_fd);
    readed  = readdir(dir);
    responseHeader = "<head><title>Index of"+dirName+"</title></head>";
    responseBody = "<body><h1>Index of"+dirName+"</h1><hr><pre>";
    while (readed)
    {
        fName = readed->d_name;
        if (fName.compare("."))
        {
            if (readed->d_type == DT_DIR)
                fName+= "/";
            responseBody += "<a href=\""+fName+"\">"+fName+"</a>\n";
        }
        readed  = readdir(dir);
    }
    responseBody += "</pre><hr></body>";
    fullResp = "<html>" + responseHeader + responseBody + "</html>";
    if (send (client_fd, fullResp.c_str(),fullResp.length(), MSG_CONFIRM) == -1)
        std::cerr <<"Send FAILED ! (to send fullResp)\n";
}
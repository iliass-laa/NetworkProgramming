#include "../../headers/webserver.hpp"


t_methods allowedMetods(std::string meth)
{
    if (!meth.compare("GET"))
        return GET;
    if (!meth.compare("POST"))
        return POST;
    if (!meth.compare("DELETE"))
        return DELETE;
    return NOTALLOWED;
}

int checkFirstLine(std::string fline, t_request &req)
{
    std::size_t pos;
    std::string method, path, httpV;
    t_methods m;
    pos = fline.find(" ");
    if (pos== std::string::npos)
        throw(RequestError());
    method = fline.substr(0, pos);
    // std::cout << "Method is ::" << method << "<<<<<\n";
    m = allowedMetods(method);
    if (m == NOTALLOWED)
        return 1;
    fline = fline.substr(pos + 1, fline.length());
    pos = fline.find(" ");
    path = fline.substr(0,pos);
    if (path.find("/") == std::string::npos)
        return 1;
    fline = fline.substr(pos + 1, fline.length());
    pos = fline.find("\r\n");
    httpV = fline.substr(0,pos);
    if (httpV.compare("HTTP/1.1") && httpV.compare("HTTP/1.0"))
        return 1;
    req.headers.httpV = httpV;
    req.headers.method = m;
    req.headers.path = path;
    return (0);
}


int checkRplicatedVal(t_request &req,  std::pair <std::string, std::vector<std::string> > &p)
{
    size_t Rmax, Pmax;

    std::map  <std::string, std::vector<std::string> > ::iterator itF, itL ;
    std::vector <std::string> ::iterator itVL;
    itL = req.headers.additionalHeaders.end();
    itF = req.headers.additionalHeaders.begin();

    if (req.headers.additionalHeaders.find(p.first) != itL)
    {
        Pmax = p.second.size();
        Rmax = req.headers.additionalHeaders.at(p.first).size();
        for(size_t i = 0; i < Rmax ; i++ )
        {
            for(size_t j = 0; j < Pmax ; j++ )
            {
                if (req.headers.additionalHeaders.at(p.first).at(i).compare(p.second.at(j)) == 0)
                    return 1;
            }
        }
        itVL =  req.headers.additionalHeaders.at(p.first).end(); 
        req.headers.additionalHeaders.at(p.first).insert(itVL,  p.second.begin(), p.second.end());
        return 2;
    }
    // std::cout << "NO DUPLICATED !\n";
    return 0;
}

void fillAddHeaders(t_request &req, std::string key, std::string val)
{
    std::pair <std::string, std::vector<std::string> > p;
    std::string tmpVal;
    std::size_t commaPos;
    int check;
    commaPos = val.find(",");
    if (commaPos != std::string::npos)
    {
        p.first = key;
        while (commaPos!= std::string::npos)
        {
            tmpVal = val.substr(0, commaPos);
            if (val[commaPos + 1] != ' ')
                val =  val.substr(commaPos + 1, val.length());
            else
                val =  val.substr(commaPos + 2, val.length());
            p.second.push_back(tmpVal);
            commaPos = val.find(",");
        }
        p.second.push_back(val);
        check = checkRplicatedVal(req, p); 
        if (check  == 1)
        {  
            std::cerr << "this is the Replicated :" << p.first << "\n";
            throw (RequestError("Replicated Values in the Header of the Request!"));
        }
        if (check == 0)
            req.headers.additionalHeaders.insert(p);
    } 
    else
    {
        // std::cout << "Nbr of Headers :"<< req.headers.additionalHeaders.size() << "<<\n";
        p.first = key;
        p.second.push_back(val);
        check = 45;
        check = checkRplicatedVal(req, p); 
        // std::cout << "CHECK :" <<check << "\n";
        if (check == 1)
        {
            std::cerr << "this is the Replicated :" << p.first << "\n";
            throw (RequestError("Replicated Values in the Header of the Request!"));
        }
        if (check == 0)
            req.headers.additionalHeaders.insert(p);
        // std::cout << "FIll ADDR>>>>>>>>>>>>>>DONE\n";
   }
}


void fillRequest(std::string request_str,t_request  &req)
{
    std::string line, val, key, rest;
    std::size_t nlpos, ppos;
    nlpos = request_str.find("\r\n");
    ppos = 0;
    if (nlpos == std::string::npos)
    {
        std::cout <<"???????????????Nasa\n";
        throw (RequestError());   
    }
    while(nlpos != std::string::npos)
    {
        line = request_str.substr(0, nlpos);
        if (line.length() ==0)
            break;
        // std::cout << "line Working On :>>" + line <<  "<< size:" << line.length()<<"\n";
        rest = request_str.substr(nlpos + 2 , request_str.length());
        ppos = line.find(":");
        if (ppos == std::string::npos)
            throw (RequestError("NO : Founded \n"));
            
        key = line.substr(0, ppos);
        val = line.substr(ppos + 2, line.length());
        fillAddHeaders(req, key, val);
        request_str = rest;
        nlpos = request_str.find("\r\n");
    }

    
}

void     getHostName(t_request &req)
{
    std::size_t pos;
    int port;
    std::string hostName;
    std::map <std::string , std::vector <std::string>  >::iterator it;
    
    it = req.headers.additionalHeaders.find("Host");
    if (it == req.headers.additionalHeaders.end())
        throw(RequestError("NO host Name founded\n"));
    pos = it->second.back().find(":");
    if (pos== std::string::npos)
        throw(RequestError("NO host Name founded\n"));
    hostName = it->second.back().substr(0, pos);
    port = std::atoi(it->second.back().substr(pos+1, it->second.back().length()).c_str());
    req.headers.hostname = hostName;
    req.headers.port = port;
}

int parseRequest(std::string request_str, t_request &req)
{
    if (request_str.length() == 0)
        return 1;
    std::size_t pos;
    std::string line;
    pos = request_str.find("\r\n");
    if (pos== std::string::npos)
        throw(RequestError());
    line = request_str.substr(0, pos);
    request_str = request_str.substr(pos + 2, request_str.length());
    if (checkFirstLine(line, req))
        throw(RequestError());
    fillRequest(request_str, req);
    getHostName(req);
    // std::cout << "---------------Printing requst after being Parsed !---------------\n";
    // printRequest(req);
    // std::cout << "\n---------------//////---------------\n";
    return 0;
}


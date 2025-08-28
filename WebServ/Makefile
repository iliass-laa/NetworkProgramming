CPP = c++

CGI = Core/Response/CGI/cgi.cpp \
		Core/Response/CGI/tools.cpp

ResponseFiles = Core/Response/response.cpp \
				 Core/Response/sending.cpp \
				 Core/Response/tools.cpp\
				 $(CGI)


CoreFiles =  Core/core.cpp Core/utils.cpp\
			Core/Request/parseRequest.cpp \
			$(ResponseFiles)
ParseFiles = configParse/parseConfigFile.cpp\
			configParse/buildTree.cpp\
			configParse/utils.cpp\
			configParse/freeTree.cpp configParse/greatTools.cpp \
			configParse/findContexts.cpp 
CPPFILES = $(ParseFiles) $(CoreFiles) \
			server.cpp main.cpp 
CPPHEADERS = headers/*
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g
OBJ = $(CPPFILES:.cpp=.o)
NAME = webserv

all : $(NAME)


%.o : %.cpp $(CPPHEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@


$(NAME) : $(OBJ)
	$(CPP) $(CPPFLAGS) $^ -o $@


clean : 
	rm -rf $(OBJ)


fclean : clean	
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re




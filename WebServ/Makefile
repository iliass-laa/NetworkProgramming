CPP = c++


ParseFiles = configParse/parseConfigFile.cpp \
			configParse/buildTree.cpp\
			configParse/utils.cpp\
			configParse/freeTree.cpp
CPPFILES = Core/response.cpp Core/parseRequest.cpp\
			server.cpp main.cpp $(ParseFiles)
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




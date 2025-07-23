CPP = c++
CPPFILES = Core/parseRequest.cpp server.cpp main.cpp
CPPHEADERS = headers/*
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
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




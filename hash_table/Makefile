
NAME		= hash_table
SRCS		= src/main.cpp
OBJS		= $(SRCS:.cpp=.o)

OPTI		= 
IPATH		= -I.
OBJOPT	= $(OPTI) -W -Wall -std=c++11
CXXFLAGS	= $(OBJOPT) $(IPATH)
CXX		= g++

.PHONY		: clean fclean re

all		: $(NAME)

$(NAME)		: $(OBJS)
		  $(CXX) $(OBJS) -o $(NAME)

clean		:
		  $(RM) $(OBJS) *~ src/*~ incl/*~

fclean		: clean
		  $(RM) $(NAME)

re		: fclean all

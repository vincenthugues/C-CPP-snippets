
NAME		= hash_table
SRCS		= src/main.cpp		\
		src/HashTable.cpp
OBJS		= $(SRCS:.cpp=.o)

OPTI		= 
IPATH		= -I.
OBJOPT	= $(OPTI) -W -Wall
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

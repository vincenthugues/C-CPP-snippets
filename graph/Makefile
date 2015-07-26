
NAME		= graph
SRCS		= src/main.cpp		\
		  src/Graph.cpp		\
		  src/Vertex.cpp	\
		  src/Edge.cpp		\
		  src/Matrix.cpp	\
		  src/FileParser.cpp
OBJS		= $(SRCS:.cpp=.o)

OPTI		= -O3
IPATH		= -I./incl
OBJOPT		= $(OPTI) -W -Wall -Werror
CXXFLAGS	= $(OBJOPT) $(IPATH) -pipe
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

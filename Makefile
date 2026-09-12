NAME = matrix

SRC =   srcs/main.cpp 

OBJS = $(SRC:.cpp=.o)

CXX  = c++

CXXFLAGS  = -Wall -Wextra -Werror -std=c++11 -I includes

${NAME} : ${OBJS}
	@${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

.cpp.o:
	@${CXX} ${CXXFLAGS} -c $< -o ${<:.cpp=.o}

all:    ${NAME}

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
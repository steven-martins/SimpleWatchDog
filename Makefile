NAME 	= 	watchdog

SRC 	= 	CUAbsTcpSocket.cpp \
		CWAbsTcpSocket.cpp \
		Checker.cpp \
		Scheduler.cpp \
		main.cpp \
		time.cpp


OBJ 	= 	$(SRC:.cpp=.o)

CFLAGS 	= 	-Wall

$(NAME)	:	$(OBJ)
		g++ -o $(NAME) $(OBJ)

all	:	$(NAME)

clean	:
		rm -f *~ \#* $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all
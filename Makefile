NAME = out
CPPFLAGS = -Wall -Wextra -Wshadow -std=c++20 -MD -Ofast -flto
CC = g++
SRC = main.cpp Node.cpp

OBJ = $(SRC:.cpp=.o)
DFILES = $(SRC:.cpp=.d)

all: $(NAME)

debug: CPPFLAGS += -g
debug: all

profiling: CPPFLAGS += -pg
profiling: run
	gprof $(NAME) gmon.out

address: CPPFLAGS += -fsanitize=address -g
address: all

run: all
	@./$(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CPPFLAGS) $^ -o $@ $(DEBUG)
	@echo finish

%.o: %.cpp
	@echo building $@
	@$(CC) -c $(CPPFLAGS) $< -o $@ $(DEBUG)

clean:
	@rm -rf $(OBJ) $(DFILES)
	@echo cleaned
	@rm -rf gmon.out

fclean: clean
	@rm -rf $(NAME)

re: fclean all

-include $(DFILES)

.PHONY: all clean fclean re debug run

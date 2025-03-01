# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 16:15:58 by sakitaha          #+#    #+#              #
#    Updated: 2025/02/12 03:20:54 by sakitaha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -MMD -MP

SRCS     := PmergeMe.cpp Utils.cpp main.cpp
OBJS     := $(SRCS:.cpp=.o)
DEPS     := $(OBJS:.o=.d)
NAME     := PmergeMe

OS       := $(shell uname -s)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	@echo "== Running Tests  =="
	@echo "--- Basic Test ---"
	@echo "--- case 1 ---"
	./$(NAME) 7 || true
	@echo "\n--- case 2 ---"
	./$(NAME) 19 13
	@echo "\n--- case 5 ---"
	./$(NAME) 3 5 9 7 4
	@echo "\n--- case 7 ---"
	./$(NAME) 2 5 3 7 0 13 8
	@echo "\n--- case 8 ---"
	./$(NAME) 1 12 5 3 7 0 13 8
	@echo "\n--- case 11 ---"
	./$(NAME) 13 7 10 2 0 5 4 9 6 11 3

ifeq ($(OS), Linux)
	@echo "\n--- Linux Random Test ---"
	./$(NAME) `shuf -i 1-100 -n 13 | tr "\n" " "`
else ifeq ($(OS), Darwin)
	@echo "\n--- macOS Random Test ---"
	./$(NAME) `jot -r 13 1 100 | tr '\n' ' '`
endif

	@echo "\n--- case 21 ---"
	./$(NAME) 7 18 23 12 8 13 3 21 4 22 20 11 10 9 5 16 2 14 15 19 0
	@echo "\n--- case Reverse Sorted ---"
	./$(NAME) 10 9 8 7 6 5 4 3 2 1
	@echo "\n--- case Sorted ---"
	./$(NAME) 1 2 3 4 5 6 7 8 9 10
	@echo "\n--- case Duplicate ---"
	./$(NAME) 5 5 5 5 5
	@echo "\n--- Invalid Input Test ---"
	./$(NAME) "-1" "2" || true
	./$(NAME) "1" "" "3" || true
	@echo "\n== Tests Completed =="

test: CXXFLAGS += -DDISPLAY_DEBUG_MSG
test: re run

large: CXXFLAGS += -DMUTE_DEBUG_PRINT
large: re
	@echo "== Running Large Tests  =="
	@echo "--- case 3000 ---"
ifeq ($(OS), Linux)
	./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "`
else ifeq ($(OS), Darwin)
	./$(NAME) `jot -r 3000 1 100000 | tr '\n' ' '`
endif

	@echo "\n--- case 10000 ---"
ifeq ($(OS), Linux)
	./$(NAME) `shuf -i 1-100000 -n 10000 | tr "\n" " "`
else ifeq ($(OS), Darwin)
	./$(NAME) `jot -r 10000 1 100000 | tr '\n' ' '`
endif

	@echo "\n--- case 70000 ---"
ifeq ($(OS), Linux)
	./$(NAME) `shuf -i 1-100000 -n 70000 | tr "\n" " "`
else ifeq ($(OS), Darwin)
	./$(NAME) `jot -r 70000 1 100000 | tr '\n' ' '`
endif
	@echo "\n== Tests Completed =="

debug: CXXFLAGS += -fsanitize=address -g
debug: re run

valgrind: all
	valgrind --leak-check=full 	./$(NAME) 3 5 9 7 4

.PHONY: all clean fclean re run test debug valgrind large

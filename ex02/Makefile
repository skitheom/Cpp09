# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 16:15:58 by sakitaha          #+#    #+#              #
#    Updated: 2025/02/11 23:43:43 by sakitaha         ###   ########.fr        #
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
	./$(NAME) 3 5 9 7 4

ifeq ($(OS), Linux)
	@echo "\n--- Linux Random Test ---"
	./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "`
else ifeq ($(OS), Darwin)
	@echo "\n--- macOS Random Test ---"
	./$(NAME) `jot -r 3000 1 100000 | tr '\n' ' '`
endif

	@echo "\n--- Invalid Input Test ---"
	./$(NAME) "-1" "2" || true
	@echo "\n== Tests Completed =="

test: CXXFLAGS += -DDISPLAY_DEBUG_MSG
test: re
	./$(NAME) 3 5 9 7 4

debug: CXXFLAGS += -fsanitize=address -g
debug: $(NAME)
	./$(NAME)

valgrind: all
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re run test debug valgrind

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 16:15:58 by sakitaha          #+#    #+#              #
#    Updated: 2025/02/06 16:07:46 by sakitaha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -MMD -MP

SRCS     := main.cpp BitcoinExchange.cpp
OBJS     := $(SRCS:.cpp=.o)
DEPS     := $(OBJS:.o=.d)
NAME     := btc

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(NAME)
	@echo "== Running Tests  =="
	@echo "--- Basic Test ---"
	./$(NAME) input.txt
	@echo "\n--- Edge Case test ---"
	./$(NAME) edgecase.txt
	@echo "== Tests Completed =="

debug: CXXFLAGS += -DDISPLAY_DEBUG_MSG
debug: re run

asan: CXXFLAGS += -fsanitize=address -g
asan: re run

valgrind: all
	valgrind --leak-check=full ./$(NAME) input.txt

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re run debug asan valgrind

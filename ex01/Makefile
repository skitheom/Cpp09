# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 16:15:58 by sakitaha          #+#    #+#              #
#    Updated: 2025/02/07 14:55:28 by sakitaha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -MMD -MP

SRCS     := main.cpp RPN.cpp
OBJS     := $(SRCS:.cpp=.o)
DEPS     := $(OBJS:.o=.d)
NAME     := RPN

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
	./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	./$(NAME) "7 7 * 7 -"
	./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	./$(NAME) "(1 + 1)" || true
	@echo "\n--- Error Case Test ---"
	./$(NAME) "1 2 + -" || true
	./$(NAME) "42 + 1" || true
	./$(NAME) "7 % 4" || true
	./$(NAME) "4 9 + 0 /" || true
	./$(NAME) "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *" || true
	@echo "\n--- Additional Test ---"
	./$(NAME) "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"
	./$(NAME) "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /"
	./$(NAME) "2 1 + 3 *"
	./$(NAME) "4 7 5 / +"
	./$(NAME) "9 6 9 3 + 1 * / * 7 + 5 +"
	@echo ""
	@echo "== Tests Completed =="

test: CXXFLAGS += -DDISPLAY_DEBUG_MSG
test: re run

debug: CXXFLAGS += -fsanitize=address -g
debug: $(NAME)
	./$(NAME)

valgrind: all
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re run test debug valgrind

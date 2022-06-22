# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iayni <iayni@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 21:27:19 by iayni             #+#    #+#              #
#    Updated: 2022/06/21 21:46:31 by iayni            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

BONUS_EXE = philo_bonus

SRC_PATH = ./src

SRC = philo.c init.c utils.c

SRC_INC = ./src/philo.h

BONUS_PATH = ./bonus

BONUS = check_args.c check_death.c data_fill.c end_program.c \
		monitor.c philo_bonus.c print.c utils.c \

BONUS_INC = ./bonus/philo_bonus.h

CFLAGS = -Wall -Wextra -Werror

CC = cc

SRC_NAME = $(addprefix $(SRC_PATH)/, $(SRC))

SRC_OBJ = $(SRC_NAME:.c=.o)

BONUS_NAME = $(addprefix $(BONUS_PATH)/, $(BONUS))

BONUS_OBJ = $(BONUS_NAME:.c=.o)

all: $(NAME)

$(NAME): $(SRC_NAME) $(SRC_OBJ) $(SRC_INC)
	@$(CC) $(CFLAGS) $(SRC_OBJ) -o $(NAME)

bonus: $(BONUS_EXE)

$(BONUS_EXE): $(BONUS_NAME) $(BONUS_OBJ) $(BONUS_INC)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_EXE)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(SRC_OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -rf $(NAME) $(BONUS_EXE)

re: fclean all
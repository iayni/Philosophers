NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -c

RM = rm -f

SRCS = philo_bonus.c check_args.c check_death.c end_program.c\
		fill_data.c monitor.c tools.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) philo_bonus.h
	cc $(CFLAGS) $(SRCS)
	cc $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
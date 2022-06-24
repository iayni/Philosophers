NAME = philo

CFLAGS = -Wall -Wextra -Werror -c

RM = rm -f

SRCS = philo.c check_args.c print.c thread_init.c
	

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) philo.h
	cc $(CFLAGS) $(SRCS)
	cc $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
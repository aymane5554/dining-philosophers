CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = init_bonus.c main_bonus.c ft_atoi_bonus.c
OBJS = $(SRCS:%.c=%.o)
NAME = philo_bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

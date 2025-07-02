CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
SRCS = init_bonus.c main_bonus.c ft_atoi_bonus.c kill_philos.c ft_itoa_bonus.c join.c
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

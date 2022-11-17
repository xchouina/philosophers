SRCS =	srcs/actions.c		\
		srcs/main.c			\
		srcs/parsing.c		\
		srcs/utils.c		\
		srcs/ft_atoi.c		\

NAME = philo

OBJS = $(SRCS:.c=.o)

CC = gcc

# CFLAGS = -Werror -Wall -Wextra

CFLAGS = -Werror -Wall -Wextra -fsanitize=thread

.c.o : 
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS)  $(OBJS) $(LIBS) -o $(NAME) 
	@echo "philo done! ;)\n--------------------------------------------\n"

all: $(NAME)

clean:
	@rm -rf $(OBJS)
	@$(RM_BIG_BOI)

fclean: clean
	@rm -f $(NAME)

re: fclean all
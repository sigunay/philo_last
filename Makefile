NAME = philo
CC = @gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c \
		utils.c \
		ft_substr.c \
		ft_split.c \
		ft_exit.c \
		routines.c \
		routines1.c \

OBJS = $(SRCS:.c=.o)

PURPLE = \033[35m
CYAN = \033[36m
BLUE = \033[34m
RED = \033[31m
END = \033[0m

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
		@echo "$(CYAN)Compiled successfully!$(END)"
all: $(NAME)
clean:
		@rm -f $(OBJS)
		@echo "$(CYAN)Cleaned successfully!$(END)"
fclean: clean
		@rm -f $(NAME)
		@echo "$(CYAN)Fclean completed successfully!$(END)"
re: fclean all
f: fclean
c: clean

.PHONY: all clean fclean re f c
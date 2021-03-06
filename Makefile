NAME = philo

LIBNAME = philo.a

SRC = ft_actions.c \
	ft_init.c \
	ft_parsing.c \
	ft_philosophers.c \
	ft_simulation.c \
	libft_functions.c

HEADERFILE = philosophers.h

FLAGS = -Wall -Wextra -Werror

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	@ar rcs $(LIBNAME) $(OBJECT)
	@gcc $(LIBNAME)  -o $(NAME)
	@echo "\n$(GREEN)██████████████████████████ Done compiling ███████████████████████████$(RESET)"

%.o:%.c $(HEADERFILE)
	gcc $(FLAGS) -c $<

clean:
	@echo "$(RED)Deleting object files...$(RESET) "
	@/bin/rm -f $(OBJECT)

fclean: clean
	@echo "$(RED)Deleting libraries, and executables...$(RESET) "
	@/bin/rm -f $(LIBNAME)
	@/bin/rm -f $(NAME)

re: fclean all
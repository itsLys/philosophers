NAME		= philo_bonus
CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -ggdb -fsanitize=thread
CFLAGS		= -Wall -Wextra -Werror -ggdb -pthread
LFLAGS		= -pthread
SRC			= init_bonus.c \
			  main_bonus.c \
			  routine_bonus.c \
			  forks_bonus.c \
			  update_bonus.c \
			  cleanup_bonus.c \
			  parser_bonus.c \
			  sleep_bonus.c \
			  time_bonus.c \
			  utils_bonus.c
OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) done!$(RESET)"

$(NAME): $(OBJ)
	@echo "$(YELLOW)complining $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< $(INCLUDES) -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean

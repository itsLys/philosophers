vpath %c src
GREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
INCLUDES	= -I./headers/
SRC_DIR		= src
SRC			= main.c \
			  utils.c \
			  parser.c
OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) done!$(RESET)"

$(NAME): $(OBJ)
	@echo "$(YELLOW)complining $(NAME)...$(RESET)"
	@$(CC) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< $(INCLUDES) -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean

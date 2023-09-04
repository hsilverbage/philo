.PHONY: 		clean fclean re norm

NAME = philo

CC = cc -g3
CFLAGS = -pthread -Wall -Wextra -Werror #-fsanitize=thread
INCLUDES = -I ./includes

RED=\033[0;31m
BLUE=\033[0;34m
GREEN=\033[0;32m
YELLOW=\033[0;33m
END=\033[0m

SRC_DIR = ./sources

OBJ_DIR = .obj

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/free.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)Compilation succeded ! ✔️$(END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/sources
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#norm:
#@norminette ./libft ./sources ./includes ./bonus | grep "Error" && echo "$(RED)Norminette KO!$(END)" || echo "$(GREEN)Norminette OK!$(END)"

clean:
	@echo "$(YELLOW)All .o files deleted 🗑 $(END)"
		@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)The final program is deleted 🗑 $(END)"
	@rm -f $(NAME)

re: fclean norm all

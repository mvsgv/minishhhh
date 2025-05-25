NAME            =       minishell
CC              =       cc
CFLAGS          =       -Wall -Werror -Wextra -g3 -fsanitize=address
RM              =       rm -rf

MINISHELL_DIR   =       ./includes/
READLINE_DIR    =       /opt/homebrew/opt/readline
READLINE_LIB    =       -L$(READLINE_DIR)/lib -lreadline -lhistory

INC_DIR         =       include source /include $(READLINE_DIR)/include $MINISHELL_DIR
CFLAGS          +=      $(addprefix -I, $(INC_DIR))
LDFLAGS         =       $(READLINE_LIB)

VPATH           =       src src/builtins src/exec src/lexer src/parser src/utils

SRC_BUILTINS    =       builtins/builtins1.c builtins/arr_utils.c builtins/builtins2.c builtins/env_utils.c builtins/env.c
MAIN            =       main/main.c
SRC_EXEC        =       exec/exec.c exec/pipe.c exec/utils.c
SRC_LEXER       =       lexer/lexer.c lexer/lexer_utils.c
SRC_PARSER      =       parser/input.c parser/pipes.c parser/parser_utils.c parser/parser.c
SRC_UTILS       =       utils/ft_isdigit.c utils/ft_atoi.c utils/ft_strcmp.c utils/ft_isspace.c \
                      utils/ft_substr.c utils/ft_strdup.c utils/utils.c \
                      utils/ft_memcpy.c utils/ft_strlen.c utils/ft_strncmp.c \
                      utils/ft_putstr_fd.c utils/ft_putchar_fd.c utils/ft_putendl_fd.c

SRC             =       $(MAIN) $(SRC_UTILS) $(SRC_PARSER) $(SRC_BUILTINS) \
                      $(SRC_LEXER) $(SRC_EXEC)

PINK            =       \033[38;2;255;20;147m
GREEN_APPLE     =       \033[38;2;118;255;3m
RESET           =       \033[0m

OBJ             =       $(SRC:.c=.o)

all: banner $(NAME)

banner:
	@echo "$(GREEN_APPLE)      ___                   ___                   ___         ___         ___         ___  ___  $(RESET)"
	@echo "$(GREEN_APPLE)     /\\__\\        ___      /\\__\\        ___      /\\  \\       /\\__\\       /\\  \\       /\\__\\/\\__\\ $(RESET)"
	@echo "$(GREEN_APPLE)    /::|  |      /\\  \\    /::|  |      /\\  \\    /::\\  \\     /:/  /      /::\\  \\     /:/  /:/  / $(RESET)"
	@echo "$(GREEN_APPLE)   /:|:|  |      \\:\\  \\  /:|:|  |      \\:\\  \\  /:/\\ \\  \\   /:/__/      /:/\\:\\  \\   /:/  /:/  /  $(RESET)"
	@echo "$(GREEN_APPLE)  /:/|:|__|__    /::\\__\\/:/|:|  |__    /::\\__\\_\\:\\~\\ \\  \\ /::\\  \\ ___ /::\\~\\:\\  \\ /:/  /:/  /   $(RESET)"
	@echo "$(GREEN_APPLE) /:/ |::::\\__\\__/:/\\/__/:/ |:| /\\__\\__/:/\\/__/\\ \\:\\ \\ \\__/:/\\:\\  /\\__/:/\\:\\ \\:\\__/:/__/:/__/    $(RESET)"
	@echo "$(GREEN_APPLE) \\/__/~~/:/  /\\/:/  /  \\/__|:|/:/  /\\/:/  /  \\:\\ \\:\\ \\/__\\/__\\:\\/:/  \\:\\~\\:\\ \\/__\\:\\  \\:\\  \\    $(RESET)"
	@echo "$(GREEN_APPLE)       /:/  /\\::/__/       |:/:/  /\\::/__/    \\:\\ \\:\\__\\      \\::/  / \\:\\ \\:\\__\\  \\:\\  \\:\\  \\   $(RESET)"
	@echo "$(GREEN_APPLE)      /:/  /  \\:\\__\\       |::/  /  \\:\\__\\     \\:\\/:/  /      /:/  /   \\:\\ \\/__/   \\:\\  \\:\\  \\  $(RESET)"
	@echo "$(GREEN_APPLE)     /:/  /    \\/__/       /:/  /    \\/__/      \\::/  /      /:/  /     \\:\\__\\      \\:\\__\\:\\__\\ $(RESET)"
	@echo "$(GREEN_APPLE)     \\/__/                 \\/__/                 \\/__/       \\/__/       \\/__/       \\/__/\\/__/ $(RESET)"
	@echo ""

$(NAME): $(OBJ)
	@echo "$(GREEN_APPLE)Compiling minishell...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "$(GREEN_APPLE)Done !$(RESET)"

# Compile object files from sources
%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "Cleaned object files."

fclean: clean
	@$(RM) $(NAME)
	@echo "Removed executable."

re: fclean all

.PHONY: all clean fclean re banner



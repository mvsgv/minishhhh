NAME            = minishell
CC              = cc
CFLAGS          = -Wall -Werror -Wextra -g3 -fsanitize=address
RM              = rm -rf

MINISHELL_DIR   = ./includes/
READLINE_DIR    = /opt/homebrew/opt/readline
READLINE_LIB    = -L$(READLINE_DIR)/lib -lreadline -lhistory
OBJDIR          = obj

INC_DIR         = include source /include $(READLINE_DIR)/include $(MINISHELL_DIR)
CFLAGS          += $(addprefix -I, $(INC_DIR))
LDFLAGS         = $(READLINE_LIB) Libft/libft.a

VPATH           = src src/builtins src/exec src/lexer src/parser src/utils

LIBFT           = Libft/libft.a
SRC_BUILTINS    = builtins/cd_pwd.c builtins/echo_exit.c builtins/env_set.c builtins/export_utils.c builtins/export.c builtins/unset_env.c
MAIN            = main/main.c main/env_init.c
SRC_EXEC        = exec/exec_all.c exec/exec_builtins.c exec/exec_child.c exec/exec_fork.c exec/handle_signal.c exec/utils.c
SRC_LEXER       = lexer/lexer.c lexer/lexer_utils.c lexer/lexer2.c
SRC_EXPANDER    = expander/expander.c expander/expander_utils.c
SRC_PARSER      = parser/input.c parser/pipes.c parser/parser_utils.c parser/parser.c
SRC_UTILS       = utils/utils.c utils/utils2.c

SRC             = $(MAIN) $(SRC_UTILS) $(SRC_PARSER) $(SRC_BUILTINS) \
                  $(SRC_LEXER) $(SRC_EXEC) $(SRC_EXPANDER)

PINK            = \033[38;2;255;20;147m
GREEN_APPLE     = \033[38;2;118;255;3m
RESET           = \033[0m

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: banner $(NAME)

banner:
	@echo "$(GREEN_APPLE)      ___                   ___                   ___         ___         ___         ___  ___  $(RESET)"
	@echo "$(GREEN_APPLE)     /\__\        ___      /\__\        ___      /\  \       /\__\       /\  \       /\__\/\__\ $(RESET)"
	@echo "$(GREEN_APPLE)    /::|  |      /\  \    /::|  |      /\  \    /::\  \     /:/  /      /::\  \     /:/  /:/  / $(RESET)"
	@echo "$(GREEN_APPLE)   /:|:|  |      \:\  \  /:|:|  |      \:\  \  /:/\ \  \   /:/__/      /:/\:\  \   /:/  /:/  /  $(RESET)"
	@echo "$(GREEN_APPLE)  /:/|:|__|__    /::\__\/:/|:|  |__    /::\__\_\:\~\ \  \ /::\  \ ___ /::\~\:\  \ /:/  /:/  /   $(RESET)"
	@echo "$(GREEN_APPLE) /:/ |::::\__\__/:/\/__/:/ |:| /\__\__/:/\/__/\ \:\ \ \__/:/\:\  /\__/:/\:\ \:\__/:/__/:/__/    $(RESET)"
	@echo "$(GREEN_APPLE) \/__/~~/:/  /\/:/  /  \/__|:|/:/  /\/:/  /  \:\ \:\ \/__\/__\:\/:/  \:\~\:\ \/__\:\  \:\  \    $(RESET)"
	@echo "$(GREEN_APPLE)       /:/  /\::/__/       |:/:/  /\::/__/    \:\ \:\__\      \::/  / \:\ \:\__\  \:\  \:\  \   $(RESET)"
	@echo "$(GREEN_APPLE)      /:/  /  \:\__\       |::/  /  \:\__\     \:\/:/  /      /:/  /   \:\ \/__/   \:\  \:\  \  $(RESET)"
	@echo "$(GREEN_APPLE)     /:/  /    \/__/       /:/  /    \/__/      \::/  /      /:/  /     \:\__\      \:\__\:\__\ $(RESET)"
	@echo "$(GREEN_APPLE)     \/__/                 \/__/                 \/__/       \/__/       \/__/       \/__/\/__/ $(RESET)"
	@echo "\033[38;2;255;20;147m"

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C Libft

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN_APPLE)Compiling minishell...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)
	@echo "$(GREEN_APPLE)Done !$(RESET)"

clean:
	@$(RM) $(OBJDIR)
	@$(MAKE) -s -C Libft clean
	@echo "$(PINK)Cleaned object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C Libft fclean

re: fclean all

.PHONY: all clean fclean re banner
NAME 			= 		minishell
CC 				=		cc 
CFLAGS 			=		-Wall -Werror -Wextra -g3 -fsanitize=address
RM 				= 		rm -rf

MINISHELL_DIR	=		./includes/
READLINE_DIR	=		$(HOME)/.brew/opt/readline
READLINE_LIB 	=		-L$(READLINE_DIR)/lib -lreadline -lhistory

INC_DIR			=		include source /include $(READLINE_DIR)/include $MINISHELL_DIR
CFLAGS			+=		$(addprefix -I, $(INC_DIR))
LDFLAGS			=		$(READLINE_LIB)

VPATH			=		src src/builtins src/exec src/lexer src/parser src/utils
SRC_BUILTINS	=
SRC_MAIN		=		main/main.c
SRC_EXEC		=
SRC_LEXER		=		lexer/lexer.c
SRC_PARSER		=		parser/input.c parser/pipes.c
SRC_UTILS		=		utils/ft_isspace.c utils/ft_substr.c utils/ft_strdup.c utils/utils.c


SRC 			=		$(MAIN) $(SRC_UTILS) $(SRC_PARSER) $(SRC_BUILTINS) \
						$(SRC_LEXER) $(SRC_EXEC) 

OBJ		= $(SRC:%.c=src/%.o)


PINK = \033[38;2;255;20;147m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[38;2;255;20;147mCompiling minishell...\033[0m"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "\033[32mDone !\033[0m"

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) src/*.o
	@echo "\033[33mCleaned object files.\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[31mRemoved executable.\033[0m"

re: fclean all

.PHONY: all clean fclean re
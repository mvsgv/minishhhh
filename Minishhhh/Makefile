NAME = minishell
CC = cc 
CFLAGS = - Wall -Werror -Wextra
LIBFT = /Libft/libft.a
BUILTINS = 
EXEC = 
PARSER = parser_utils pipes 
HEADER = minishell.h

PINK = \033[38;2;255;20;147m


SRC = $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) 

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make -C libft/
	@echo "\033[38;2;255;20;147mCompiling minishell...\033[0m\n]"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\n\033[0mDone !"
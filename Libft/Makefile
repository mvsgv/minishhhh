NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_PART = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_strjoin.c ft_memchr.c \
ft_strcmp.c ft_isspace.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_substr.c ft_strtrim.c ft_split.c ft_strmapi.c ft_itoa.c ft_striteri.c \
ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c

OBJDIR = obj
OBJ_PART = $(addprefix $(OBJDIR)/, $(SRC_PART:.c=.o))

all: $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_PART)
	@ar rcs $@ $^

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
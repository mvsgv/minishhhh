NAME = libft.a

CC = gcc -c

FLAGS = -Wall -Werror -Wextra

SRC_PART = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
 ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c\
 ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
 ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_strjoin.c ft_memchr.c\
 ft_substr.c ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c\
 ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c

SRC_BONUS = ft_lstnew.c ft_lstsize.c ft_lstadd_back.c ft_lstsize.c ft_lstadd_front.c\
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstlast.c

OBJ_PART = $(SRC_PART:.c=.o)
OBJ_BONUS = $(OBJ_PART) $(SRC_BONUS:.c=.o)

RM = rm -f

HEAD = libft.h

.c.o : $(SRCS)
	${CC} ${CFLAGS} -c -o $@ $^

all : $(NAME)

$(NAME) : $(OBJ_PART) $(HEAD)
	@$(CC) $(SRC_PART) $(FLAGS)
	ar rcs $(NAME) $(OBJ_PART)

bonus: $(OBJ_BONUS) $(HEAD)
	@$(CC) $(SRC_PART) $(SRC_BONUS) $(FLAGS)
	ar rcs $(NAME) $(OBJ_BONUS)

clean :
	$(RM) $(OBJ_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror 
CC = cc
SRCS = base16.c check_current1.c ft_printf.c various_print.c
OBJS = $(SRCS:.c=.o) 

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS) 

fclean : clean
	rm -f $(NAME)

re : fclean all
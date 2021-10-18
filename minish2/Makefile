NAME = libftprintf.a

LIBFTNAME = libft.a

CC = gcc

FLAGS =   -I ./libft/ -g -L ./libft/ -l ft -L/usr/include -lreadline 	

SRCS = main.c

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRCS)
run:
	./a.out

test:
	$(CC) $(FLAGS) test.c

clean:
	rm -f a.out

re: clean all run

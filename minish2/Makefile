NAME = libftprintf.a

LIBFTNAME = libft.a

CC = gcc

FLAGS =   -I ./libft/ -g -L ./libft/ -l ft -L/usr/include -lreadline 	

SRCS = minish.c

all: $(NAME)

$(NAME):
	$(CC) $(SRCS) -L/usr/include -lreadline -g
run:
	./a.out

test:
	$(CC) $(FLAGS) test.c

clean:
	rm -f a.out

re: clean all run

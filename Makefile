ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME_LINK	=	libft_malloc.so
NAME		=	libft_malloc_$(HOSTTYPE).so.

SRCDIR		=	./srcs
INCDIR		=	./includes
OBJDIR		=	obj

SRC			=	malloc.c\
				free.c\
				utils.c\
				finder.c\
				display.c\
				realloc.c\
				allocation.c\
				typed_free.c\
				typed_allocation.c\

OBJ			=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC			=	gcc
CFLAGS		=	-std=gnu99 -g -Wall -Wextra -Werror

FT			=	./libft/
FT_LIB		=	$(addprefix $(FT),libft.a)
FT_INC		=	-I ./libft

all:			obj $(FT_LIB) $(NAME)

obj:
				mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c includes/ft_malloc.h
				$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
				make -C $(FT)

$(NAME):		$(OBJ)
				rm -f $(NAME_LINK)
				ar -rc $(NAME) $(OBJ)
				ranlib $(NAME)
				ln -s $(NAME) $(NAME_LINK)

test:			$(NAME_LINK) $(FT_LIB)
				$(CC) src_test/*.c -I $(INCDIR) $(FT_INC) -L. $(NAME_LINK) $(FT_LIB) -o test_malloc

clean:
				rm -rf $(OBJDIR)
				make -C $(FT) clean

fclean:			clean
				rm -rf $(NAME) $(NAME_LINK) test_malloc
				make -C $(FT) fclean

re: fclean all


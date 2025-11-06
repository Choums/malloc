ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME_LINK	=	libft_malloc.so
NAME		=	libft_malloc_$(HOSTTYPE).so

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
CFLAGS		=	-std=gnu99 -g -Wall -Wextra -Werror -fPIC

FT			=	./libft/
FT_LIB		=	$(addprefix $(FT),libft.a)
FT_INC		=	-I ./libft

all:			obj $(FT_LIB) $(NAME)

obj:
				mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(INCDIR)/malloc.h
				$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
				make -C $(FT)

$(NAME):		$(OBJ) $(FT_LIB)
				rm -f $(NAME_LINK)
				$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJ) -Wl,--whole-archive $(FT_LIB) -Wl,--no-whole-archive #Link the static libft.a into the shared library. --whole-archive forces inclusion of all symbols
				ln -s $(NAME) $(NAME_LINK)

test:			$(NAME_LINK)
				$(CC) src_test/main.c -I $(INCDIR) $(FT_INC) -L. -Wl,-rpath=. -l:$(NAME_LINK) -o test_malloc

# Build and run the allocator tests against the system malloc (do NOT link libft_malloc.so)
test_system:
			$(CC) src_test/auto_test.c -I $(INCDIR) $(FT_INC) -o test_system

clean:
				rm -rf $(OBJDIR)
				make -C $(FT) clean

fclean:			clean
				rm -rf $(NAME) $(NAME_LINK) test_malloc
				make -C $(FT) fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY:			all clean fclean re test obj test_system
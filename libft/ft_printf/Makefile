# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/11 11:38:13 by fhuang            #+#    #+#              #
#    Updated: 2017/11/04 14:50:23 by fhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Editable =====
LIBFT	:=	../
LIBNAME	:= lib/
LIBDIR	:=	$(LIBFT)$(LIBNAME)
NAME	:=	$(addprefix $(LIBDIR), libftprintf.a)
# ====================

# ===== Standard =====
CC		:=	clang -pipe
CFLAGS	:=	-Wall -Wextra -Werror -g3
SRCDIR	:=	src/
OBJDIR	:=	obj/
INCDIR	:=	../include/
SRC		:=	add_link.c					\
			desactivate_flags.c			\
			ft_ctoa_base.c				\
			ft_lltoa_base.c				\
			ft_ltoa_base.c				\
			ft_printf.c					\
			ft_printf_itoa_base.c		\
			ft_stoa_base.c				\
			get_color.c					\
			get_struct.c				\
			get_type.c					\
			get_type_int.c				\
			init_destroy.c				\
			new_link.c					\
			no_type.c					\
			print_entire_list.c			\
			read_and_transform_arg.c	\
			read_str.c					\
			transform_flags.c			\
			transform_for_numbers.c		\
			transform_for_strings.c		\
			transform_tools.c			\
			transform_wchar.c
OBJ		:=	$(SRC:%.c=$(OBJDIR)%.o)
INC		:=	-I./$(INCDIR)
LIBPATH	:=	-L./$(LIBDIR) -lft
CACHEF	:=	.cache_exists
# ====================

# ====== Colors ======
CLEAR		= "\033[2K"
UP			= "\033[A"
EOC			= "\033[0;0m"
BLACK		= "\033[0;30m"
RED			= "\033[0;31m"
GREEN		= "\033[0;32m"
YELLOW		= "\033[0;33m"
BLUE		= "\033[0;34m"
PURPLE		= "\033[0;35m"
CYAN		= "\033[0;36m"
WHITE		= "\033[0;37m"
# ====================

EXEC			:= $(addprefix $(LIBDIR), $(NAME))
CACHEF			:=	.cache_exists

.PHONY: clean fclean re all
.SILENT:

all : $(NAME)

$(NAME): $(OBJ)
	@echo "\033[32m" "-> ft_printf" "\033[0m"
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(CACHEF)
	$(CC) $(CFLAGS) -c  $< -o $@ $(INC)

$(CACHEF):
	test -d $(OBJDIR) || mkdir $(OBJDIR)
	test -d $(LIBDIR) || mkdir $(LIBDIR)
	test -d $(CACHEF) || touch $(CACHEF)

clean:
	rm -rf $(OBJDIR) $(CACHEF)

fclean: clean
	rm -f $(NAME)

re: fclean all

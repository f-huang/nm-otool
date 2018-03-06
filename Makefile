# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/16 23:26:49 by fhuang            #+#    #+#              #
#    Updated: 2018/02/18 00:43:33 by fhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===== Editable =====
NAME1		:=	ft_nm
NAME2		:=	ft_otool
NAME		=	$(NAME1) $(NAME2)
# ====================

# ===== Standard =====
CC			:=	clang -pipe
CFLAGS		:=	-Wall -Wextra -Werror -g3
SRCDIR		:=	src/
OBJDIR		:=	obj/
BINDIR		:=	bin/
INCDIR		:=	include/
LIBFT		:=	libft/
LIBDIR		:=	lib/
SRC			:=	close_and_unmap.c		\
				loop_through_arg.c		\
				open_and_map.c
OBJ			:=	$(SRC:%.c=$(OBJDIR)%.o)
INC			:=	-I./$(INCDIR) -I./$(LIBFT)$(INCDIR)
LIBPATH		:=	-L./$(LIBFT)$(LIBDIR) -lft -lftprintf
CACHEF		:=	.cache_exists
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

# ======= nm =========

NMSRCDIR	:=	$(SRCDIR)nm/
NMOBJDIR	:=	$(OBJDIR)nm/

##### === Subdirectories ===
SECTIONDIR	:=	section/
SYMBOLDIR	:=	symbol/
##### ======================

NMSRC		:=	main.c					\
				ft_nm.c				\
				handle_32_bits.c		\
				handle_64_bits.c		\
				handle_ar.c				\
				handle_fat.c				\
				is_symbol_skipped.c		\
				print_symbol_table.c	\
				set_options.c			\
				$(SECTIONDIR)add_32.c	\
				$(SECTIONDIR)add_64.c	\
				$(SECTIONDIR)add_determine_type.c		\
				$(SECTIONDIR)get_type.c	\
				$(SYMBOLDIR)add.c		\
				$(SYMBOLDIR)clear.c		\
				$(SYMBOLDIR)get_cmp_function.c

NMOBJ		:=	$(NMSRC:%.c=$(NMOBJDIR)%.o)
# ====================

# ====== otool =======
OTOOLDIR	:=	$(SRCDIR)otool/
OTOOLOBJDIR	:=	$(OBJDIR)otool/
OTOOLSRC	:=	main.c					\
				ft_otool.c				\
				handle_32_bits.c		\
				handle_64_bits.c		\
				handle_ar.c				\
				handle_fat.c
OTOOLOBJ	:=	$(OTOOLSRC:%.c=$(OTOOLOBJDIR)%.o)
# ====================

.PHONY: all libft norme clean fclean re nm otool

all: libft nm otool

$(OBJDIR)%.o: $(SRCDIR)%.c $(CACHEF)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@printf $(GREEN)"•"$(EOC)

$(CACHEF):
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@test -d $(NMOBJDIR) || mkdir $(NMOBJDIR)
	@test -d $(NMOBJDIR)$(SECTIONDIR) || mkdir $(NMOBJDIR)$(SECTIONDIR)
	@test -d $(NMOBJDIR)$(SYMBOLDIR) || mkdir $(NMOBJDIR)$(SYMBOLDIR)
	@test -d $(OTOOLOBJDIR) || mkdir $(OTOOLOBJDIR)
	@test -d $(CACHEF) || touch $(CACHEF)

%.c:
	@echo $(RED)"Missing file : $@"$(EOC)

otool: $(OBJ) $(OTOOLOBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(OTOOLOBJ) -o $(NAME2) $(LIBPATH) $(INC)
	@echo $(GREEN)"\t✓"$(EOC)

nm: $(OBJ) $(NMOBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(NMOBJ) -o $(NAME1) $(LIBPATH) $(INC)
	@echo $(GREEN)"\t✓"$(EOC)

libft:
	@make -C $(LIBFT)

norme:
	@norminette $(SRCDIR) $(INCDIR) | grep -v Norme -B1 || true
	@norminette $(LIBFT)$(SRCDIR) $(LIBFT)$(INCDIR) | grep -v Norme -B1 || true

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJDIR) $(CACHEF)
	@echo $(YELLOW)"Objects erased"$(EOC)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@echo $(RED)"$(NAME1), $(NAME2) erased"$(EOC)

re: fclean all

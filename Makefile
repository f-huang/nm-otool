# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/16 23:26:49 by fhuang            #+#    #+#              #
#    Updated: 2017/12/21 10:09:45 by fhuang           ###   ########.fr        #
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
SRC			:=
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
NMSRC		:=	main.c
NMOBJ		:=	$(NMSRC:%.c=$(NMOBJDIR)%.o)
# ====================

# ====== otool =======
OTOOLDIR	:=	$(SRCDIR)otool/
OTOOLOBJDIR	:=	$(OBJDIR)otool/
OTOOLSRC	:=	main.c
OTOOLOBJ	:=	$(OTOOLSRC:%.c=$(OTOOLOBJDIR)%.o)
# ====================

.PHONY: all libft norme clean fclean re nm otool

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(CACHEF)
	@$(CC) $(CFLAGS) -c  $< -o $@ $(INC)

$(CACHEF):
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@test -d $(NMOBJDIR) || mkdir $(NMOBJDIR)
	@test -d $(OTOOLOBJDIR) || mkdir $(OTOOLOBJDIR)
	@test -d $(CACHEF) || touch $(CACHEF)

%.c:
	@echo $(RED)"Missing file : $@"$(EOC)

$(NAME1): $(NMOBJ)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(NMOBJ) -o $(NAME1) $(LIBPATH) $(INC)
	@echo $(GREEN)"$(NAME1) ✓"$(EOC)

$(NAME2):  $(OTOOLOBJ)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(OTOOLOBJ) -o $(NAME2) $(LIBPATH) $(INC)
	@echo $(GREEN)"$(NAME2) ✓"$(EOC)

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

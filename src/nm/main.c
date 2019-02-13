/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 09:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 15:44:26 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_nm.h"
#include "ft_nm_otool.h"


static int	init_struct(t_nm_otool *nm_otool)
{
	ft_bzero(nm_otool, sizeof(t_nm_otool));
	if (!(nm_otool->env = (t_nm*)ft_memalloc(sizeof(t_nm))))
		return (0);
	((t_nm*)nm_otool->env)->format = HEXA;
	nm_otool->func_ptr[FUNC_OBJ_64] = &nm_64_bits;
	nm_otool->func_ptr[FUNC_OBJ_32] = &nm_32_bits;
	nm_otool->func_ptr[FUNC_FAT_32] = &fat_32;
	nm_otool->func_ptr[FUNC_FAT_64] = &fat_64;
	nm_otool->func_ptr[FUNC_AR] = &nm_ar;
	return (1);
}

int		main(int ac, char **av)
{
	t_nm_otool	nm_otool;
	int			i;
	int			print;
	int			error;

	i = 0;
	error = 0;
	if (!init_struct(&nm_otool))
		return (1);
	if (!set_options(av, nm_otool.env, &i))
		return (EXIT_FAILURE);
	if (((t_nm*)nm_otool.env)->options & OPTION_H)
		ft_putendl_fd("usage: nm [-"NM_OPTIONS"] [file ...]", 2);
	else
	{
		print = (int)(ac - i > 1);
		while (1)
		{
			if (print)
				ft_printf("\n%s:\n", !av[i] ? DEFAULT_FILE : av[i]);
			error = handle_file(&nm_otool, !av[i] ? DEFAULT_FILE : av[i]);
			if (!av[i] || !av[++i])
				break ;
		}
	}
	ft_memdel(&nm_otool.env);
	return (error);
}

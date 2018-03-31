/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 09:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/31 16:50:15 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_nm.h"
#include "ft_nm_otool.h"

int		main(int ac, char **av)
{
	t_nm	nm;
	int		i;
	int		print;
	int		error;

	i = 0;
	ft_bzero(&nm, sizeof(t_nm));
	nm.format = HEXA;
	error = 0;
	if (!set_options(av, &nm, &i))
		return (EXIT_FAILURE);
	if (nm.options & OPTION_H)
		ft_putendl_fd("usage: "PROGRAM_NAME" [-"NM_OPTIONS"] [file ...]", 2);
	else
	{
		print = (int)(ac - i > 1);
		while (1)
		{
			if (print)
				ft_printf("\n%s:\n", !av[i] ? DEFAULT_FILE : av[i]);
			error = handle_file(&nm, !av[i] ? DEFAULT_FILE : av[i],\
				(int (*)(void*, void*, const char*))ft_nm);
			if (!av[i] || !av[++i])
				break ;
		}
	}
	return (error);
}

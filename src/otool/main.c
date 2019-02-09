/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 09:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/01 11:43:22 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_otool.h"
#include "ft_nm_otool.h"

int		main(int ac, char **av)
{
	t_otool	otool;
	int		i;
	int		error;

	i = 1;
	error = 0;
	ft_bzero(&otool, sizeof(t_otool));
	if (ac > 1)
	{
		while (av[i])
		{
			error = handle_file(&otool, av[i],\
				(int (*)(void*, void*, size_t, const char*))ft_otool);
			if (!av[i] || !av[++i])
				break ;
		}
	}
	return (error);
}

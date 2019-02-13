/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 09:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 20:21:35 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_otool.h"
#include "ft_nm_otool.h"

int		main(int ac, char **av)
{
	t_nm_otool	nm_otool;
	int			i;
	int			error;

	i = 1;
	error = 0;
	ft_bzero(&nm_otool, sizeof(t_nm_otool));
	nm_otool.command = OTOOL;
	nm_otool.func_ptr[FUNC_OBJ_64] = &otool_64_bits;
	nm_otool.func_ptr[FUNC_OBJ_32] = &otool_32_bits;
	nm_otool.func_ptr[FUNC_FAT_32] = &fat_32;
	nm_otool.func_ptr[FUNC_FAT_64] = &fat_64;
	nm_otool.func_ptr[FUNC_AR] = &otool_ar;
	if (ac > 1)
	{
		while (av[i])
		{
			error = handle_file(&nm_otool, av[i], 0);
			if (!av[i] || !av[++i])
				break ;
		}
	}
	return (error);
}

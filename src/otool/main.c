/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 09:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2018/02/20 12:22:07 by fhuang           ###   ########.fr       */
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

	i = 1;
	ft_bzero(&otool, sizeof(t_otool));
	if (ac > 1)
		loop_through_arg(&otool, av, i, (int (*)(void*, void*, const char*))ft_otool);
	(void)ac;
	(void)av;
	return (EXIT_SUCCESS);
}

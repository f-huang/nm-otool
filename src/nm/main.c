/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 09:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/28 17:38:35 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_nm.h"

int		main(int ac, char **av)
{
	t_nm	nm;
	int		i;
	int		fd;
	size_t	size;
	void	*ptr;

	ft_bzero(&nm, sizeof(t_nm));
	nm.format = HEXA;
	if (!set_options(av, &nm, &i))
		return (EXIT_FAILURE);
	if (nm.options & OPTION_H)
		ft_putendl_fd("usage: "PROGRAM_NAME" [-"NM_OPTIONS"] [file ...]", 2);
	else
	{
		i = 0;
		ptr = NULL;
		size = 0;
		while (av[i++])
		{
			if ((fd = open_and_map(ac == 1 ? DEFAULT_FILE : av[i], &ptr, &size)) == -1)
				continue ;
			if (ac > 2)
				ft_printf("\n%s:\n", av[i]);
			read_symbol(&nm, ptr, av[i]);
			close_and_unmap(ptr, size, fd);
		}
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 09:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/19 11:42:44 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_nm.h"

int		main(int ac, char **av)
{
	t_nm	nm;
	int		i;

	i = 0;
	ft_bzero(&nm, sizeof(t_nm));
	nm.format = HEXA;
	if (!set_options(av, &nm, &i))
		return (EXIT_FAILURE);
	if (nm.options & OPTION_H)
		ft_putendl_fd("usage: "PROGRAM_NAME" [-"NM_OPTIONS"] [file ...]", 2);
	else
	{
		if (!set_files(av, &nm, ac, i))
			return (EXIT_FAILURE);
		name_list(&nm);
		clear(&nm);
	}
	return (EXIT_SUCCESS);
}

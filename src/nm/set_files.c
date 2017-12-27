/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:31:46 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/27 12:40:13 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

int		set_files(char **av, t_nm *nm, int ac, int i)
{
	int		nfiles;
	int		j;

	nfiles = av[i] ? ac - i : 1;
	if (!(nm->files = (char**)ft_memalloc(sizeof(char*) * (nfiles + 1))))
		return (0);
	if (!av[i] && (!(nm->files[0] = ft_strdup(DEFAULT_FILE))))
		return (0);
	j = 0;
	while (av[i])
	{
		if (!(nm->files[j++] = ft_strdup(av[i])))
		{
			ft_tabfree(&nm->files);
			return (0);
		}
		++i;
	}
	return (1);
}

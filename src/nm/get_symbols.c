/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 13:02:35 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/27 14:25:48 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "libft.h"
#include "ft_nm.h"

static int	name_list(t_nm *nm, void *ptr)
{
	unsigned int	magic_number;

	magic_number = *((int*)ptr);
	if (magic_number == MH_MAGIC_64)
	{
		ft_putendl("64");
	}
	else if (magic_number == MH_MAGIC)
	{
		ft_putendl("32");
	}
	(void)nm;
	return (1);
}

int			get_symbols(t_nm *nm)
{
	int			i;
	int			fd;
	struct stat	buf;
	void		*ptr;

	i = 0;
	while (nm->files[i])
	{
		if ((fd = open(nm->files[i], O_RDONLY)) >= 0 && fstat(fd, &buf) >= 0\
			&& (ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) != MAP_FAILED)
		{
			name_list(nm, ptr);
			if (munmap(ptr, buf.st_size) < 0 || close(fd) < 0)
			{
				ft_putendl("error end");
				return (0);
			}
		}
		else
		{
			ft_putendl("error");
			//error -> permission - no such file
		}
		++i;
	}
	return (1);
}

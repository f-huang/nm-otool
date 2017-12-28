/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 13:02:35 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/28 19:09:33 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "libft.h"
#include "ft_nm.h"

static void	handle_64_bits(t_nm *nm, void *ptr)
{
	struct mach_header_64	*header;
	struct nlist_64			*nlist;
	struct load_command		*lc;
	struct symtab_command	*sym;
	char					*stringtable;
	uint32_t				i;
	uint32_t				ncmds;
	uint32_t				j;

	header = (struct mach_header_64*)ptr;
	ft_printf("filetype: %p\n", header->filetype);
	ncmds = header->ncmds;
	lc = ptr + sizeof(*header);
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			ft_printf("nb symboles: %d\n", sym->nsyms);
			nlist = (void*)ptr + sym->symoff;
			stringtable = (void*)ptr + sym->stroff;
			j = 0;
			while (j < sym->nsyms)
			{
				ft_putendl(stringtable + nlist[j].n_un.n_strx);
				++j;
			}
			break ;
		}
		else if (lc->cmd == LC_SEGMENT)
		{
			ft_putendl("it's a segment !");
		}
		else if (lc->cmd == LC_DYSYMTAB)
		{
			ft_putendl("it's a dysymtab !");
		}
		lc = (void*)lc + lc->cmdsize;
		++i;
	}
	(void)nm;

}

static int	name_list(t_nm *nm, void *ptr)
{
	uint32_t	magic_number;
	int			swap;

	magic_number = *((int*)ptr);
	ft_printf("magic: %p\n", magic_number);
	swap = (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM);
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		ft_putendl("64 bits");
		handle_64_bits(nm, ptr);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		ft_putendl("32 bits");
	}
	else
	{
		ft_putendl("unknown");
	}
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

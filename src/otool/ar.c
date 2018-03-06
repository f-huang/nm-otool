/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 17:49:06 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/06 02:20:09 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/ranlib.h>
#include <ar.h>
#include "libft.h"
#include "ft_otool.h"

static int	get_offset(const char *ar_name)
{
	char			*ptr;

	ptr = ft_strrchr(ar_name, '/');
	return (ptr ? ft_atoi(ptr + 1) : 0);
}

void	sort_rans(struct ranlib **rans, size_t n_entries, void *ptr)
{
	size_t			i;
	struct ranlib	tmp;

	i = 0;
	while (i + 1 < n_entries)
	{
		if (ft_strcmp(((struct ar_hdr*)(ptr + (*rans)[i].ran_off))->ar_name+ sizeof(struct ar_hdr),\
			((struct ar_hdr*)(ptr + (*rans)[i + 1].ran_off))->ar_name+ sizeof(struct ar_hdr)) > 0)
		{
			tmp = (*rans)[i];
			(*rans)[i] = (*rans)[i + 1];
			(*rans)[i + 1] = tmp;
			i = 0;
		}
		++i;
	}
}

static void	fill_rans(struct ranlib **rans, struct ar_hdr *header, size_t n_entries)
{
	struct ranlib	*ranlib;
	size_t			i;

	ranlib = (void*)header + sizeof(struct ar_hdr) + get_offset(header->ar_name) + sizeof(int);
	i = -1;
	while (++i < n_entries)
		ft_memcpy((*rans) + i, ranlib + i, sizeof(struct ranlib));
}

static void	otool_archive(t_otool *otool, struct ar_hdr *header, const char *filename)
{
	char			*subname;

	subname = header->ar_name + sizeof(struct ar_hdr);
	ft_printf("%s(%s):\n", filename, subname);
	ft_otool(otool, subname + get_offset(header->ar_name), NULL);
}


void	otool_ar(t_otool *otool, void *ptr, const char *filename)
{
	struct ranlib	*rans;
	struct ar_hdr	*header;
	size_t			i;
	size_t			n_entries;

	header = (struct ar_hdr*)(ptr + SARMAG);
	n_entries = *((int *)((void*)header + sizeof(struct ar_hdr) + get_offset(header->ar_name)))\
					/ sizeof(struct ranlib);
	rans = (struct ranlib*)ft_memalloc(sizeof(struct ranlib) * (n_entries + 1));
	if (!rans)
		return ;
	ft_printf("Archive : %s\n", filename);
	fill_rans(&rans, header, n_entries);
	sort_rans(&rans, n_entries, ptr);
	i = -1;
	while (++i < n_entries)
		if (i == 0 || (i > 0 && rans[i - 1].ran_off != rans[i].ran_off))
			otool_archive(otool, ptr + rans[i].ran_off, filename);
	ft_memdel((void**)&rans);
}

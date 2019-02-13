/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 17:49:06 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 12:12:35 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/ranlib.h>
#include <ar.h>
#include "libft.h"
#include "ft_nm.h"

#include <unistd.h>

static int	get_offset(const char *ar_name)
{
	char			*ptr;

	ptr = ft_strrchr(ar_name, '/');
	return (ptr ? ft_atoi(ptr + 1) : 0);
}

void		*pass_string_table(void *ptr, size_t n_entries)
{
	char			*str;
	size_t			i;
	size_t			j;

	i = 0;
	str = (char*)ptr;
	while (i < n_entries)
	{
		j = 0;
		while (str[j])
			++j;
		str = str + j + 1;
		++i;
	}
	while (*str == 0)
		str++;
	return str;
}

static void	nm_archive(t_nm *nm, struct ar_hdr *header, const char *filename)
{
	char			*subname;

	subname = header->ar_name + sizeof(struct ar_hdr);
	ft_printf("\n%s(%s):\n", filename, subname);
	ft_nm(nm, subname + get_offset(header->ar_name), 0, subname);
}

void		nm_ar(t_nm *nm, void *ptr, const char *filename)
{
	struct ar_hdr	*header;
	size_t			n_entries;
	size_t			size;

	header = (struct ar_hdr*)(ptr + SARMAG);
	n_entries = *((int *)((void*)header + sizeof(struct ar_hdr)\
		+ get_offset(header->ar_name)))\
		/ sizeof(struct ranlib);
	ptr = (void*)header + sizeof(struct ar_hdr) + get_offset(header->ar_name) + sizeof(int);
	ptr = ptr + (n_entries * sizeof(struct ranlib)) + 4;
	if (n_entries)
		ptr = pass_string_table(ptr, n_entries);
	while (ptr < nm->end_of_file)
	{
		header = (struct ar_hdr*)ptr;
		if (!ft_strnequ(header->ar_name, "#1/", 3))
			break ;
		size = ft_atoi(header->ar_size);
		nm_archive(nm, header, filename);
		ptr = ptr + sizeof(struct ar_hdr) + size;
	}
}

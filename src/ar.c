/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 17:49:06 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 15:12:41 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/ranlib.h>
#include <ar.h>
#include "ft_nm_otool.h"
#include "libft.h"

static int	get_offset(const char *ar_name)
{
	char			*ptr;

	ptr = ft_strrchr(ar_name, '/');
	return (ptr ? ft_atoi(ptr + 1) : 0);
}


static void	archive(t_nm_otool *nm_otool, struct ar_hdr *header, const char *filename)
{
	char			*subname;

	subname = header->ar_name + sizeof(struct ar_hdr);
	if (nm_otool->command == NM)
		ft_printf("\n%s(%s):\n", filename, subname);
	else
		ft_printf("%s(%s):\n", filename, subname);
	handle_file_objects(nm_otool, subname + get_offset(header->ar_name), (void*)0);
}

static void		*pass_string_table(void *ptr, size_t n_entries)
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

void		ar(t_nm_otool *nm_otool, void *ptr, const char *filename)
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
	while (ptr < nm_otool->end_of_file)
	{
		header = (struct ar_hdr*)ptr;
		if (!ft_strnequ(header->ar_name, "#1/", 3))
			break ;
		size = ft_atoi(header->ar_size);
		archive(nm_otool, header, filename);
		ptr = ptr + sizeof(struct ar_hdr) + size;
	}
}

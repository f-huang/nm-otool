/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 17:49:06 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/22 18:59:34 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/ranlib.h>
#include <ar.h>
#include "libft.h"
#include "ft_nm.h"

void		handle_ar(t_nm *nm, void *ptr, const char *filename)
{
	struct ar_hdr	*ar;
	struct ranlib	*ranlib;
	char			*decimal_offset;
	int				n_entries;

	n_entries = 0;
	ar = (struct ar_hdr*)ptr;
	decimal_offset = ft_strrchr(ar->ar_name, '/');
	if (!decimal_offset)
		return ;
	n_entries = ft_atoi(decimal_offset + 1);
	ft_putendl(ar->ar_name);
	ranlib = ptr + sizeof(struct ar_hdr);
	ft_printf("%p -> %lu, %u\n", ranlib, ranlib->ran_off, ranlib->ran_un.ran_strx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 17:49:06 by fhuang            #+#    #+#             */
/*   Updated: 2018/02/18 01:03:24 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <mach-o/ranlib.h>
// #include <ar.h>
// #include "libft.h"
// #include "ft_nm.h"
//
// static int	get_offset(const char *ar_name)
// {
// 	char			*ptr;
//
// 	ptr = ft_strrchr(ar_name, '/');
// 	return (ptr ? ft_atoi(ptr + 1) : 0);
// }
//
// void	handle_ar(t_nm *nm, void *ptr, const char *filename)
// {
// 	struct ranlib	*ranlib;
// 	struct ar_hdr	*ar;
// 	int				i;
// 	int				n_entries;
// 	void			*ptr2;
//
// 	ar = (struct ar_hdr*)(ptr + SARMAG);
// 	n_entries = get_offset(ar->ar_name);
// 	ranlib = (void*)ar + sizeof(struct ar_hdr) + n_entries + sizeof(int);
// 	n_entries = *(int*)((void*)ar + n_entries + sizeof(struct ar_hdr))\
// 					/ sizeof(struct ranlib);
// 	i = 0;
// 	while (i < n_entries)
// 	{
// 		ar = ptr + ranlib[i].ran_off;
// 		ptr2 = (void*)ar + sizeof(struct ar_hdr) + get_offset(ar->ar_name);
// 		ft_printf("\n%s(%s):\n", filename, ar->ar_name + sizeof(struct ar_hdr));
// 		ft_nm(nm, ptr2, ar->ar_name + sizeof(struct ar_hdr));
// 		++i;
// 	}
// }

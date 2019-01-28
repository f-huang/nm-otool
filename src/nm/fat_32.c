/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 19:07:04 by fhuang            #+#    #+#             */
/*   Updated: 2019/01/28 19:07:23 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach/machine.h>
#include "ft_nm.h"

int		already_parsed(struct fat_arch *fat, uint32_t current, uint8_t swap)
{
	uint32_t			i;

	i = 0;
	while (i < current)
	{
		if (swap_32(fat[i].cputype, swap) == swap_32(fat[current].cputype, swap))
			return (1);
		++i;
	}
	return (0);
}


void	nm_fat_32(t_nm *nm, void *ptr, uint8_t swap)
{
	struct fat_header	*header;
	struct fat_arch		*fat;
	void				*ptr2;
	uint32_t			i;
	uint32_t			cputype;

	header = (struct fat_header*)ptr;
	fat = (struct fat_arch*)(ptr + sizeof(struct fat_header));
	i = 0;
	while (i < swap_32(header->nfat_arch, swap))
	{
		ptr2 = header;
		cputype = swap_32(fat[i].cputype, swap);
		if (!already_parsed(fat, i, swap) && cputype == CPU_TYPE_X86_64)
		{
			ptr2 += swap_32(fat[i].offset, swap);
			ft_nm(nm, ptr2, NULL);
		}
		++i;
	}
}

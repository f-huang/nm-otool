/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 19:07:04 by fhuang            #+#    #+#             */
/*   Updated: 2019/01/26 16:42:35 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach/machine.h>
#include "ft_nm.h"

void	nm_fat_32(t_nm *nm, void *ptr, uint8_t swap)
{
	struct fat_header	*header;
	struct fat_arch		*fat;
	void				*ptr2;
	uint32_t			i;
	uint32_t			nfat_arch;

	header = (struct fat_header*)ptr;
	fat = (struct fat_arch*)(ptr + sizeof(struct fat_header));
	i = 0;
	nfat_arch = swap_32(header->nfat_arch, swap);
	while (i < nfat_arch)
	{
		ptr2 = header;
		if (swap_32(fat[i].cputype, swap) == CPU_TYPE_X86_64)
		{
			ptr2 += swap_32(fat[i].offset, swap);
			ft_nm(nm, ptr2, NULL);
		}
		++i;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 19:07:04 by fhuang            #+#    #+#             */
/*   Updated: 2019/01/26 16:43:51 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach/machine.h>
#include "ft_nm.h"

void	nm_fat_64(t_nm *nm, void *ptr, uint8_t swap)
{
	struct fat_header	*header;
	struct fat_arch_64	*fat64;
	void				*ptr2;
	uint64_t			i;
	uint64_t			nfat_arch;

	header = (struct fat_header*)ptr;
	fat64 = (struct fat_arch_64*)(ptr + sizeof(struct fat_header));
	i = 0;
	nfat_arch = swap_64(header->nfat_arch, swap);
	while (i < nfat_arch)
	{
		ptr2 = header;
		if (swap_64(fat64[i].cputype, swap) == CPU_TYPE_X86_64)
		{
			ptr2 += swap_64(fat64[i].offset, 64);
			ft_nm(nm, ptr2, NULL);
		}
		++i;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 19:07:04 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/01 11:43:39 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach/machine.h>
#include <stddef.h>
#include "ft_otool.h"

void	otool_fat(t_otool *otool, void *ptr)
{
	struct fat_header	*header;
	struct fat_arch_64	*fat64;
	void				*ptr2;
	uint32_t			i;

	header = (struct fat_header*)ptr;
	fat64 = (struct fat_arch_64*)(ptr + sizeof(struct fat_header));
	i = 0;
	while (i < header->nfat_arch)
	{
		ptr2 = header;
		if (fat64[i].cputype == CPU_TYPE_X86_64)
		{
			ptr2 += fat64[i].offset;
			ft_otool(otool, ptr2, 0, NULL);
		}
		++i;
	}
}

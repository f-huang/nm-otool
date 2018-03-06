/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 19:07:04 by fhuang            #+#    #+#             */
/*   Updated: 2018/02/18 01:03:27 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <mach-o/fat.h>
// #include <mach/machine.h>
// #include "ft_nm.h"
//
// void	handle_fat_64(t_nm *nm, void *ptr)
// {
// 	struct fat_header	*header;
// 	struct fat_arch_64	*fat64;
// 	void				*ptr2;
// 	uint32_t			i;
//
// 	header = (struct fat_header*)ptr;
// 	fat64 = (struct fat_arch_64*)(ptr + sizeof(struct fat_header));
// 	i = 0;
// 	while (i < header->nfat_arch)
// 	{
// 		ptr2 = header;
// 		if (fat64[i].cputype == CPU_TYPE_X86_64)
// 		{
// 			ptr2 += fat64[i].offset;
// 			ft_nm(nm, ptr2, NULL);
// 		}
// 		++i;
// 	}
// }

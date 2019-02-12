/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_64_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/12 14:34:56 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include "ft_swap.h"
#include "libft.h"
#include "ft_otool.h"

static void	print_section(struct section_64 *section, const void *ptr, uint8_t swap)
{
	uint64_t	size;
	uint64_t	i;
	uint64_t	j;
	uint8_t		*tmp;

	tmp = (uint8_t*)(ptr + swap_64(section->offset, swap));
	i = 0;
	size = swap_64(section->size, swap);
	while (i < size)
	{
		ft_printf("%0.16llx\t", swap_64(section->addr + i, swap));
		j = 0;
		while (j < 16 && i + j < size)
		{
			ft_printf("%02x ", tmp[i + j]);
			j++;
		}
		while (swap && j < 16 && i + j < size)
		{
			ft_printf("%02x", tmp[i + j]);
			j++;
			if (j % 4 == 0)
				ft_putchar(' ');
		}
		ft_printf("\n");
		i += 16;
	}
}

static void	parse_sections_64(struct segment_command_64 *segment,\
	const void *ptr, uint8_t swap)
{
	uint64_t			i;
	struct section_64	*section;

	i = 0;
	section = (struct section_64*)(segment + 1);
	while (i < swap_64(segment->nsects, swap))
	{
		if (ft_strequ(section[i].segname, SEG_TEXT)
			&& ft_strequ(section[i].sectname, SECT_TEXT))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			print_section(section + i, ptr, swap);
		}
		section = (struct section_64*)((void*)section +\
			sizeof(struct section_64));
		i++;
	}
}

void		otool_64_bits(t_otool *otool, void *ptr, const char *filename, uint8_t swap)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint64_t				i;

	header = (struct mach_header_64*)ptr;
	lc = ptr + sizeof(struct mach_header_64);
	i = 0;
	if (filename)
		ft_printf("%s:\n", filename);
	while (i < swap_64(header->ncmds, swap))
	{
		if (swap_64(lc->cmd, swap) == LC_SEGMENT_64)
			parse_sections_64((struct segment_command_64*)lc, ptr, swap);
		lc = (void*)lc + swap_64(lc->cmdsize, swap);
		++i;
	}
	(void)otool;
}

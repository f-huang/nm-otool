/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_32_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/12 14:29:43 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include "ft_swap.h"
#include "libft.h"
#include "ft_otool.h"

static void	print_section(struct section *section, const void *ptr, uint8_t swap)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	size;
	uint8_t		*tmp;

	tmp = (uint8_t*)(ptr + swap_32(section->offset, swap));
	i = 0;
	size = swap_32(section->size, swap);
	while (i < size)
	{
		ft_printf("%0.8llx\t", swap_32(section->addr, swap) + i);
		j = 0;
		while (!swap && j < 16 && i + j < size)
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
		ft_putchar('\n');
		i += 16;
	}
}

static void	parse_sections_32(struct segment_command *segment, const void *ptr, uint8_t swap)
{
	uint32_t			i;
	struct section		*section;

	i = 0;
	section = (struct section*)(segment + 1);
	while (i < swap_32(segment->nsects, swap))
	{
		if (ft_strequ(section[i].segname, SEG_TEXT)
			&& ft_strequ(section[i].sectname, SECT_TEXT))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			print_section(section + i, ptr, swap);
		}
		section = (struct section*)((void*)section + sizeof(struct section));
		i++;
	}
}

void		otool_32_bits(t_otool *otool, void *ptr, const char *filename, uint8_t swap)
{
	struct mach_header		*header;
	struct load_command		*lc;
	uint32_t				i;

	header = (struct mach_header*)ptr;
	lc = ptr + sizeof(struct mach_header);
	(void)swap;
	i = 0;
	if (filename)
		ft_printf("%s:\n", filename);
	while (i < swap_32(header->ncmds, swap))
	{
		if (swap_32(lc->cmd, swap) == LC_SEGMENT)
			parse_sections_32((struct segment_command*)lc, ptr, swap);
		lc = (void*)lc + swap_32(lc->cmdsize, swap);
		++i;
	}
	(void)otool;
}

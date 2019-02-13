/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_32_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 18:58:07 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include "ft_swap.h"
#include "libft.h"
#include "ft_otool.h"

static void	print_section(struct section *section,
							const void *ptr,
							void *end_of_file,
							uint8_t swap)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	size;
	uint8_t		*tmp;

	tmp = (uint8_t*)(ptr + swap_32(section->offset, swap));
	i = 0;
	size = swap_32(section->size, swap);
	if (!is_ptr_in_file(end_of_file, ptr + size)\
	|| !is_ptr_in_file(end_of_file, tmp + size))
		return ;
	while (i < size)
	{
		ft_printf("%0.8llx\t", swap_32(section->addr, swap) + i);
		j = -1;
		while (!swap && ++j < 16 && i + j < size)
			ft_printf("%02x ", tmp[i + j]);
		while (swap && ++j < 16 && i + j < size)
			ft_printf("%02x%s", tmp[i + j], (j + 1) % 4 == 0 ? " " : "");
		ft_putchar('\n');
		i += 16;
	}
}

static void	parse_sections_32(t_nm_otool *nm_otool,
								struct segment_command *segment,
								const void *ptr,
								uint8_t swap)
{
	uint32_t			i;
	struct section		*section;

	i = 0;
	section = (struct section*)(segment + 1);
	while (is_ptr_in_file(nm_otool->end_of_file, section + i)
		&& i < swap_32(segment->nsects, swap))
	{
		if (ft_strequ(section[i].segname, SEG_TEXT)
			&& ft_strequ(section[i].sectname, SECT_TEXT))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			print_section(section + i, ptr, nm_otool->end_of_file, swap);
		}
		section = (struct section*)((void*)section + sizeof(struct section));
		i++;
	}
}

void		otool_32_bits(t_nm_otool *nm_otool,
						void *ptr,
						const char *filename,
						uint8_t swap)
{
	struct mach_header		*header;
	struct load_command		*lc;
	uint32_t				i;

	header = (struct mach_header*)ptr;
	lc = ptr + sizeof(struct mach_header);
	i = 0;
	if (filename)
		ft_printf("%s:\n", filename);
	while (is_ptr_in_file(nm_otool->end_of_file, lc)
		&& i < swap_32(header->ncmds, swap))
	{
		if (swap_32(lc->cmd, swap) == LC_SEGMENT)
			parse_sections_32(nm_otool, (struct segment_command*)lc, ptr, swap);
		lc = (void*)lc + swap_32(lc->cmdsize, swap);
		++i;
	}
	(void)nm_otool;
}

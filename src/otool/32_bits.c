/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_bits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/06 02:20:39 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include "libft.h"
#include "ft_otool.h"

static void	print_section(struct section *section, const void *ptr)
{
	uint32_t	i;
	uint32_t	j;
	uint8_t		*tmp;

	tmp = (uint8_t*)(ptr + section->offset);
	i = 0;
	while (i < section->size)
	{
		ft_printf("%0.8llx\t", section->addr + i);
		j = 0;
		while (j < 16 && i + j < section->size)
		{
			ft_printf("%02x ", tmp[i + j]);
			j++;
		}
		ft_printf("\n");
		i += 16;
	}
}

static void	parse_sections_32(struct segment_command *segment, const void *ptr)
{
	uint32_t			i;
	struct section		*section;

	i = 0;
	section = (struct section*)(segment + 1);
	while (i < segment->nsects)
	{
		if (ft_strequ(section[i].segname, SEG_TEXT)
			&& ft_strequ(section[i].sectname, SECT_TEXT))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			print_section(section + i, ptr);
		}
		section = (struct section*)((void*)section + sizeof(struct section));
		i++;
	}
}

void		otool_32_bits(t_otool *otool, void *ptr, const char *filename)
{
	struct mach_header		*header;
	struct load_command		*lc;
	uint32_t				i;

	header = (struct mach_header*)ptr;
	lc = ptr + sizeof(struct mach_header);
	i = 0;
	if (filename)
		ft_printf("%s:\n", filename);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			parse_sections_32((struct segment_command*)lc, ptr);
		lc = (void*)lc + lc->cmdsize;
		++i;
	}
	(void)otool;
}

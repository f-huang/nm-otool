/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:29:44 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/30 19:38:38 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include "libft.h"
#include "ft_nm.h"

static char	get_section_type(const char *sectname)
{
	if (ft_strequ(sectname, "__text"))
		return ('T');
	else if (ft_strequ(sectname, "__bss"))
		return ('B');
	else if (ft_strequ(sectname, "__data"))
		return ('D');
	else
		return ('\0');
}

void		section_add(t_section sections[N_SECTION], struct segment_command_64 *seg)
{
	char				type;
	uint32_t			i;
	uint32_t			j;
	struct section_64	*sec;

	i = 0;
	j = sections[0].type ? 0 : 1;
	j += sections[1].type ? 1 : 0;
	sec = (void*)(seg + 1);
	while (i < seg->nsects && j < N_SECTION)
	{
		if ((type = get_section_type(sec->sectname)))
		{
			sections[j++] = (t_section) {
				.index = i + 1,
				.type = type
			};
		}
		sec += 1;
		++i;
	}
}

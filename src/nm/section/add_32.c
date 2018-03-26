/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:29:44 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/26 18:31:15 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include "libft.h"
#include "ft_nm.h"

void		section_add_32(t_section sections[N_SECTION],\
	uint8_t *section_ordinal, struct segment_command *seg)
{
	char			type;
	struct section	*sec;
	uint32_t		j;
	uint32_t		k;

	j = sections[0].type ? 0 : 1;
	j += sections[1].type ? 1 : 0;
	sec = (void*)(seg + 1);
	k = -1;
	while (++k < seg->nsects && j < N_SECTION)
	{
		if ((type = section_add_determine_type(sec->sectname)))
		{
			sections[j++] = (t_section) {
				.index = *section_ordinal + 1,
				.type = type
			};
		}
		sec += 1;
		++(*section_ordinal);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:29:44 by fhuang            #+#    #+#             */
/*   Updated: 2019/01/24 16:41:56 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include "libft.h"
#include "ft_nm.h"

void		section_add_64(t_section sections[N_SECTION],\
	uint8_t *section_ordinal, struct segment_command_64 *seg)
{
	char				type;
	struct section_64	*sec;
	uint32_t			j;
	uint32_t			k;

	sec = (void*)(seg + 1);
	k = -1;
	j = (sections[0].type ? 1 : 0) + (sections[1].type ? 1 : 0);
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

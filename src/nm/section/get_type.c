/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:44:16 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/30 18:57:40 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	section_get_type(t_section *sections, uint8_t index)
{
	uint32_t	i;

	i = 0;
	while (i < N_SECTION)
	{
		if (sections[i].index == index)
			return (sections[i].type);
		++i;
	}
	return ('\0');
}

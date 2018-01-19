/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_determine_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 14:11:48 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/19 14:14:57 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define SEC_TEXT "__text"
#define SEC_BSS "__bss"
#define SEC_DATA "__data"

char	section_add_determine_type(const char *sectname)
{
	if (ft_strequ(sectname, SEC_TEXT))
		return ('T');
	else if (ft_strequ(sectname, SEC_BSS))
		return ('B');
	else if (ft_strequ(sectname, SEC_DATA))
		return ('D');
	else
		return ('\0');
}

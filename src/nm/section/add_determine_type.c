/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_determine_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 14:11:48 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/19 14:45:39 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include "libft.h"

char	section_add_determine_type(const char *sectname)
{
	if (ft_strequ(sectname, SECT_TEXT))
		return ('T');
	else if (ft_strequ(sectname, SECT_BSS))
		return ('B');
	else if (ft_strequ(sectname, SECT_DATA))
		return ('D');
	else
		return ('\0');
}

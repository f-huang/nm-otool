/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_skipped.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:49:13 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/19 16:33:31 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		is_symbol_skipped(int options, char type)
{
	if (options & OPTION_UU && (type == 'U' || type == 'u'))
		return (1);
	else if (options & OPTION_U && type != 'U' && type != 'U')
		return (1);
	else if (type == '-')
		return (1);
	return (0);
}

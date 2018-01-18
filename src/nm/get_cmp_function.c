/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmp_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:13:55 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/18 18:30:06 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int (*get_cmp_function(int options))(t_symbol, t_symbol)
{
	if (options & OPTION_N)
		return ((options & OPTION_R) ? symbol_cmp_r_value : symbol_cmp_value);
	else
		return ((options & OPTION_R) ? symbol_cmp_r_name : symbol_cmp_name);
}

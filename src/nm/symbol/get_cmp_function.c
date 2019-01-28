/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmp_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:13:55 by fhuang            #+#    #+#             */
/*   Updated: 2019/01/28 19:44:20 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

int		symbol_cmp_name(t_symbol sym1, t_symbol sym2)
{
	int		ret;

	ret = ft_strcmp(sym1.name, sym2.name);
	return (ret ? ret : symbol_cmp_value(sym1, sym2));
}

int		symbol_cmp_r_name(t_symbol sym1, t_symbol sym2)
{
	int		ret;

	ret = ft_strcmp(sym1.name, sym2.name) * -1;
	return (ret ? ret : symbol_cmp_r_value(sym1, sym2));
}

int		symbol_cmp_r_value(t_symbol sym1, t_symbol sym2)
{
	return (!(sym1.value > sym2.value));
}

int		symbol_cmp_value(t_symbol sym1, t_symbol sym2)
{
	return (sym1.value > sym2.value);
}

int		(*get_cmp_function(int options))(t_symbol, t_symbol)
{
	if (options & OPTION_N)
		return ((options & OPTION_R) ? symbol_cmp_r_value : symbol_cmp_value);
	else
		return ((options & OPTION_R) ? symbol_cmp_r_name : symbol_cmp_name);
}

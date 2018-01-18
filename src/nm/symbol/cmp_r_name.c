/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_r_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:14:19 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/18 18:37:18 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

int		symbol_cmp_r_name(t_symbol sym1, t_symbol sym2)
{
	int		ret;

	return (!(ret = ft_strcmp(sym1.name, sym2.name) * -1) ? 1 : ret);
}

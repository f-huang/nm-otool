/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:14:19 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/30 19:15:36 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

int		symbol_cmp_name(t_symbol sym1, t_symbol sym2)
{
	return (ft_strcmp(sym1.name, sym2.name));
}

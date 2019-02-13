/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 17:49:06 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 15:08:08 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm_otool.h"

void		otool_ar(t_nm_otool *nm_otool, void *ptr, const char *filename, uint8_t swap)
{
	(void)swap;
	ft_printf("Archive : %s\n", filename);
	ar(nm_otool, ptr, filename);
}

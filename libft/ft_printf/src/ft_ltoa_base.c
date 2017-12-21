/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 13:40:41 by fhuang            #+#    #+#             */
/*   Updated: 2017/11/02 19:04:06 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_n(unsigned long n, int base)
{
	int					ret;

	ret = 1;
	while (n / base)
	{
		ret++;
		n /= base;
	}
	return (ret);
}

char		*ft_ltoa_base(long n, int base, int is_uin)
{
	char				pattern[17];
	char				*ret;
	unsigned long		uin;
	int					len;
	int					neg;

	ft_strcpy(pattern, "0123456789abcdef");
	neg = (base == 10 && n < 0) ? 1 : 0;
	neg && is_uin == 0 ? ABS(n) : 1;
	uin = (unsigned long)n;
	len = count_n(uin, base);
	if ((ret = ft_strnew(len)) == NULL)
		return (NULL);
	ret[len--] = 0;
	while (len >= 0)
	{
		ret[len] = pattern[uin % base];
		uin /= base;
		len--;
	}
	return (ret);
}

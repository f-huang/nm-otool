/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_through_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:18:24 by fhuang            #+#    #+#             */
/*   Updated: 2018/02/20 12:22:20 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm_otool.h"

int		loop_through_arg(void *env, char **av, int i, int (*f)(void*, void *ptr, const char*))
{
	void	*ptr;
	size_t	size;
	int		fd;

	ptr = NULL;
	size = 0;
	while (1)
	{
		if ((fd = open_and_map(!av[i] ? DEFAULT_FILE : av[i], &ptr, &size)) != -1)
		{
			f(env, ptr, !av[i] ? DEFAULT_FILE : av[i]);
			close_and_unmap(ptr, size, fd);
		}
		if (!av[i] || !av[++i])
			break ;
	}
	return (0);
}

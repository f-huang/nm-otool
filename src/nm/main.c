/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 09:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/30 19:41:17 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_nm.h"

int		main(int ac, char **av)
{
	t_nm	nm;
	int		i;

	i = 0;
	ft_bzero(&nm, sizeof(t_nm));
	if (!set_options(av, &nm, &i))
		return (EXIT_FAILURE);
	if (!set_files(av, &nm, ac, i))
		return (EXIT_FAILURE);
	name_list(&nm);
	clear(&nm);
	return (EXIT_SUCCESS);
}

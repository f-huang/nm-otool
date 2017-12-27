/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:31:12 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/27 13:00:11 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

static int	set_option_in_struct(t_nm *nm, const char c)
{
	static const struct s_nm_options	options[] = {
		{'n', OPTION_N},
		{'r', OPTION_R},
		{'u', OPTION_U},
		{'U', OPTION_UU},
		{'x', OPTION_X},
		{'j', OPTION_J},
		{'t', OPTION_T},
		{'h', OPTION_H},
		{'\0', 0}
	};
	int									i;

	i = 0;
	while (options[i].c)
	{
		if (options[i].c == c)
		{
			if (nm->options & options[i].shift)
			{
				nm->options = c;
				return (ERROR_OPTION_DUPLICATE);
			}
			nm->options |= options[i].shift;
			return (0);
		}
		++i;
	}
	return (ERROR_OPTION_UNDEFINED);
}
static void	print_error(t_nm nm, const char *str, int error)
{
	if (error == ERROR_OPTION_UNDEFINED)
		ft_printf_fd(2, PROGRAM_NAME": "OUTPUT_ERROR_OPTION_UNDEFINED"\n", str);
	else if (error == ERROR_OPTION_DUPLICATE)
		ft_printf_fd(2, PROGRAM_NAME": "OUTPUT_ERROR_OPTION_DUPLICATE"\n", nm.options);
}

int			set_options(char **av, t_nm *nm, int *i)
{
	int									j;
	int									error;

	*i = 0;
	error = 0;
	while (!error && av[++(*i)] && av[*i][0] == '-')
	{
		j = 0;
		while (av[*i][++j])
		{
			if (ft_strfind_c(NM_OPTIONS, av[*i][j]))
			{
				if ((error = set_option_in_struct(nm, av[*i][j])))
					break ;
			}
			else if ((error = ERROR_OPTION_UNDEFINED))
				break ;
		}
	}
	if (av[*i] && ft_strequ(av[*i], "--") && !(error = 0))
		++(*i);
	print_error(*nm, av[*i], error);
	return (!error);
}

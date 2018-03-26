/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:31:12 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/26 19:08:39 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

#define ERROR_OPTION_UNDEFINED 10
#define ERROR_OPTION_DUPLICATE 11
#define ERROR_OPTION_FORMAT_NOT_FOUND 12

#define N_OPTIONS 8

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
		{'h', OPTION_H}
	};
	int									i;

	i = -1;
	while (++i < N_OPTIONS)
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
	return (ERROR_OPTION_UNDEFINED);
}

static void	print_error(t_nm nm, const char *str, int error)
{
	if (error == ERROR_OPTION_UNDEFINED)
		ft_printf_fd(2, PROGRAM_NAME\
			": Unknow command line argument '%s'. Try: nm -h\n", str);
	else if (error == ERROR_OPTION_FORMAT_NOT_FOUND)
	{
		if (str)
			ft_printf_fd(2, PROGRAM_NAME\
				": for the -radix option: Cannot find option named '%c'\n",\
				nm.options);
		else
			ft_printf_fd(2, PROGRAM_NAME\
				": for the -t option: requires a value !\n");
	}
	else if (error == ERROR_OPTION_DUPLICATE)
		ft_printf_fd(2, PROGRAM_NAME\
			": for the -%c option: may only occur zero or one times!\n",\
			nm.options);
}

static void	set_option_format(t_nm *nm, char c)
{
	if (c == 'd')
		nm->format = DECIMAL;
	else if (c == 'o')
		nm->format = OCTAL;
	else
		nm->format = HEXA;
}

static int	is_option_found(char *av, t_nm *nm, int *error)
{
	if (!av || ft_strlen(av) > 1\
		|| !ft_strfind_c(NM_OPTION_FORMATS, av[0]))
	{
		nm->options = av ? (char)av[0] : nm->options;
		*error = ERROR_OPTION_FORMAT_NOT_FOUND;
		return (0);
	}
	return (1);
}

int			set_options(char **av, t_nm *nm, int *i)
{
	int									j;
	int									error;

	*i = 0;
	error = 0;
	while (!error && av[++(*i)] && av[*i][0] == '-' && !(j = 0))
		while (av[*i][++j] && !error)
			if (ft_strfind_c(NM_OPTIONS, av[*i][j]))
			{
				error = set_option_in_struct(nm, av[*i][j]);
				if (!error && (av[*i][j] == 't' && (++(*i)) && !(j = 0)))
				{
					if (!is_option_found(av[*i], nm, &error))
						break ;
					set_option_format(nm, av[*i][j]);
				}
			}
			else if (!error && (error = ERROR_OPTION_UNDEFINED))
				break ;
	if (av[*i] && ft_strequ(av[*i], "--") && !(error = 0))
		++(*i);
	print_error(*nm, av[*i], error);
	return (!error);
}

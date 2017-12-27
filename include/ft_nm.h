/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 08:40:36 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/27 13:03:45 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# define PROGRAM_NAME "nm"
# define DEFAULT_FILE "a.out"

/*
**	OPTIONS
**		 -n     Sort numerically rather than alphabetically.
**		 -r     Sort in reverse order.
**		 -u     Display only undefined symbols.
**		 -U     Don't display undefined symbols.
**		 -x     Display the symbol table entry's fields in hexadecimal,
**		                   along with the name as a string.
**		 -j     Just display the symbol names (no value or type).
**		 -t     format
**		            d      The value shall be written in decimal (default).
**		            o      The value shall be written in octal.
**		            x      The value shall be written in hexadecimal.
*/

# define ERROR_OPTION_UNDEFINED 10
# define ERROR_OPTION_DUPLICATE 11

# define OUTPUT_ERROR_OPTION_UNDEFINED "Unknow command line argument '%s'. Try: nm -h"
# define OUTPUT_ERROR_OPTION_DUPLICATE "for the -%c option: may only occur zero or one times!"

# define NM_OPTIONS "nruUxjth"

# define OPTION_N  (1 << 0)
# define OPTION_R  (1 << 1)
# define OPTION_U  (1 << 2)
# define OPTION_UU (1 << 3)
# define OPTION_X  (1 << 4)
# define OPTION_J  (1 << 5)
# define OPTION_T  (1 << 6)
# define OPTION_H  (1 << 7)

struct				s_nm_options
{
	const char	c;
	int			shift;
};

typedef struct		s_nm
{
	int		options;
	char	**files;
}					t_nm;

int					get_symbols(t_nm *nm);
int					set_options(char **av, t_nm *nm, int *i);
int					set_files(char **av, t_nm *nm, int ac, int i);
void				clear(t_nm *nm);

#endif

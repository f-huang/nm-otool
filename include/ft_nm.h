/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 08:40:36 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/29 18:27:10 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdint.h>

/*
**	DESCRIPTION
**		If an argument is an  archive,
**			a listing for each object file in the archive will be produced.
**		Unless the -m option is  specified, each symbol name is preceded by
**			its value (blanks if undefined).
**		Symbol type:
**			U = undefined
**			A = absolute
**			T = text section symbol
**			D = data section symbol
**			B = bss section symbol
**			C = common symbol
**			I = indirect symbol
**			- = debugger symbol table entries
**			S = symbol in a section other than those above
**		If the symbol is local (non-external), the symbol's  type
**		is  instead  represented  by  the corresponding lowercase letter.
**		A lower case u in a dynamic shared library indicates a undefined
**		reference to a private external in another module in the same  library.
**		If the symbol is a Objective C method, the symbol name is
**			+-[Class_name(category_name) method:name:],      where
**				`+' is for class methods,
**				`-' is for instance methods,
**				(category_name) is present only when the method is in a category
**		The output is sorted alphabetically by default.
*/

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

struct				s_symbol
{
	char			*name;
	char			type;
	uint64_t		value;
}					t_symbol;

struct				s_nm_options
{
	const char	c;
	int			shift;
};

typedef struct		s_nm
{
	int			options;
	char		**files;
}					t_nm;

int					name_list(t_nm *nm);
int					set_options(char **av, t_nm *nm, int *i);
int					set_files(char **av, t_nm *nm, int ac, int i);
void				clear(t_nm *nm);


void				handle_64_bits(t_nm *nm, void *ptr);

#endif

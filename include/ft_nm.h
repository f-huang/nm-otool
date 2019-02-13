/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 08:40:36 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 17:47:18 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdint.h>
# include <stddef.h>
# include <mach-o/loader.h>

# include "ft_nm_otool.h"
/*
**	DESCRIPTION
**		If an argument is an  archive,
**			a listing for each object file in the archive will be produced.
**		Unless the -m option is  specified, each symbol name is preceded by
**			its value (blanks if undefined).
**		Symbol type:
**			U = undefined										√
**			A = absolute										√
**			T = text section symbol								√
**			D = data section symbol								√
**			B = bss section symbol								√
**			C = common symbol									√
**			I = indirect symbol									√
**			- = debugger symbol table entries					√
**			S = symbol in a section other than those above		√
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

/*
**	EXTERNAL LINKS
**		https://www.unix.com/man-page/opensolaris/3HEAD/ar.h/
**		http://www.manpagez.com/man/5/ranlib/
**		http://www.manpagez.com/man/5/ar/
*/


/*
**	OPTIONS
**		 -n     Sort numerically rather than alphabetically.				√
**		 -r     Sort in reverse order.										√
**		 -u     Display only undefined symbols.								√
**		 -U     Don't display undefined symbols.							√
**		 -x     Display the symbol table entry's fields in hexadecimal,
**		                   along with the name as a string.
**		 -j     Just display the symbol names (no value or type).			√
**		 -t     format														√
**		            d      The value shall be written in decimal.
**		            o      The value shall be written in octal.
**		            x      The value shall be written in hexadecimal (default).
*/

# define NM_OPTIONS "nruUjth"
# define NM_OPTION_FORMATS "dox"

# define OPTION_N  (1 << 0)
# define OPTION_R  (1 << 1)
# define OPTION_U  (1 << 2)
# define OPTION_UU (1 << 3)
# define OPTION_X  (1 << 4)
# define OPTION_J  (1 << 5)
# define OPTION_T  (1 << 6)
# define OPTION_H  (1 << 7)

/*
**	3 types of LC_SEGMENT load_command->cmd:
**		PAGE_ZERO, TEXT, DATA
*/

# define N_SECTION 3

enum				e_nm_format
{
	DECIMAL_64 = 10,
	OCTAL_64 = 8,
	HEXA_64 = 16,
	DECIMAL_32 = -10,
	OCTAL_32 = -8,
	HEXA_32 = -16
};

typedef struct		s_symbol
{
	char				*name;
	char				type;
	uint64_t			value;
	struct s_symbol		*next;
}					t_symbol;

typedef struct		s_section
{
	uint8_t				index;
	char				type;
}					t_section;

struct				s_nm_options
{
	const char			c;
	int					shift;
};

struct				s_nm_print
{
	enum e_nm_format	format;
	const char			*str1;
	const char			*str2;
};

typedef struct		s_nm
{
	int					options;
	enum e_nm_format	format;
	uint8_t				section_ordinal;
	t_section			sections[N_SECTION];
	t_symbol			*symbols;
}					t_nm;

int					set_options(char **av, t_nm *nm, int *i);
void				print_symbol_table(t_symbol *symbols,\
						enum e_nm_format format, int options);

void				nm_ar(t_nm_otool *nm_otool, void *ptr, const char *filename, uint8_t swap);
void				nm_32_bits(t_nm_otool *nm_otool, void *ptr, const char *filename, uint8_t swap);
void				nm_64_bits(t_nm_otool *nm_otool, void *ptr, const char *filename, uint8_t swap);

char				section_add_determine_type(const char *sectname);
void				section_add_32(t_section *sections,\
						uint8_t *section_ordinal, struct segment_command *seg, uint8_t swap);
void				section_add_64(t_section *sections,\
						uint8_t *section_ordinal,\
						struct segment_command_64 *seg, uint8_t swap);
char				section_get_type(t_section *sections, uint8_t index);
int					is_symbol_skipped(int options, char type);
void				symbol_add(t_symbol **symbols, t_symbol *new,\
						int (*cmp)(t_symbol, t_symbol));
void				symbol_clear(t_symbol **symbols);

int					(*get_cmp_function(int options))(t_symbol, t_symbol);
int					symbol_cmp_name(t_symbol sym1, t_symbol sym2);
int					symbol_cmp_value(t_symbol sym1, t_symbol sym2);
int					symbol_cmp_r_name(t_symbol sym1, t_symbol sym2);
int					symbol_cmp_r_value(t_symbol sym1, t_symbol sym2);

#endif

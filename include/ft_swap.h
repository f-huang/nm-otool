/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:43:30 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/12 10:43:52 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SWAP_H
# define FT_SWAP_H

uint8_t				swap_16(uint8_t value, uint8_t swap);
uint32_t			swap_32(uint32_t value, uint8_t swap);
uint64_t			swap_64(uint64_t value, uint8_t swap);

#endif

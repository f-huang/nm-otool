/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:00:57 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/19 11:42:48 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		**fresh_lst;
	t_list		*new_link;

	if (!(fresh_lst = ((t_list**)malloc(sizeof(t_list *)))))
		return (NULL);
	*fresh_lst = NULL;
	while (lst != NULL)
	{
		if (!(new_link = (t_list*)malloc(sizeof(t_list))))
			return (NULL);
		new_link = f(lst);
		ft_lstaddend(fresh_lst, new_link);
		free(new_link);
		lst = lst->next;
	}
	return (*fresh_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 14:37:18 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/10 17:51:07 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_glob		*get_glob(void)
{
	static t_glob	glob = {0, 0, 0, 0, 1};

	return (&glob);
}

t_list		**get_room(void)
{
	static t_list	*rooms = NULL;

	return (&rooms);
}

int			***get_path(void)
{
	static int		**path = NULL;
	unsigned int	i;

	if (path == NULL)
	{
		path = (int**)ft_memalloc(sizeof(int*) * get_glob()->count);
		i = 0;
		while (i < get_glob()->count)
			path[i++] = (int*)ft_memalloc(sizeof(int) * get_glob()->count);
	}
	return (&path);
}
